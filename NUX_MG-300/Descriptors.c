/*
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2015  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaims all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *
 *  USB Device Descriptors, for library use when in USB device mode. Descriptors are special
 *  computer-readable structures which the host requests upon device enumeration, to determine
 *  the device's capabilities and functions.
 */

#include "Descriptors.h"

/** Device descriptor structure. This descriptor, located in FLASH memory, describes the overall
 *  device characteristics, including the supported USB version, control endpoint size and the
 *  number of device configurations. The descriptor is read out by the USB host when the enumeration
 *  process begins.
 */
const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	.Header                 = {.Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},

	.USBSpecification       = VERSION_BCD(2,0,0),
	.Class                  = USB_CSCP_IADDeviceClass,
	.SubClass               = 2,
	.Protocol               = 1,

	.Endpoint0Size          = 64,

	.VendorID               = 0x1FC9,
	.ProductID              = 0x8260,
	.ReleaseNumber          = VERSION_BCD(1,0,0),

	.ManufacturerStrIndex   = STRING_ID_Manufacturer,
	.ProductStrIndex        = STRING_ID_Product,
	.SerialNumStrIndex      = 3,

	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

/** Configuration descriptor structure. This descriptor, located in FLASH memory, describes the usage
 *  of the device in one of its supported configurations, including information about any device interfaces
 *  and endpoints. The descriptor is read out by the USB host during the enumeration process when selecting
 *  a configuration so that the host may correctly communicate with the USB device.
 */
const USB_Descriptor_Configuration_t PROGMEM ConfigurationDescriptor =
{
	.Config =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Configuration_Header_t), .Type = DTYPE_Configuration},

			.TotalConfigurationSize   = sizeof(USB_Descriptor_Configuration_t),
			.TotalInterfaces          = 4,

			.ConfigurationNumber      = 1,
			.ConfigurationStrIndex    = NO_DESCRIPTOR,

			.ConfigAttributes         = (USB_CONFIG_ATTR_RESERVED | USB_CONFIG_ATTR_SELFPOWERED),

			.MaxPowerConsumption      = USB_CONFIG_POWER_MA(2)
		},
	.Interface_Association = 
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_Association_t), .Type = DTYPE_InterfaceAssociation},
			.FirstInterfaceIndex      = 0,
			.TotalInterfaces          = 3,
			.Class                    = 1,
			.SubClass                 = 0,
			.Protocol                 = 0x20,
			.IADStrIndex              = 0,
		},
/* USB Audio Control */
	.Audio_ControlInterface =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_AudioControl,
			.AlternateSetting         = 0,

			.TotalEndpoints           = 0,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_ControlSubclass,
			.Protocol                 = 0x20,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},

	.Audio_ControlInterface_SPC =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Interface_AC_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_Header,

			.ACSpecification          = VERSION_BCD(2,0,0),
			.Category                 = 8,
			.TotalLength              = offsetof(USB_Descriptor_Configuration_t, Audio_StreamInterface1) - offsetof(USB_Descriptor_Configuration_t, Audio_ControlInterface_SPC),
			.Controls                 = 0,
		},
//ClockSource
	.Audio_ControlInterface_SPC1 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_ClockSource_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_ClockSource,

			.ClockID                  = 0x29,
			.Attributes               = 0x03,
			.Controls                 = 0x07,
			.AssocTerminal            = 0,
			.ClockSource              = 0,
		},
//ClockSelector
	.Audio_ControlInterface_SPC2 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_ClockSelector_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_ClockSelector,

			.ClockID                  = 0x28,
			.NrInPins                 = 0x01,
			.CSourceID                = {0x29},
			.Controls                 = 3,
			.ClockSource              = 0,
		},
//Input Terminal
	.Audio_ControlInterface_SPC3 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_InputTerminal_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_InputTerminal,

			.TerminalID               = 2,
			.TerminalType             = 0x0101,
			.AssocTerminal            = 0,
			.CSourceID                = 0x28,
			.TotalChannels            = 2,
			.ChannelConfig            = 0x00000000,
			.ChannelStrIndex          = 0,
			.Controls                 = 0x0000,
			.TerminalStrIndex         = 0,
		},
