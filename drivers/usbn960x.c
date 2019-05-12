/*
 * usbn960x.c
 *
 *  Created on: Dec 14, 2017
 *      Author: steff
 */

#include "usbn960x.h"

#include "board.h"

#include <usb/usb.h>
#include <usb/usb_device.h>
#include <usb/usb_request.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay_basic.h>

#include <stdint.h>

typedef struct _usbn960x_ep_t {
	uint8_t regs;
	uint8_t addr;

	usb_buffer_t buffer;

	uint16_t size;

	union {
		usb_out_hdlr_t out_hdlr;
		usb_in_hdlr_t in_hdlr;
	};
} usbn960x_ep_t;

typedef struct _usbn960x_t {
	void *ep0_out, *ep0_in;

	usbn960x_ep_t eps[8];

	uint8_t address;

	usbn960x_ep_t *txfifo_to_ep[4];
	usbn960x_ep_t *rxfifo_to_ep[4];

	uint8_t ep_idx;				/* for ep allocation */
} usbn960x_t;

static uint8_t ep0_out_buffer[16];

static usbn960x_t _usbn960x;
static usbn960x_t *usbn960x = &_usbn960x;

static void ep0_out_handler(void *_ep, const uint8_t *data, unsigned int len)
{
	/* ignore status stage */
	if (len > 0) {
		const usb_setup_t *setup = (usb_setup_t *)data;
		if (usb_request_handle(usbn960x->ep0_in, setup, data + sizeof(*setup), len - sizeof(*setup)) < 0)
			usbn960x_stall_ep(usbn960x->ep0_in);
	}
}

/* this is called after successfully transmitting control endpoint IN data */
static void ep0_in_handler(void *_ep)
{
	usbn960x_ep_t *ep = usbn960x->ep0_out;
	usb_buffer_t *out_buffer = &ep->buffer;
	usb_setup_t *setup = out_buffer->data;

	if (setup->bmRequestType & USB_REQ_DIR_IN) {
		/* enable receive for OUT status stage */
		usbn960x_receive_data(ep);
	}
}

static void alternate_event_handler(void)
{
	uint8_t altev0 = board_usbn960x_read(USBN960x_ALTEV) &
			board_usbn960x_read(USBN960x_ALTMSK);

	if (altev0 & USBN960x_ALTEV_RESET) {
		/* enter reset state */
		board_usbn960x_write(USBN960x_NFSR, 0 << USBN960x_NFSR_NFS_Pos);

		usbn960x->address = 0;

		/* configure EP0 for address reception */
		board_usbn960x_write(USBN960x_FAR, USBN960x_FAR_AD_EN);
		board_usbn960x_write(USBN960x_TXC0, USBN960x_TXC0_FLUSH);
		while (board_usbn960x_read(USBN960x_TXC0) & USBN960x_TXC0_FLUSH) {};
		board_usbn960x_write(USBN960x_RXC0, USBN960x_RXC0_FLUSH);
		while (board_usbn960x_read(USBN960x_RXC0) & USBN960x_RXC0_FLUSH) {};

		/* leave reset state */
		board_usbn960x_write(USBN960x_NFSR, 2 << USBN960x_NFSR_NFS_Pos);
	}

	/* other event bits are related to DMA or suspend/resume */
}

static void write_packet(usbn960x_ep_t *ep)
{
	usb_buffer_t *in_buffer = &ep->buffer;
	int i, n = in_buffer->valid - in_buffer->pos;
	uint8_t txc0 = board_usbn960x_read(ep->regs + 3);

	/* TXFIFO _should_ be empty at this point */

	if (n > ep->size)
		n = ep->size;

	for (i = 0; i < n; i++)
		board_usbn960x_write(ep->regs + 1, ((uint8_t *)in_buffer->data)[in_buffer->pos++]);

	/* toggle DATA0/DATA1 */
	txc0 ^= USBN960x_TXC0_TOGGLE;

	/* start transmitting
	   NOTE: LAST bit does not exist in TXC0,
	         but seemingly it does not hurt either */
	board_usbn960x_write(ep->regs + 3, txc0 | USBN960x_TXC_LAST | USBN960x_TXC0_TX_EN);
}

