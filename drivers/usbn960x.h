/*
 * usbn960x.h
 *
 *  Created on: Dec 14, 2017
 *      Author: steff
 */

#ifndef USBN960X_H_
#define USBN960X_H_

#include <usb/usb_function.h>

#include <stdint.h>

#define USBN960x_CKI	48000000UL

#define USBN960x_MCNTRL	0x00
#define USBN960x_CCONF	0x01
#define USBN960x_FAR	0x04
#define USBN960x_NFSR	0x05
#define USBN960x_MAEV	0x06
#define USBN960x_MAMSK	0x07
#define USBN960x_ALTEV	0x08
#define USBN960x_ALTMSK	0x09
#define USBN960x_TXEV	0x0a
#define USBN960x_TXMSK	0x0b
#define USBN960x_RXEV	0x0c
#define USBN960x_RXMSK	0x0d
#define USBN960x_NAKEV	0x0e
#define USBN960x_NAKMSK	0x0f
#define USBN960x_EPC0	0x20
#define USBN960x_TXD0	0x21
#define USBN960x_TXS0	0x22
#define USBN960x_TXC0	0x23
#define USBN960x_RXD0	0x25
#define USBN960x_RXS0	0x26
#define USBN960x_RXC0	0x27
#define USBN960x_EPC1	0x28
#define USBN960x_TXD1	0x29
#define USBN960x_TXS1	0x2a
#define USBN960x_TXC1	0x2b
#define USBN960x_EPC2	0x2c
#define USBN960x_RXD1	0x2d
#define USBN960x_RXS1	0x2e
#define USBN960x_RXC1	0x2f
#define USBN960x_EPC3	0x30
#define USBN960x_TXD2	0x31
#define USBN960x_TXS2	0x32
#define USBN960x_TXC2	0x33
#define USBN960x_TXS3	0x3a

#define USBN960x_MCNTRL_SRST_Msk	(1 << USBN960x_MCNTRL_SRST_Pos)
#define USBN960x_MCNTRL_SRST		USBN960x_MCNTRL_SRST_Msk
#define USBN960x_MCNTRL_SRST_Pos	0U
#define USBN960x_MCNTRL_VGE_Msk		(1 << USBN960x_MCNTRL_VGE_Pos)
#define USBN960x_MCNTRL_VGE			USBN960x_MCNTRL_VGE_Msk
#define USBN960x_MCNTRL_VGE_Pos		2U
#define USBN960x_MCNTRL_NAT_Msk		(1 << USBN960x_MCNTRL_NAT_Pos)
#define USBN960x_MCNTRL_NAT			USBN960x_MCNTRL_NAT_Msk
#define USBN960x_MCNTRL_NAT_Pos		3U
#define USBN960x_MCNTRL_INTOC_Msk	(3 << USBN960x_MCNTRL_INTOC_Pos)
#define USBN960x_MCNTRL_INTOC		USBN960x_MCNTRL_INTOC_Msk
#define USBN960x_MCNTRL_INTOC_Pos	6U

#define USBN960x_FAR_AD_EN_Msk		(1 << USBN960x_FAR_AD_EN_Pos)
#define USBN960x_FAR_AD_EN			USBN960x_FAR_AD_EN_Msk
#define USBN960x_FAR_AD_EN_Pos		7U

#define USBN960x_NFSR_NFS_Msk		(3 << USBN960x_NFSR_NFS_Pos)
#define USBN960x_NFSR_NFS			USBN960x_NFSR_NFS_Msk
#define USBN960x_NFSR_NFS_Pos		0U

