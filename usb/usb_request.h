
#ifndef __usb_request_h__
#define __usb_request_h__

#include "usb.h"		/* usb_setup_t */

#include <stdint.h>

typedef int (*request_hdlr_t)(void *, const usb_setup_t *,
		const uint8_t *, unsigned int);

typedef struct _usb_request_hdlrs_t {
	request_hdlr_t standard_hdlr;
	request_hdlr_t class_hdlr;
	request_hdlr_t vendor_hdlr;
} usb_request_hdlrs_t;

int usb_request_handle(void *ep, const usb_setup_t *setup,
		const uint8_t *data, unsigned int len);

#endif