static void transmit_handler(usbn960x_ep_t *ep)
{
	uint8_t txs0 = board_usbn960x_read(ep->regs + 2);

	/* 7.1.9 Transmit Event Register (TXEV) - TXFIFO
	    These bits are a copy of the TX_DONE bits from the corresponding
	    Transmit Status (TXSx) registers. */
	/* -> no need to check TX_DONE */

	if (txs0 & USBN960x_TXS0_ACK_STAT) {
		usb_buffer_t *in_buffer = &ep->buffer;

		if (in_buffer->pos < in_buffer->valid) {
			write_packet(ep);
			putck('w');
		} else {
			/* transfer finished */
			if (ep->in_hdlr != NULL)
				ep->in_hdlr(ep);
			putck('.');
		}
	} else {
		putck('#');
	}
}

static void transmit_event_handler(void)
{
	uint8_t txev0 = board_usbn960x_read(USBN960x_TXEV) &
			board_usbn960x_read(USBN960x_TXMSK);
	uint8_t idx;

	/* TXUDRRN3-0 should always be 0, since underrun cannot occur,
	   because LAST and TX_EN in TXC are always set simultaneously */

	/* check for TXFIFO3-0 */
	for (idx = 0; txev0 != 0x00; txev0 >>= 1, idx++)
		if (txev0 & 0x01)
			transmit_handler(usbn960x->txfifo_to_ep[idx]);
}

static void clear_stall(usbn960x_ep_t *ep)
{
	uint8_t epc0 = board_usbn960x_read(ep->regs);
	if (epc0 & USBN960x_EPC0_STALL)
		board_usbn960x_write(ep->regs, epc0 & ~(USBN960x_EPC0_STALL));
}

static void receive_handler(usbn960x_ep_t *ep)
{
	usb_buffer_t *out_buffer = &ep->buffer;

	/* read status flags first, since they get cleared on read */
	uint8_t rxs0 = board_usbn960x_read(ep->regs + 2);
	uint8_t rcount = (rxs0 & USBN960x_RXS0_RCOUNT_Msk) >> USBN960x_RXS0_RCOUNT_Pos;

	if (rxs0 & USBN960x_RXS0_SETUP)
		out_buffer->pos = 0;

	while (rcount != 0) {
		/* stall endpoint, if allocated buffer is not large enough */
		if (out_buffer->pos + rcount > out_buffer->size) {
			usbn960x_stall_ep(ep);
			return;
		}

		out_buffer->pos += board_usbn960x_read_multi(ep->regs + 1,
				(uint8_t *)out_buffer->data + out_buffer->pos, rcount);

		rcount = board_usbn960x_read(ep->regs + 2);
	}

	if (rxs0 & USBN960x_RXS0_SETUP) {
		/* TODO: ep0 muss nicht richtig sein! */
		usbn960x_ep_t *ep0_in = usbn960x->ep0_in;

		/* TODO: fuer andere EPs als EP0 anpassen */
		usb_setup_t *setup = out_buffer->data;
		unsigned int valid = out_buffer->pos;

		putck('\n');

		/* clear stall, if it is set from previous transfer */
		clear_stall(ep);
		clear_stall(ep0_in);

		if (setup->bmRequestType & USB_REQ_DIR_IN) {
			/* reset toggle bit so next DATA token will be DATA1 */
			board_usbn960x_write(ep0_in->regs + 3, 0);

			putck('i');
		} else {
			valid += setup->wLength;

			putck('o');
		}

		out_buffer->valid = valid;
	}

	if (out_buffer->pos >= out_buffer->valid) {
		unsigned int pos = out_buffer->pos;

		/* no more data expected */
		out_buffer->valid = 0;
		out_buffer->pos = 0;

		if (ep->out_hdlr != NULL)
			ep->out_hdlr(ep, (const uint8_t *)out_buffer->data, pos);
	} else {
		/* expecting more data, enable receiver for next OUT token */
		usbn960x_receive_data(ep);
	}
}

static void receive_event_handler(void)
{
	uint8_t rxev0 = board_usbn960x_read(USBN960x_RXEV) &
			board_usbn960x_read(USBN960x_RXMSK);
	uint8_t idx;

	/* RXOVRRN3-0 should always be 0, since RX_EN is only set,
	   when the receive FIFO _should_ be empty */

	/* check for RXFIFO3-0 */
	for (idx = 0; rxev0 != 0x00; rxev0 >>= 1, idx++)
		if (rxev0 & 0x01)
			receive_handler(usbn960x->rxfifo_to_ep[idx]);
}