//Feature
	.Audio_ControlInterface_SPC4 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Feature_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_Feature,

			.UnitID                   = 0x0a,
			.SourceID                 = 0x02,
			.Controls                = {CPU_TO_LE32(0x0000000f), CPU_TO_LE32(0x0000000f), CPU_TO_LE32(0x0000000f)},
			.Feature              = 0,
		},
//Output Terminal
	.Audio_ControlInterface_SPC5 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_OutputTerminal_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_OutputTerminal,

			.TerminalID               = 0x14,
			.TerminalType             = 0x0301,
			.AssocTerminal            = 0,
			.SourceID                 = 0x0a,
			.CSourceID                = 0x28,
			.Controls                 = 0x0000,
			.TerminalStrIndex         = 0,
		},
//Input Terminal
	.Audio_ControlInterface_SPC6 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_InputTerminal_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_InputTerminal,

			.TerminalID               = 1,
			.TerminalType             = 0x0201,
			.AssocTerminal            = 0,
			.CSourceID                = 0x28,
			.TotalChannels            = 2,
			.ChannelConfig            = 0x00000000,
			.ChannelStrIndex          = 0,
			.Controls                 = 0x0000,
			.TerminalStrIndex         = 0,
		},
		//Output Terminal
	.Audio_ControlInterface_SPC7 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_OutputTerminal_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO2_DSUBTYPE_CSInterface_OutputTerminal,

			.TerminalID               = 0x16,
			.TerminalType             = 0x0101,
			.AssocTerminal            = 0,
			.SourceID                 = 0x02,
			.CSourceID                = 0x28,
			.Controls                 = 0x0000,
			.TerminalStrIndex         = 0,
		},
/* USB Audio Streaming #1 */
//Audio1
	.Audio_StreamInterface1 =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_AudioStream1,
			.AlternateSetting         = 0,

			.TotalEndpoints           = 0,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_AudioStreamingSubclass,
			.Protocol                 = 0x20,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},
	.Audio_StreamInterface1alt =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_AudioStream1,
			.AlternateSetting         = 1,

			.TotalEndpoints           = 2,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_AudioStreamingSubclass,
			.Protocol                 = 0x20,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},
	.Audio_StreamInterface1_SPC = 
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Interface_AS_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_General,

			.TerminalLink             = 0x02,
			.Control                  = 0,
			.FormatType               = 1,
			.Formats                  = 0x00000001,
			.NrChannles               = 2,
			.ChannleConfig            = 0x00000000,
			.ChannelNames             = 0,
		},
	.Audio_StreamInterface1_SPC1 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Type3_Format_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_FormatType,

			.FormatType               = 1,
			.SubslotSize              = 4,
			.BitResolution            = 0x18,
		},
	.Audio_StreamOutEndpoint =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			.EndpointAddress          = (ENDPOINT_DIR_OUT | 1),
			.Attributes               = (EP_TYPE_ISOCHRONOUS | ENDPOINT_ATTR_ASYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize             = 600,
			.PollingIntervalMS        = 4,
		},
	.Audio_StreamIsoAudioDataEndpoint =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_IsoAudioData_Endpoint_t), .Type = AUDIO_DTYPE_CSEndpoint},
			.Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General, 
			.Attributes               = 0,
			.Controls                 = 0,
			.LockDelayUnits           = 0,
			.LockDelay                = 0x0000,
		},
	.Audio_StreamInEndpoint =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			.EndpointAddress          = (ENDPOINT_DIR_IN | 1),
			.Attributes               = (EP_TYPE_ISOCHRONOUS | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_FEEDBACK),
			.EndpointSize             = 4,
			.PollingIntervalMS        = 4,
		},
