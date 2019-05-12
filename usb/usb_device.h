
#ifndef __usb_device_h__
#define __usb_device_h__

#include "usb_descr.h"
#include "usb_request.h"

#include <stdint.h>

typedef void (*usb_out_hdlr_t)(void *ep, const uint8_t *data, unsigned int len);
typedef void (*usb_in_hdlr_t)(void *ep);

typedef struct _usb_interface_t {
	usb_request_hdlrs_t request_hdlrs;
} usb_interface_t;

typedef struct _usb_function_t {
	int (*init)(void);
	void (*configure)(void);

	const usb_interface_t * const *interfaces;
} usb_function_t;

typedef struct _usb_device_t {
	usb_configuration_descriptor_t *conf_desc;
	const usb_device_descriptor_t *device_desc;
	const usb_qualifier_descriptor_t *quali_desc;

	const usb_string_descriptor_t **string_descs;

	const usb_function_t * const *functions;
} usb_device_t;

usb_configuration_descriptor_t *usb_get_config_descr(void);
const usb_device_descriptor_t *usb_get_device_descr(void);
const usb_string_descriptor_t *usb_get_string(uint8_t index);
const usb_interface_t *usb_get_interface(unsigned int n);
int usb_set_configuration(uint8_t idx);

void usb_device_init(const usb_device_t *device);

#endif