#if 0
static void nack_event_handler(void)
{
	board_usbn960x_read(USBN960x_NAKEV);
}
#endif

void usbn960x_handler(void)
{
	uint8_t maev0 = board_usbn960x_read(USBN960x_MAEV) &
			board_usbn960x_read(USBN960x_MAMSK);

	if (maev0 & USBN960x_MAEV_ALT)
		alternate_event_handler();

	if (maev0 & USBN960x_MAEV_TX_EV)
		transmit_event_handler();

	if (maev0 & USBN960x_MAEV_RX_EV)
		receive_event_handler();

#if 0
	if (maev0 & USBN960x_MAEV_NAK)
		nack_event_handler();
#endif

	/* TODO: FRAME auswerten -> SOF */
}

static usbn960x_ep_t *alloc_ep(uint8_t addr, uint8_t size)
{
	usbn960x_ep_t *ep = &usbn960x->eps[usbn960x->ep_idx++];

	ep->addr = addr;
	/* TODO: hardware-limitierungen beruecksichtigen? */
	ep->size = size;

	return ep;
}

void usbn960x_init(void)
{
	uint8_t mcntrl0 = 3 << USBN960x_MCNTRL_INTOC_Pos | USBN960x_MCNTRL_VGE;

	/* first set clock output to 16 MHz */
	board_usbn960x_write(USBN960x_CCONF, (USBN960x_CKI / F_CPU) - 1);

	/* perform software reset, all registers but CCONF are effected */
	board_usbn960x_write(USBN960x_MCNTRL, USBN960x_MCNTRL_SRST);
	while (board_usbn960x_read(USBN960x_MCNTRL) & USBN960x_MCNTRL_SRST) {};

	usbn960x->ep_idx = 0;

	/* configure interrupt pin as low active, push-pull and enable internal
	 * 3.3V voltage regulator */
	board_usbn960x_write(USBN960x_MCNTRL, mcntrl0);

//	usbn960x_write(USBN960x_MAMSK, USBN960x_MAMSK_ALT);
//	usbn960x_write(USBN960x_ALTMSK, USBN960x_ALTMSK_RESET);
	board_usbn960x_write(USBN960x_MAMSK, 0xf7);
	board_usbn960x_write(USBN960x_ALTMSK, 0xfd);
//	usbn960x_write(USBN960x_NAKMSK, 0xff);

	usbn960x->ep0_out = alloc_ep(0x00, 8);
	usbn960x->ep0_in = alloc_ep(0x80, 8);

	/* configure EP0, RX and TX */
	usbn960x_setup_send(usbn960x->ep0_in, ep0_in_handler);
	usbn960x_enable_ep(usbn960x->ep0_in);
	usbn960x_setup_receive(usbn960x->ep0_out, ep0_out_buffer, sizeof(ep0_out_buffer),
			ep0_out_handler);
	usbn960x_enable_ep(usbn960x->ep0_out);

	board_usbn960x_write(USBN960x_FAR, USBN960x_FAR_AD_EN);

	/* TODO: notwendig? wird im Reset-Interrupt gemacht */
	/* enter operation state */
	board_usbn960x_write(USBN960x_NFSR, 2 << USBN960x_NFSR_NFS_Pos);
}

void usbn960x_connect(void)
{
	uint8_t mcntrl0 = board_usbn960x_read(USBN960x_MCNTRL);

	/* 7.1.1 Main Control Register (MCNTRL) - NAT:
	 *  The NAT bit should be set by the firmware if an external 3.3V supply
	 *  has been provided to the V3.3 pin, or at least 1 ms after the VGE bit
	 *  is set (in the latter case, the delay allows the internal regulator
	 *  sufficient time to stabilize). */
	_delay_loop_2((F_CPU / 1000) / 4);
	board_usbn960x_write(USBN960x_MCNTRL, mcntrl0 | USBN960x_MCNTRL_NAT);
}

