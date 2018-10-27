
#ifndef __usb_descr_h__
#define __usb_descr_h__

#include <stdint.h>

#include "usb.h"

typedef struct _usb_decriptor_header_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
} __attribute__ ((packed)) usb_descriptor_header_t;

typedef struct _usb_configuration_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t wTotalLength;
	uint8_t bNumInterfaces;
	uint8_t bConfigurationValue;
	uint8_t iConfiguration;
	uint8_t bmAttributes;
	uint8_t bMaxPower;
} __attribute__ ((packed)) usb_configuration_descriptor_t;

typedef struct _usb_interface_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bInterfaceNumber;
	uint8_t bAlternateSetting;
	uint8_t bNumEndpoints;
	uint8_t bInterfaceClass;
	uint8_t bInterfaceSubClass;
	uint8_t bInterfaceProtocol;
	uint8_t iInterface;
} __attribute__ ((packed)) usb_interface_descriptor_t;

typedef struct _usb_endpoint_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
} __attribute__ ((packed)) usb_endpoint_descriptor_t;

struct usb_audio_endpoint_descriptor
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bEndpointAddress;
	uint8_t bmAttributes;
	uint16_t wMaxPacketSize;
	uint8_t bInterval;
	uint8_t bRefresh;
	uint8_t bSynchAddress;
} __attribute__ ((packed));


typedef struct _usb_string_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bString[];
} __attribute__ ((packed)) usb_string_descriptor_t;

typedef struct _usb_interface_association_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bFirstInterface;
	uint8_t bInterfaceCount;
	uint8_t bFunctionClass;
	uint8_t bFunctionSubClass;
	uint8_t bFunctionProtocol;
	uint8_t iFunction;
} __attribute__ ((packed)) usb_interface_association_descriptor_t;

typedef struct _usb_header_functional_descriptor_t
{
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint16_t bcdCDC;
} __attribute__ ((packed)) usb_header_functional_descriptor_t;

typedef struct _usb_call_management_functional_descriptor_t
{
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmCapabilities;
	uint8_t bDataInterface;
} __attribute__ ((packed)) usb_call_management_functional_descriptor_t;

typedef struct _usb_acm_functional_descriptor_t
{
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmCapabilities;
} __attribute__ ((packed)) usb_acm_functional_descriptor_t;

typedef struct _usb_union_interface_functional_descriptor_t
{
	uint8_t bFunctionLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bMasterInterface0;
	uint8_t bSlaveInterface0;
} __attribute__ ((packed)) usb_union_interface_functional_descriptor_t;

typedef struct _usb_class_specific_ac_interface_header_10_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint16_t bcdADC;
	uint16_t wTotalLength;
	uint8_t bInCollection;
	uint8_t baInterfaceNr[];
} __attribute__ ((packed)) usb_class_specific_ac_interface_header_10_t;

typedef struct _usb_class_specific_ac_interface_header_20_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint16_t bcdADC;
	uint8_t bCategory;
	uint16_t wTotalLength;
	uint8_t bmControls;
} __attribute__ ((packed)) usb_class_specific_ac_interface_header_20_t;

typedef struct _usb_clock_source_descriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bClockID;
	uint8_t bmAttributes;
	uint8_t bmControls;
	uint8_t bAssocTerminal;
	uint8_t iClockSource;
} __attribute__ ((packed)) usb_clock_source_descriptor_t;

struct uac1_input_terminal_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalID;
	uint16_t wTerminalType;
	uint8_t bAssocTerminal;
	uint8_t bNrChannels;
	uint16_t wChannelConfig;
	uint8_t iChannelNames;
	uint8_t iTerminal;
} __attribute__ ((packed));

typedef struct _usb_input_terminal_descriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalID;
	uint16_t wTerminalType;
	uint8_t bAssocTerminal;
	uint8_t bCSourceID;
	uint8_t bNrChannels;
	uint32_t bmChannelConfig;
	uint8_t iChannelNames;
	uint16_t bmControls;
	uint8_t iTerminal;
} __attribute__ ((packed)) usb_input_terminal_descriptor_t;

struct uac1_output_terminal_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalID;
	uint16_t wTerminalType;
	uint8_t bAssocTerminal;
	uint8_t bSourceID;
	uint8_t iTerminal;
} __attribute__ ((packed));

typedef struct _usb_output_terminal_descriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalID;
	uint16_t wTerminalType;
	uint8_t bAssocTerminal;
	uint8_t bSourceID;
	uint8_t bCSourceID;
	uint16_t bmControls;
	uint8_t iTerminal;
} __attribute__ ((packed)) usb_output_terminal_descriptor_t;

struct uac1_as_header_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalLink;
	uint8_t bDelay;
	uint16_t wFormatTag;
} __attribute__ ((packed));

typedef struct _usb_class_specific_as_interface_descriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bTerminalLink;
	uint8_t bmControls;
	uint8_t bFormatType;
	uint32_t bmFormats;
	uint8_t bNrChannels;
	uint32_t bmChannelConfig;
	uint8_t iChannelNames;

} __attribute__ ((packed)) usb_class_specific_as_interface_descriptor_t;

struct uac1_format_type_i_discrete_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bFormatType;
	uint8_t bNrChannels;
	uint8_t bSubframeSize;
	uint8_t bBitResolution;
	uint8_t bSamFreqType;
	uint8_t tSamFreq[];
} __attribute__ ((packed));

typedef struct _usb_format_type_i_decriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bFormatType;
	uint8_t bSubslotSize;
	uint8_t bBitResolution;
} __attribute__ ((packed)) usb_format_type_i_decriptor_t;

struct uac1_iso_endpoint_descriptor {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmAttributes;
	uint8_t bLockDelayUnits;
	uint16_t wLockDelay;
} __attribute__ ((packed));

typedef struct _usb_class_specific_as_iso_endpoint_descriptor_t {
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bDescriptorSubtype;
	uint8_t bmAttributes;
	uint8_t bmControls;
	uint8_t bLockDelayUnits;
	uint16_t wLockDelay;
} __attribute__ ((packed)) usb_class_specific_as_iso_endpoint_descriptor_t;

typedef struct _usb_device_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint16_t idVendor;
	uint16_t idProduct;
	uint16_t bcdDevice;
	uint8_t iManufacturer;
	uint8_t iProduct;
	uint8_t iSerialNumber;
	uint8_t bNumConfigurations;
} __attribute__ ((packed)) usb_device_descriptor_t;

typedef struct _usb_qualifier_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint16_t bcdUSB;
	uint8_t bDeviceClass;
	uint8_t bDeviceSubClass;
	uint8_t bDeviceProtocol;
	uint8_t bMaxPacketSize0;
	uint8_t bNumConfigurations;
	uint8_t bReserved;
} __attribute__ ((packed)) usb_qualifier_descriptor_t;

typedef struct _usb_hub_descriptor_t
{
	uint8_t bLength;
	uint8_t bDescriptorType;
	uint8_t bNbrPorts;
	uint16_t wHubCharacteristics;
	uint8_t bPwrOn2PwrGood;
	uint8_t bHubContrCurrent;
} __attribute__ ((packed)) usb_hub_descriptor_t;

static inline uint8_t usb_get_iep(const usb_endpoint_descriptor_t *ep_desc)
{
	return ep_desc->bEndpointAddress & 0x0f;
}

usb_string_descriptor_t *usb_alloc_string_desc(const char *str);
void usb_descr_for_each_ep(usb_configuration_descriptor_t *config_descr,
		void (*op)(usb_endpoint_descriptor_t *, void *), void *ctx);

#endif /* __usb_descr_h__ */