#define USBN960x_MAEV_WARN_Msk		(1 << USBN960x_MAEV_WARN_Pos)
#define USBN960x_MAEV_WARN			USBN960x_MAEV_WARN_Msk
#define USBN960x_MAEV_WARN_Pos		0U
#define USBN960x_MAEV_ALT_Msk		(1 << USBN960x_MAEV_ALT_Pos)
#define USBN960x_MAEV_ALT			USBN960x_MAEV_ALT_Msk
#define USBN960x_MAEV_ALT_Pos		1U
#define USBN960x_MAEV_TX_EV_Msk		(1 << USBN960x_MAEV_TX_EV_Pos)
#define USBN960x_MAEV_TX_EV			USBN960x_MAEV_TX_EV_Msk
#define USBN960x_MAEV_TX_EV_Pos		2U
#define USBN960x_MAEV_FRAME_Msk		(1 << USBN960x_MAEV_FRAME_Pos)
#define USBN960x_MAEV_FRAME			USBN960x_MAEV_FRAME_Msk
#define USBN960x_MAEV_FRAME_Pos		3U
#define USBN960x_MAEV_NAK_Msk		(1 << USBN960x_MAEV_NAK_Pos)
#define USBN960x_MAEV_NAK			USBN960x_MAEV_NAK_Msk
#define USBN960x_MAEV_NAK_Pos		4U
#define USBN960x_MAEV_ULD_Msk		(1 << USBN960x_MAEV_ULD_Pos)
#define USBN960x_MAEV_ULD			USBN960x_MAEV_ULD_Msk
#define USBN960x_MAEV_ULD_Pos		5U
#define USBN960x_MAEV_RX_EV_Msk		(1 << USBN960x_MAEV_RX_EV_Pos)
#define USBN960x_MAEV_RX_EV			USBN960x_MAEV_RX_EV_Msk
#define USBN960x_MAEV_RX_EV_Pos		6U
#define USBN960x_MAEV_INTR_Msk		(1 << USBN960x_MAEV_INTR_Pos)
#define USBN960x_MAEV_INTR			USBN960x_MAEV_INTR_Msk
#define USBN960x_MAEV_INTR_Pos		7U

#define USBN960x_MAMSK_ALT_Msk		(1 << USBN960x_MAMSK_ALT_Pos)
#define USBN960x_MAMSK_ALT			USBN960x_MAMSK_ALT_Msk
#define USBN960x_MAMSK_ALT_Pos		1U

#define USBN960x_ALTEV_RESET_Msk	(1 << USBN960x_ALTEV_RESET_Pos)
#define USBN960x_ALTEV_RESET		USBN960x_ALTEV_RESET_Msk
#define USBN960x_ALTEV_RESET_Pos	6U

#define USBN960x_ALTMSK_RESET_Msk	(1 << USBN960x_ALTMSK_RESET_Pos)
#define USBN960x_ALTMSK_RESET		USBN960x_ALTMSK_RESET_Msk
#define USBN960x_ALTMSK_RESET_Pos	6U

#define USBN960x_TXEV_TXFIFO0_Msk	(1 << USBN960x_TXEV_TXFIFO0_Pos)
#define USBN960x_TXEV_TXFIFO0		USBN960x_TXEV_TXFIFO0_Msk
#define USBN960x_TXEV_TXFIFO0_Pos	0U
#define USBN960x_TXEV_TXFIFO1_Msk	(1 << USBN960x_TXEV_TXFIFO1_Pos)
#define USBN960x_TXEV_TXFIFO1		USBN960x_TXEV_TXFIFO1_Msk
#define USBN960x_TXEV_TXFIFO1_Pos	1U
#define USBN960x_TXEV_TXFIFO2_Msk	(1 << USBN960x_TXEV_TXFIFO2_Pos)
#define USBN960x_TXEV_TXFIFO2		USBN960x_TXEV_TXFIFO2_Msk
#define USBN960x_TXEV_TXFIFO2_Pos	2U
#define USBN960x_TXEV_TXFIFO3_Msk	(1 << USBN960x_TXEV_TXFIFO3_Pos)
#define USBN960x_TXEV_TXFIFO3		USBN960x_TXEV_TXFIFO3_Msk
#define USBN960x_TXEV_TXFIFO3_Pos	3U

#define USBN960x_TXMSK_TXFIFO0_Msk	(1 << USBN960x_TXMSK_TXFIFO0_Pos)
#define USBN960x_TXMSK_TXFIFO0		USBN960x_TXMSK_TXFIFO0_Msk
#define USBN960x_TXMSK_TXFIFO0_Pos	0U
#define USBN960x_TXMSK_TXFIFO1_Msk	(1 << USBN960x_TXMSK_TXFIFO1_Pos)
#define USBN960x_TXMSK_TXFIFO1		USBN960x_TXMSK_TXFIFO1_Msk
#define USBN960x_TXMSK_TXFIFO1_Pos	1U
#define USBN960x_TXMSK_TXFIFO2_Msk	(1 << USBN960x_TXMSK_TXFIFO2_Pos)
#define USBN960x_TXMSK_TXFIFO2		USBN960x_TXMSK_TXFIFO2_Msk
#define USBN960x_TXMSK_TXFIFO2_Pos	2U

