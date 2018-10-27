
#ifndef __usb_h__
#define __usb_h__

#include <stdint.h>	/* uint*_t */
#include <stdlib.h>

/* standard request codes */
#define USB_SRC_GET_STATUS					0x00
#define USB_SRC_CLEAR_FEATURE				0x01
#define USB_SRC_SET_FEATURE					0x03
#define USB_SRC_SET_ADDRESS					0x05
#define USB_SRC_GET_DESCRIPTOR				0x06
#define USB_SRC_SET_DESCRIPTOR				0x07
#define USB_SRC_GET_CONFIGURATION			0x08
#define USB_SRC_SET_CONFIGURATION			0x09
#define USB_SRC_GET_INTERFACE				0x0a
#define USB_SRC_SET_INTERFACE				0x0b
#define USB_SRC_SYNCH_FRAME					0x0c

/* descriptor types */
#define USB_DT_DEVICE						0x01
#define USB_DT_CONFIGURATION				0x02
#define USB_DT_STRING						0x03
#define USB_DT_INTERFACE					0x04
#define USB_DT_ENDPOINT						0x05
#define USB_DT_DEVICE_QUALIFIER				0x06
#define USB_DT_OTHER_SPEED_CONFIGURATION	0x07
#define USB_DT_INTERFACE_POWER				0x08

#define USB_DT_INTERFACE_ASSOCIATION		0x0b


/* device classes (incomplete) */
#define USB_DC_PER_INTERFACE				0x00
#define USB_DC_AUDIO						0x01
#define USB_DC_COMMUNICATION_DEVICE			0x02
#define USB_DC_HID							0x03
#define USB_DC_MASS_STORAGE					0x08
#define USB_DC_HUB							0x09
#define USB_DC_CDC_DATA						0x0a
#define USB_DC_VENDOR_SPEC					0xff

#define USB_DSC_UNDEFINED					0x00
#define USB_DSC_AUDIOCONTROL				0x01
#define USB_DSC_AUDIOSTREAMING				0x02

#define USB_DSC_ACM							0x02
#define USB_DSC_EEM							0x0c

#define USB_DT_CS_INTERFACE					0x24
#define USB_DT_CS_ENDPOINT					0x25

#define USB_DST_HEADER						0x00
#define USB_DST_CALL_MANAGEMENT				0x01
#define USB_DST_ACM							0x02
#define USB_DST_UNION						0x06

#define USB_EP_XFER_MASK					0x03
#define USB_EP_XFER_CONTROL					0
#define USB_EP_XFER_ISOC					1
#define USB_EP_XFER_BULK					2
#define USB_EP_XFER_INT						3
#define USB_EP_DIR_IN						(1 << 7)

#define USB_CONFIG_ATT_SELFPOWER			(1 << 6)

#define USB_REQ_TYPE_RECIPIENT_MASK			(0x1f << 0)
#define USB_REQ_TYPE_RECIPIENT_DEVICE			(0x00 << 0)
#define USB_REQ_TYPE_RECIPIENT_INTERFACE			(0x01 << 0)
#define USB_REQ_TYPE_RECIPIENT_ENDPOINT			(0x02 << 0)
#define USB_REQ_TYPE_RECIPIENT_OTHER			(0x03 << 0)

#define USB_REQ_TYPE_MASK					(0x03 << 5)
#define USB_REQ_TYPE_STANDARD				(0x00 << 5)
#define USB_REQ_TYPE_CLASS					(0x01 << 5)
#define USB_REQ_TYPE_VENDOR					(0x02 << 5)

#define USB_REQ_DIR_OUT						0
#define USB_REQ_DIR_IN						(1 << 7)

typedef struct _usb_setup_t
{
	uint8_t bmRequestType;		/* direction, type, recipient */
	uint8_t bRequest;
	uint16_t wValue;
	uint16_t wIndex;
	uint16_t wLength;
} __attribute__ ((packed)) usb_setup_t;

typedef struct _usb_buffer_t {
	size_t size;
	size_t valid;
	unsigned int pos;
	void *data;
} usb_buffer_t;

#endif /* __usb_h__ */
