/*
 * usb.c
 *
 *  Created on: Oct 14, 2018
 *      Author: steff
 */

#include "usb_function.h"

#include "usb.h"
#include "usb_descr.h"

#include <stdint.h>
#include <stdlib.h>

static const usb_function_t *usb_function;

usb_configuration_descriptor_t *usb_get_config_descr(void)
{
	return usb_function->conf_desc;
}

const usb_device_descriptor_t *usb_get_device_descr(void)
{
	return usb_function->device_desc;
}

const usb_string_descriptor_t *usb_get_string(uint8_t index)
{
	const usb_string_descriptor_t * const *string = &usb_function->string_descs[0];
	while (index-- > 0 && *string != NULL)
		string++;
	return *string;
}

const usb_interface_t *usb_get_interface(unsigned int n)
{
	const usb_interface_t * const *interface = &usb_function->interfaces[0];
	while (n-- > 0 && *interface != NULL)
		interface++;
	return *interface;
}

int usb_set_configuration(uint8_t idx)
{
	const usb_interface_t *interface;
	int i = 0;

	while ((interface = usb_get_interface(i++)) != NULL)
		if (interface->configure != NULL)
			interface->configure();

	return 0;
}

void usb_function_init(const usb_function_t *function)
{
	const usb_interface_t *interface;
	int i = 0;

	usb_function = function;

	while ((interface = usb_get_interface(i++)) != NULL)
		if (interface->init != NULL)
			interface->init();
}