#define USBN960x_RXEV_RXFIFO0_Msk	(1 << USBN960x_RXEV_RXFIFO0_Pos)
#define USBN960x_RXEV_RXFIFO0		USBN960x_RXEV_RXFIFO0_Msk
#define USBN960x_RXEV_RXFIFO0_Pos	0U
#define USBN960x_RXEV_RXFIFO1_Msk	(1 << USBN960x_RXEV_RXFIFO1_Pos)
#define USBN960x_RXEV_RXFIFO1		USBN960x_RXEV_RXFIFO1_Msk
#define USBN960x_RXEV_RXFIFO1_Pos	1U

#define USBN960x_RXMSK_RXFIFO0_Msk	(1 << USBN960x_RXMSK_RXFIFO0_Pos)
#define USBN960x_RXMSK_RXFIFO0		USBN960x_RXMSK_RXFIFO0_Msk
#define USBN960x_RXMSK_RXFIFO0_Pos	0U
#define USBN960x_RXMSK_RXFIFO1_Msk	(1 << USBN960x_RXMSK_RXFIFO1_Pos)
#define USBN960x_RXMSK_RXFIFO1		USBN960x_RXMSK_RXFIFO1_Msk
#define USBN960x_RXMSK_RXFIFO1_Pos	1U

#define USBN960x_EPC0_DEF_Msk		(1 << USBN960x_EPC0_DEF_Pos)
#define USBN960x_EPC0_DEF			USBN960x_EPC0_DEF_Msk
#define USBN960x_EPC0_DEF_Pos		6U
#define USBN960x_EPC0_STALL_Msk		(1 << USBN960x_EPC0_STALL_Pos)
#define USBN960x_EPC0_STALL			USBN960x_EPC0_STALL_Msk
#define USBN960x_EPC0_STALL_Pos		7U

#define USBN960x_TXS0_TX_DONE_Msk		(1 << USBN960x_TXS0_TX_DONE_Pos)
#define USBN960x_TXS0_TX_DONE			USBN960x_TXS0_TX_DONE_Msk
#define USBN960x_TXS0_TX_DONE_Pos		5U
#define USBN960x_TXS0_ACK_STAT_Msk		(1 << USBN960x_TXS0_ACK_STAT_Pos)
#define USBN960x_TXS0_ACK_STAT			USBN960x_TXS0_ACK_STAT_Msk
#define USBN960x_TXS0_ACK_STAT_Pos		6U

#define USBN960x_TXC_TX_EN_Msk		(1 << USBN960x_TXC_TX_EN_Pos)
#define USBN960x_TXC_TX_EN			USBN960x_TXC_TX_EN_Msk
#define USBN960x_TXC_TX_EN_Pos		0U
#define USBN960x_TXC_LAST_Msk		(1 << USBN960x_TXC_LAST_Pos)
#define USBN960x_TXC_LAST			USBN960x_TXC_LAST_Msk
#define USBN960x_TXC_LAST_Pos		1U
#define USBN960x_TXC_TOGGLE_Msk		(1 << USBN960x_TXC_TOGGLE_Pos)
#define USBN960x_TXC_TOGGLE			USBN960x_TXC_TOGGLE_Msk
#define USBN960x_TXC_TOGGLE_Pos		2U

#define USBN960x_TXC0_TX_EN_Msk		(1 << USBN960x_TXC0_TX_EN_Pos)
#define USBN960x_TXC0_TX_EN			USBN960x_TXC0_TX_EN_Msk
#define USBN960x_TXC0_TX_EN_Pos		0U
#define USBN960x_TXC0_TOGGLE_Msk		(1 << USBN960x_TXC0_TOGGLE_Pos)
#define USBN960x_TXC0_TOGGLE			USBN960x_TXC0_TOGGLE_Msk
#define USBN960x_TXC0_TOGGLE_Pos		2U
#define USBN960x_TXC0_FLUSH_Msk		(1 << USBN960x_TXC0_FLUSH_Pos)
#define USBN960x_TXC0_FLUSH			USBN960x_TXC0_FLUSH_Msk
#define USBN960x_TXC0_FLUSH_Pos		3U