void usbn960x_setup_receive(void *_ep, uint8_t *buf, unsigned int size,
		usb_out_hdlr_t out_hdlr)
{
	usbn960x_ep_t *ep = _ep;

	ep->buffer.data = buf;
	ep->buffer.size = size;
	ep->buffer.pos = 0;

	ep->out_hdlr = out_hdlr;
}

void usbn960x_setup_send(void *_ep, usb_in_hdlr_t in_hdlr)
{
	usbn960x_ep_t *ep = _ep;
	ep->in_hdlr = in_hdlr;
}

void usbn960x_receive_data(void *_ep)
{
	usbn960x_ep_t *ep = _ep;
	board_usbn960x_write(ep->regs + 3, USBN960x_RXC1_RX_EN);

	putck('r');
}

int usbn960x_send_data(void *_ep, const uint8_t *data, unsigned int len)
{
	usbn960x_ep_t *ep = _ep;
	usb_buffer_t *in_buffer = &ep->buffer;

	/* if not addressed, limit transfer to one packet */
	if (usbn960x->address == 0 && len > 8)
		len = 8;

	/* discard const qualifier */
	in_buffer->data = (uint8_t *)data;
	in_buffer->valid = len;
	in_buffer->pos = 0;

	write_packet(ep);

	putck('s');
	return 0;
}

void usbn960x_send_ack(void *_ep)
{
	usbn960x_ep_t *ep = _ep;

	/* send ACK (DATA1) (zero length packet) */
	board_usbn960x_write(ep->regs + 3, USBN960x_TXC_TOGGLE | USBN960x_TXC_LAST | USBN960x_TXC_TX_EN);
	putck('a');
}

int usbn960x_set_address(uint16_t addr)
{
	usbn960x->address = addr;

	/* setting DEF aids transition to assigned address */
	board_usbn960x_write(USBN960x_EPC0,USBN960x_EPC0_DEF);
	board_usbn960x_write(USBN960x_FAR, USBN960x_FAR_AD_EN | addr);

	/* send ACK (DATA1), DEF is cleared after this packet */
	board_usbn960x_write(USBN960x_TXC0, USBN960x_TXC0_TOGGLE | USBN960x_TXC0_TX_EN);

	return 0;
}

void *usbn960x_alloc_ep(usb_endpoint_descriptor_t *ep_descr)
{
	return (void *)alloc_ep(ep_descr->bEndpointAddress, ep_descr->wMaxPacketSize);
}

void usbn960x_enable_ep(void *_ep)
{
	usbn960x_ep_t *ep = _ep;
	uint8_t msk_reg = ep->addr & USB_EP_DIR_IN ? USBN960x_TXMSK : USBN960x_RXMSK;
	uint8_t msk0, msk1;
	uint8_t idx = 0;

	/* use TXMSK/RXMSK to allocate fifos */
	msk0 = board_usbn960x_read(msk_reg);
	for (msk1 = msk0; msk1 != 0x00; msk1 >>= 1)
		idx++;

	board_usbn960x_write(msk_reg, msk0 | (1 << idx));
	if (ep->addr & USB_EP_DIR_IN) {
		usbn960x->txfifo_to_ep[idx] = ep;
		ep->regs = (USBN960x_TXD0 - 1) + (idx << 3);

		/* set TOGGLE for IN transfers to start with DATA0 */
		board_usbn960x_write(ep->regs + 3, USBN960x_TXC0_FLUSH | USBN960x_TXC0_TOGGLE);
	} else {
		usbn960x->rxfifo_to_ep[idx] = ep;
		ep->regs = (USBN960x_RXD0 - 1) + (idx << 3);
	}

	/* TODO: 0x0f -> header */
	board_usbn960x_write(ep->regs, (ep->addr & 0x0f) | USBN960x_EPC1_EP_EN);
}

void usbn960x_stall_ep(void *_ep)
{
	usbn960x_ep_t *ep = _ep;
	putck('S');

	uint8_t epc0 = board_usbn960x_read(ep->regs);
	board_usbn960x_write(ep->regs, epc0 | USBN960x_EPC0_STALL);
	/* TODO: muss hier ueberhaupt etwas emacht werden? TXC bei RX register? nur stall + en? */
	board_usbn960x_write(ep->regs + 3, USBN960x_TXC_TOGGLE | USBN960x_TXC_LAST | USBN960x_TXC_TX_EN);
}