/* USB Audio Streaming #2 */
//Audio2
	.Audio_StreamInterface2 =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_AudioStream2,
			.AlternateSetting         = 0,

			.TotalEndpoints           = 0,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_AudioStreamingSubclass,
			.Protocol                 = 0x20,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},
	.Audio_StreamInterface2alt =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_AudioStream2,
			.AlternateSetting         = 1,

			.TotalEndpoints           = 1,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_AudioStreamingSubclass,
			.Protocol                 = 0x20,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},
	.Audio_StreamInterface2_SPC = 
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Interface_AS_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_General,

			.TerminalLink             = 0x16,
			.Control                  = 0,
			.FormatType               = 1,
			.Formats                  = 0x00000001,
			.NrChannles               = 2,
			.ChannleConfig            = 0x00000000,
			.ChannelNames             = 0,
		},
	.Audio_StreamInterface2_SPC1 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_Type3_Format_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_FormatType,

			.FormatType               = 1,
			.SubslotSize              = 4,
			.BitResolution            = 0x18,
		},
	.Audio_StreamInEndpoint2 =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Endpoint_t), .Type = DTYPE_Endpoint},
			.EndpointAddress          = (ENDPOINT_DIR_IN | 2),
			.Attributes               = (EP_TYPE_ISOCHRONOUS | ENDPOINT_ATTR_ASYNC | ENDPOINT_USAGE_DATA),
			.EndpointSize             = 600,
			.PollingIntervalMS        = 4,
		},
	.Audio_StreamIsoAudioDataEndpoint2 =
		{
			.Header                   = {.Size = sizeof(USB_Audio2_Descriptor_IsoAudioData_Endpoint_t), .Type = AUDIO_DTYPE_CSEndpoint},
			.Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General, 
			.Attributes               = 0,
			.Controls                 = 0,
			.LockDelayUnits           = 0,
			.LockDelay                = 0x0000,
		},

//MIDI
	.MIDI_StreamInterface =
		{
			.Header                   = {.Size = sizeof(USB_Descriptor_Interface_t), .Type = DTYPE_Interface},

			.InterfaceNumber          = INTERFACE_ID_MidiStream,
			.AlternateSetting         = 0,

			.TotalEndpoints           = 2,

			.Class                    = AUDIO_CSCP_AudioClass,
			.SubClass                 = AUDIO_CSCP_MIDIStreamingSubclass,
			.Protocol                 = AUDIO_CSCP_StreamingProtocol,

			.InterfaceStrIndex        = NO_DESCRIPTOR
		},

	.MIDI_StreamInterface_SPC =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_AudioInterface_AS_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_General,

			.AudioSpecification       = VERSION_BCD(1,0,0),

			.TotalLength              = (sizeof(USB_Descriptor_Configuration_t) -
			                             offsetof(USB_Descriptor_Configuration_t, MIDI_StreamInterface_SPC))
		},

	.MIDI_In_Jack_Emb =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_InputJack_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_InputTerminal,

			.JackType                 = MIDI_JACKTYPE_Embedded,
			.JackID                   = 0x01,

			.JackStrIndex             = NO_DESCRIPTOR
		},

	.MIDI_In_Jack_Ext =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_InputJack_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_InputTerminal,

			.JackType                 = MIDI_JACKTYPE_External,
			.JackID                   = 0x02,

			.JackStrIndex             = NO_DESCRIPTOR
		},

	.MIDI_Out_Jack_Emb =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_OutputJack_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,

			.JackType                 = MIDI_JACKTYPE_Embedded,
			.JackID                   = 0x03,

			.NumberOfPins             = 1,
			.SourceJackID             = {0x02},
			.SourcePinID              = {0x01},

			.JackStrIndex             = NO_DESCRIPTOR
		},

	.MIDI_Out_Jack_Ext =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_OutputJack_t), .Type = AUDIO_DTYPE_CSInterface},
			.Subtype                  = AUDIO_DSUBTYPE_CSInterface_OutputTerminal,

			.JackType                 = MIDI_JACKTYPE_External,
			.JackID                   = 0x04,

			.NumberOfPins             = 1,
			.SourceJackID             = {0x01},
			.SourcePinID              = {0x01},

			.JackStrIndex             = NO_DESCRIPTOR
		},

	.MIDI_In_Jack_Endpoint =
		{
			.Endpoint =
				{
					.Header              = {.Size = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t), .Type = DTYPE_Endpoint},

					.EndpointAddress     = (ENDPOINT_DIR_OUT | 4),
					.Attributes          = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
					.EndpointSize        = 256,
					.PollingIntervalMS   = 0x00
				},

			.Refresh                  = 0,
			.SyncEndpointNumber       = 0
		},

	.MIDI_In_Jack_Endpoint_SPC =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t), .Type = AUDIO_DTYPE_CSEndpoint},
			.Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General,

			.TotalEmbeddedJacks       = 0x01,
			.AssociatedJackID         = {0x01}
		},

	.MIDI_Out_Jack_Endpoint =
		{
			.Endpoint =
				{
					.Header              = {.Size = sizeof(USB_Audio_Descriptor_StreamEndpoint_Std_t), .Type = DTYPE_Endpoint},

					.EndpointAddress     = (ENDPOINT_DIR_IN | 3),
					.Attributes          = (EP_TYPE_BULK | ENDPOINT_ATTR_NO_SYNC | ENDPOINT_USAGE_DATA),
					.EndpointSize        = 256,
					.PollingIntervalMS   = 0x00
				},

			.Refresh                  = 0,
			.SyncEndpointNumber       = 0
		},

	.MIDI_Out_Jack_Endpoint_SPC =
		{
			.Header                   = {.Size = sizeof(USB_MIDI_Descriptor_Jack_Endpoint_t), .Type = AUDIO_DTYPE_CSEndpoint},
			.Subtype                  = AUDIO_DSUBTYPE_CSEndpoint_General,

			.TotalEmbeddedJacks       = 0x01,
			.AssociatedJackID         = {0x03}
		}
};