#define USBN960x_RXS0_RCOUNT_Msk		(15U << USBN960x_RXS0_RCOUNT_Pos)
#define USBN960x_RXS0_RCOUNT_Pos		0U
#define USBN960x_RXS0_RX_LAST_Msk		(1 << USBN960x_RXS0_RX_LAST_Pos)
#define USBN960x_RXS0_RX_LAST			USBN960x_RXS0_RX_LAST_Msk
#define USBN960x_RXS0_RX_LAST_Pos		4U
#define USBN960x_RXS0_SETUP_Msk		(1 << USBN960x_RXS0_SETUP_Pos)
#define USBN960x_RXS0_SETUP			USBN960x_RXS0_SETUP_Msk
#define USBN960x_RXS0_SETUP_Pos		6U

#define USBN960x_RXC0_RX_EN_Msk		(1 << USBN960x_RXC0_RX_EN_Pos)
#define USBN960x_RXC0_RX_EN			USBN960x_RXC0_RX_EN_Msk
#define USBN960x_RXC0_RX_EN_Pos		0U
#define USBN960x_RXC0_FLUSH_Msk		(1 << USBN960x_RXC0_FLUSH_Pos)
#define USBN960x_RXC0_FLUSH			USBN960x_RXC0_FLUSH_Msk
#define USBN960x_RXC0_FLUSH_Pos		3U

#define USBN960x_EPC1_EP_EN_Msk		(1 << USBN960x_EPC1_EP_EN_Pos)
#define USBN960x_EPC1_EP_EN			USBN960x_EPC1_EP_EN_Msk
#define USBN960x_EPC1_EP_EN_Pos		4U

#define USBN960x_EPC2_EP_EN_Msk		(1 << USBN960x_EPC2_EP_EN_Pos)
#define USBN960x_EPC2_EP_EN			USBN960x_EPC2_EP_EN_Msk
#define USBN960x_EPC2_EP_EN_Pos		4U

#define USBN960x_RXS1_RCOUNT_Msk	(15U << USBN960x_RXS1_RCOUNT_Pos)
#define USBN960x_RXS1_RCOUNT_Pos	0U
#define USBN960x_RXS1_RX_LAST_Msk		(1 << USBN960x_RXS1_RX_LAST_Pos)
#define USBN960x_RXS1_RX_LAST			USBN960x_RXS1_RX_LAST_Msk
#define USBN960x_RXS1_RX_LAST_Pos		4U

#define USBN960x_RXC1_RX_EN_Msk		(1 << USBN960x_RXC1_RX_EN_Pos)
#define USBN960x_RXC1_RX_EN			USBN960x_RXC1_RX_EN_Msk
#define USBN960x_RXC1_RX_EN_Pos		0U

#define USBN960x_EPC3_EP_EN_Msk		(1 << USBN960x_EPC3_EP_EN_Pos)
#define USBN960x_EPC3_EP_EN			USBN960x_EPC3_EP_EN_Msk
#define USBN960x_EPC3_EP_EN_Pos		4U

#define USBN960x_TXC2_TOGGLE_Msk		(1 << USBN960x_TXC2_TOGGLE_Pos)
#define USBN960x_TXC2_TOGGLE			USBN960x_TXC2_TOGGLE_Msk
#define USBN960x_TXC2_TOGGLE_Pos		2U
#define USBN960x_TXC2_FLUSH_Msk		(1 << USBN960x_TXC2_FLUSH_Pos)
#define USBN960x_TXC2_FLUSH			USBN960x_TXC2_FLUSH_Msk
#define USBN960x_TXC2_FLUSH_Pos		3U

void usbn960x_init(void);
void usbn960x_connect(void);

void usbn960x_handler(void);

void usbn960x_setup_receive(void *ep, uint8_t *buf, unsigned int size,
		usb_out_hdlr_t out_hdlr);
void usbn960x_setup_send(void *ep, usb_in_hdlr_t in_hdlr);
void usbn960x_receive_data(void *ep);
int usbn960x_send_data(void *ep, const uint8_t *data, unsigned int len);
void usbn960x_send_ack(void *ep);

int usbn960x_set_address(uint16_t addr);

void *usbn960x_alloc_ep(uint8_t iep, uint16_t ep_size);
void usbn960x_enable_ep(void *ep);
void usbn960x_stall_ep(void *ep);

#endif /* USBN960X_H_ */