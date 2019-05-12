/*
 * usb.c
 *
 *  Created on: Oct 14, 2018
 *      Author: steff
 */

#include "usb_device.h"

#include "usb.h"
#include "usb_descr.h"

#include <stdint.h>
#include <stdlib.h>

static const usb_device_t *usb_device;

usb_configuration_descriptor_t *usb_get_config_descr(void)
{
	return usb_device->conf_desc;
}

const usb_device_descriptor_t *usb_get_device_descr(void)
{
	return usb_device->device_desc;
}

const usb_string_descriptor_t *usb_get_string(uint8_t index)
{
	const usb_string_descriptor_t * const *string = &usb_device->string_descs[0];
	while (index-- > 0 && *string != NULL)
		string++;
	return *string;
}

const usb_interface_t *usb_get_interface(unsigned int n)
{
	const usb_function_t *const *func;

	for (func = &usb_device->functions[0]; *func != NULL; func++) {
		const usb_interface_t *const *iface;

		for (iface = &(*func)->interfaces[0]; *iface != NULL; iface++) {

			/* return n'th interface */
			if (n-- == 0)
				return *iface;
		}
	}

	return NULL;
}

int usb_set_configuration(uint8_t idx)
{
	const usb_function_t *const *func;

	for (func = &usb_device->functions[0]; *func != NULL; func++)
		if ((*func)->configure != NULL)
			(*func)->configure();

	return 0;
}

void usb_device_init(const usb_device_t *device)
{
	const usb_function_t *const *func;

	usb_device = device;

	for (func = &usb_device->functions[0]; *func != NULL; func++)
		if ((*func)->init != NULL)
			(*func)->init();
}
