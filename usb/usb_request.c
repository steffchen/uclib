
#include "usb_request.h"

#include "usb_descr.h"
#include "usb_device.h"

#include "board.h"

#include "usb.h"		/* usb_setup_t */

#include <stdint.h>

static int handle_get_descriptor(void *ep, const usb_setup_t *setup)
{
	uint8_t index = setup->wValue;
	uint8_t type = setup->wValue >> 8;
	uint16_t resp_size = setup->wLength;
	int rc = -1;

	switch (type) {
	case USB_DT_DEVICE: {
			const usb_device_descriptor_t *device_descr = usb_get_device_descr();

			if (resp_size > device_descr->bLength)
				resp_size = device_descr->bLength;
			rc = usb_send_data(ep, (uint8_t *)device_descr, resp_size);
		}
		break;
	case USB_DT_CONFIGURATION: {
			usb_configuration_descriptor_t *config_descr = usb_get_config_descr();
			if (resp_size > config_descr->wTotalLength)
				resp_size = config_descr->wTotalLength;
			rc = usb_send_data(ep, (uint8_t *)config_descr, resp_size);
		}
		break;
	case USB_DT_STRING: {
			const usb_string_descriptor_t *string = usb_get_string(index);
			if (string != NULL) {
				if (resp_size > string->bLength)
					resp_size = string->bLength;
				rc = usb_send_data(ep, (uint8_t *)string, resp_size);
			}
		}
		break;
	default:
		break;
	}

	return rc;
}

static int handle_standard_request(void *ep, const usb_setup_t *setup,
		const uint8_t *data, unsigned int len)
{
	int rc = -1;

	switch (setup->bRequest) {
	case USB_SRC_GET_DESCRIPTOR:
		rc = handle_get_descriptor(ep, setup);
		break;
	case USB_SRC_SET_ADDRESS:
		rc = usb_set_address(setup->wValue);
		break;
	case USB_SRC_SET_CONFIGURATION:
		rc = usb_set_configuration(setup->wValue);
		usb_send_ack(ep);
		break;
	case USB_SRC_SET_INTERFACE:
	default:
		break;
	}

	return rc;
}

static usb_request_hdlrs_t device_request_hdlrs = {
		.standard_hdlr = handle_standard_request,
};

int usb_request_handle(void *ep, const usb_setup_t *setup, const uint8_t *data,
		unsigned int len)
{
	const usb_request_hdlrs_t *request_hdlrs = NULL;
	const usb_interface_t *interface;
	int rc = -1;

	/* decode recipient */
	switch (setup->bmRequestType & USB_REQ_TYPE_RECIPIENT_MASK) {
	case USB_REQ_TYPE_RECIPIENT_DEVICE:
		request_hdlrs = &device_request_hdlrs;
		break;
	case USB_REQ_TYPE_RECIPIENT_INTERFACE:
		interface = usb_get_interface(setup->wIndex & 0x00ff);
		if (interface != NULL)
			request_hdlrs = &interface->request_hdlrs;
		break;
	case USB_REQ_TYPE_RECIPIENT_ENDPOINT:
	case USB_REQ_TYPE_RECIPIENT_OTHER:
	default:
		break;
	}

	if (request_hdlrs != NULL) {
		request_hdlr_t request_hdlr = NULL;

		/* decode request type */
		switch (setup->bmRequestType & USB_REQ_TYPE_MASK) {
		case USB_REQ_TYPE_STANDARD:
			request_hdlr = request_hdlrs->standard_hdlr;
			break;
		case USB_REQ_TYPE_CLASS:
			request_hdlr = request_hdlrs->class_hdlr;
			break;
		case USB_REQ_TYPE_VENDOR:
			request_hdlr = request_hdlrs->vendor_hdlr;
			break;
		default:
			break;
		}

		/* call handler, if any */
		if (request_hdlr != NULL)
			rc = request_hdlr(ep, setup, data, len);
	}

	return rc;
}