/** Language descriptor structure. This descriptor, located in FLASH memory, is returned when the host requests
 *  the string descriptor with index 0 (the first index). It is actually an array of 16-bit integers, which indicate
 *  via the language ID table available at USB.org what languages the device supports for its string descriptors.
 */
const USB_Descriptor_String_t PROGMEM LanguageString = USB_STRING_DESCRIPTOR_ARRAY(LANGUAGE_ID_ENG);

/** Manufacturer descriptor string. This is a Unicode string containing the manufacturer's details in human readable
 *  form, and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ManufacturerString = USB_STRING_DESCRIPTOR(L"NUX");

/** Product descriptor string. This is a Unicode string containing the product's details in human readable form,
 *  and is read out upon request by the host when the appropriate string ID is requested, listed in the Device
 *  Descriptor.
 */
const USB_Descriptor_String_t PROGMEM ProductString = USB_STRING_DESCRIPTOR(L"NUX MG-300 AUDIO");

/** This function is called by the library when in device mode, and must be overridden (see library "USB Descriptors"
 *  documentation) by the application code so that the address and size of a requested descriptor can be given
 *  to the USB library. When the device receives a Get Descriptor request on the control endpoint, this function
 *  is called so that the descriptor details can be passed back and the appropriate descriptor sent back to the
 *  USB host.
 */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
                                    const uint16_t wIndex,
                                    const void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	const void* Address = NULL;
	uint16_t    Size    = NO_DESCRIPTOR;

	switch (DescriptorType)
	{
		case DTYPE_Device:
			Address = &DeviceDescriptor;
			Size    = sizeof(USB_Descriptor_Device_t);
			break;
		case DTYPE_Configuration:
			Address = &ConfigurationDescriptor;
			Size    = sizeof(USB_Descriptor_Configuration_t);
			break;
		case DTYPE_String:
			switch (DescriptorNumber)
			{
				case STRING_ID_Language:
					Address = &LanguageString;
					Size    = pgm_read_byte(&LanguageString.Header.Size);
					break;
				case STRING_ID_Manufacturer:
					Address = &ManufacturerString;
					Size    = pgm_read_byte(&ManufacturerString.Header.Size);
					break;
				case STRING_ID_Product:
					Address = &ProductString;
					Size    = pgm_read_byte(&ProductString.Header.Size);
					break;
			}

			break;
	}

	*DescriptorAddress = Address;
	return Size;
}

