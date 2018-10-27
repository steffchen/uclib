
#include "usb_descr.h"

#include "usb.h"

#include <stdint.h>		/* uint*_t */
#include <stdlib.h>		/* size_t / malloc() */
#include <string.h>		/* strlen() */

usb_string_descriptor_t *usb_alloc_string_desc(const char *str)
{
	usb_string_descriptor_t *desc;
	size_t string_length = strlen(str);
	size_t desc_length = sizeof(usb_string_descriptor_t) + 2 * string_length;
	size_t n;

	desc = (usb_string_descriptor_t *)malloc(desc_length);
	if (desc != NULL) {
		desc->bDescriptorType = USB_DT_STRING;
		desc->bLength = desc_length;

		/* since the memory behind desc is allocated with malloc, it
		 * should be correctly aligned, hence we can safely use this cast */
		for (n = 0; n < string_length; n++)
			((uint16_t *)desc->bString)[n] = str[n];
	}

	return desc;
}

void usb_descr_for_each_ep(usb_configuration_descriptor_t *config_descr,
		void (*op)(usb_endpoint_descriptor_t *, void *), void *ctx)
{
	usb_descriptor_header_t *descr = (usb_descriptor_header_t *)config_descr;
	uint16_t length = config_descr->wTotalLength;

	while ((uint8_t *)descr - (uint8_t *)config_descr < length) {
		if (descr->bDescriptorType == USB_DT_ENDPOINT)
			op((usb_endpoint_descriptor_t *)descr, ctx);
		descr = (usb_descriptor_header_t *)((uint8_t *)descr + descr->bLength);
	}
}
