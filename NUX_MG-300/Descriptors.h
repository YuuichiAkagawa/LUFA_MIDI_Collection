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
 *  Header file for Descriptors.c.
 */

#ifndef _DESCRIPTORS_H_
#define _DESCRIPTORS_H_

	/* Includes: */
		#include <LUFA/Drivers/USB/USB.h>

		#include <avr/pgmspace.h>

	/* Macros: */
		/** Endpoint address of the MIDI streaming data IN endpoint, for device-to-host data transfers. */
		#define MIDI_STREAM_IN_EPADDR       (ENDPOINT_DIR_IN  | 3)

		/** Endpoint address of the MIDI streaming data OUT endpoint, for host-to-device data transfers. */
		#define MIDI_STREAM_OUT_EPADDR      (ENDPOINT_DIR_OUT | 4)

		/** Endpoint size in bytes of the Audio isochronous streaming data IN and OUT endpoints. */
		#define MIDI_STREAM_EPSIZE          64
		/** Enum for the Audio class specific descriptor types. */

	/* Audio 2.0 */
		/** Audio class specific interface description subtypes, for the Audio Control interface. */
		enum Audio2_CSInterface_AC_SubTypes_t
		{
			AUDIO2_DSUBTYPE_CSInterface_Header         = 0x01, /**< Audio class specific control interface header. */
			AUDIO2_DSUBTYPE_CSInterface_InputTerminal  = 0x02, /**< Audio class specific control interface Input Terminal. */
			AUDIO2_DSUBTYPE_CSInterface_OutputTerminal = 0x03, /**< Audio class specific control interface Output Terminal. */
			AUDIO2_DSUBTYPE_CSInterface_Mixer          = 0x04, /**< Audio class specific control interface Mixer Unit. */
			AUDIO2_DSUBTYPE_CSInterface_Selector       = 0x05, /**< Audio class specific control interface Selector Unit. */
			AUDIO2_DSUBTYPE_CSInterface_Feature        = 0x06, /**< Audio class specific control interface Feature Unit. */
			AUDIO2_DSUBTYPE_CSInterface_Effect         = 0x07, /**< Audio class specific control interface Processing Unit. */
			AUDIO2_DSUBTYPE_CSInterface_Processing     = 0x08, /**< Audio class specific control interface Processing Unit. */
			AUDIO2_DSUBTYPE_CSInterface_Extension      = 0x09, /**< Audio class specific control interface Extension Unit. */
			AUDIO2_DSUBTYPE_CSInterface_ClockSource    = 0x0a, /**< Audio class specific control interface Clock source. */
			AUDIO2_DSUBTYPE_CSInterface_ClockSelector  = 0x0b, /**< Audio class specific control interface Clock selector. */
			AUDIO2_DSUBTYPE_CSInterface_ClockMultiplier= 0x0c, /**< Audio class specific control interface Clock multiplier. */
			AUDIO2_DSUBTYPE_CSInterface_SampleRateConv = 0x0d, /**< Audio class specific control interface Sample rate converter. */
		};
		/* Audio 2.0 AC Interface Header Descriptor */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   a value from the \ref Audio_CSInterface_AS_SubTypes_t enum.
			                                  */

			uint16_t                ACSpecification; /**< Binary Coded Decimal value, indicating the supported Audio Class specification version.
			                                          *
			                                          *   \see \ref VERSION_BCD() utility macro.
			                                          */
			uint8_t                 Category; /**< Total number of Audio Streaming interfaces linked to this Audio Control interface (must be 1). */
			uint16_t                TotalLength; /**< Total length of the Audio class-specific descriptors, including this descriptor. */

			uint8_t                 Controls; /**< Interface number of the associated Audio Streaming interface. */
		} ATTR_PACKED USB_Audio2_Descriptor_Interface_AC_t;

		/* Audio 2.0 AC Input Terminal */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   must be \ref AUDIO_DSUBTYPE_CSInterface_InputTerminal.
			                                  */

			uint8_t                 TerminalID; /**< ID value of this terminal unit - must be a unique value within the device. */
			uint16_t                TerminalType; /**< Type of terminal, a \c TERMINAL_* mask. */
			uint8_t                 AssocTerminal; /**< ID of associated output terminal, for physically grouped terminals
			                                                   *   such as the speaker and microphone of a phone handset.
			                                                   */
			uint8_t                 CSourceID; /** */
			uint8_t                 TotalChannels; /**< Total number of separate audio channels within this interface (right, left, etc.) */
			uint32_t                ChannelConfig; /**< \c CHANNEL_* masks indicating what channel layout is supported by this terminal. */

			uint8_t                 ChannelStrIndex; /**< Index of a string descriptor describing this channel within the device. */
			uint16_t                Controls; /** */
			uint8_t                 TerminalStrIndex; /**< Index of a string descriptor describing this descriptor within the device. */
		} ATTR_PACKED USB_Audio2_Descriptor_InputTerminal_t;
		/* Audio 2.0 AC Output Terminal */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   must be \ref AUDIO_DSUBTYPE_CSInterface_InputTerminal.
			                                  */

			uint8_t                 TerminalID; /**< ID value of this terminal unit - must be a unique value within the device. */
			uint16_t                TerminalType; /**< Type of terminal, a \c TERMINAL_* mask. */
			uint8_t                 AssocTerminal; /**< ID of associated output terminal, for physically grouped terminals
			                                                   *   such as the speaker and microphone of a phone handset.
			                                                   */
			uint8_t                 SourceID; /** ID of the Unit or Terminal to which this Terminal is connected. */
			uint8_t                 CSourceID; /**ID of the Clock Entity to which this Output Terminal is connected. */
			uint16_t                Controls; /** */
			uint8_t                 TerminalStrIndex; /**< Index of a string descriptor describing this descriptor within the device. */
		} ATTR_PACKED USB_Audio2_Descriptor_OutputTerminal_t;

		/* Audio 2.0 AC Feature Unit */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   must be \ref AUDIO_DSUBTYPE_CSInterface_Feature.
			                                  */

			uint8_t                 UnitID; /**< Constant uniquely identifying the Unit within the audio function. This value is used in all requests to address this Unit. */
			uint8_t                 SourceID; /** ID of the Unit or Terminal to which this Feature Unit is connected. */
			uint32_t                Controls[3]; /** */
			uint8_t                 Feature; /** Index of a string descriptor, describing this Feature Unit. */
		} ATTR_PACKED USB_Audio2_Descriptor_Feature_t;
		
		/* Audio 2.0 AC Clock Source */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   must be \ref AUDIO_DSUBTYPE_CSInterface_Feature.
			                                  */

			uint8_t                 ClockID; /**< Constant uniquely identifying the Clock Source Entity within the audio function. This value is used in all requests to address this Entity. */
			uint8_t                 Attributes; /** */
			uint8_t                 Controls; /** */
			uint8_t                 AssocTerminal; /** Terminal ID of the Terminal that is associated with this Clock Source.*/
			uint8_t                 ClockSource; /** Index of a string descriptor, describing the Clock Source Entity.*/
		} ATTR_PACKED USB_Audio2_Descriptor_ClockSource_t;
		/* Audio 2.0 AC Clock Selector */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   must be \ref AUDIO_DSUBTYPE_CSInterface_Feature.
			                                  */

			uint8_t                 ClockID; /**< Constant uniquely identifying the Clock Source Entity within the audio function. This value is used in all requests to address this Entity. */
			uint8_t                 NrInPins; /** */
			uint8_t                 CSourceID[1]; /** */
			uint8_t                 Controls; /** */
			uint8_t                 ClockSource; /** Index of a string descriptor, describing the Clock Source Entity.*/
		} ATTR_PACKED USB_Audio2_Descriptor_ClockSelector_t;


		typedef struct
		{
			uint8_t bLength; /**< Size of the descriptor, in bytes. */
			uint8_t bDescriptorType; /**< Type of the descriptor, either a value in \ref USB_DescriptorTypes_t or a value
			                          *   given by the specific class.
			                          */

			uint8_t bDescriptorSubtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                             *   must be \ref AUDIO_DSUBTYPE_CSInterface_Feature.
			                             */

			uint8_t bUnitID; /**< ID value of this feature unit - must be a unique value within the device. */
			uint8_t bSourceID; /**< Source ID value of the audio source input into this feature unit. */

			uint8_t bControlSize; /**< Size of each element in the \c ChannelControls array. */
			uint8_t bmaControls[3]; /**< Feature masks for the control channel, and each separate audio channel. */

			uint8_t iFeature; /**< Index of a string descriptor describing this descriptor within the device. */
		} ATTR_PACKED USB_Audio2_StdDescriptor_ClockSource_t;

		/* Audio 2.0 AS Interface Descriptor */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   a value from the \ref Audio_CSInterface_AS_SubTypes_t enum.
			                                  */

			uint8_t                 TerminalLink; /**< ID value of the output terminal this descriptor is describing. */
			uint8_t                 Control; /** */
			uint8_t                 FormatType; /** */
			uint32_t                Formats; /** */
			uint8_t                 NrChannles; /** */
			uint32_t                ChannleConfig; /** */
			uint8_t                 ChannelNames; /** */
		} ATTR_PACKED USB_Audio2_Descriptor_Interface_AS_t;
		
		/* Audio 2.0 AS Type III Format Type Descriptor */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Regular descriptor header containing the descriptor's type and length. */
			uint8_t                 Subtype; /**< Sub type value used to distinguish between audio class-specific descriptors,
			                                  *   a value from the \ref Audio_CSInterface_AS_SubTypes_t enum.
			                                  */

			uint8_t                 FormatType; /** */
			uint8_t                 SubslotSize; /** */
			uint8_t                 BitResolution; /** */
		} ATTR_PACKED USB_Audio2_Descriptor_Type3_Format_t;
		/* Audio 2.0 AS Isochronous Audio Data Endpoint Descriptor */
		typedef struct
		{
			USB_Descriptor_Header_t Header; /**< Descriptor header, including type and size. */
			uint8_t                 Subtype; /** */

			uint8_t                 Attributes; /** */
			uint8_t                 Controls; /** */
			uint8_t                 LockDelayUnits; /** */
			uint16_t                LockDelay; /** */
		} ATTR_PACKED USB_Audio2_Descriptor_IsoAudioData_Endpoint_t;

	/* Type Defines: */
		/** Type define for the device configuration descriptor structure. This must be defined in the
		 *  application code, as the configuration descriptor contains several sub-descriptors which
		 *  vary between devices, and which describe the device's usage to the host.
		 */
		typedef struct
		{
			USB_Descriptor_Configuration_Header_t     Config;

			// Interface Association Descritptor
			USB_Descriptor_Interface_Association_t    Interface_Association;
			// Audio Control Interface
			USB_Descriptor_Interface_t                Audio_ControlInterface;
			USB_Audio2_Descriptor_Interface_AC_t      Audio_ControlInterface_SPC;
			USB_Audio2_Descriptor_ClockSource_t       Audio_ControlInterface_SPC1;
			USB_Audio2_Descriptor_ClockSelector_t     Audio_ControlInterface_SPC2;
			USB_Audio2_Descriptor_InputTerminal_t     Audio_ControlInterface_SPC3;
			USB_Audio2_Descriptor_Feature_t           Audio_ControlInterface_SPC4;
			USB_Audio2_Descriptor_OutputTerminal_t    Audio_ControlInterface_SPC5;
			USB_Audio2_Descriptor_InputTerminal_t     Audio_ControlInterface_SPC6;
			USB_Audio2_Descriptor_OutputTerminal_t    Audio_ControlInterface_SPC7;

			// Audio Streaming Interface #1
			USB_Descriptor_Interface_t                Audio_StreamInterface1;
			USB_Descriptor_Interface_t                Audio_StreamInterface1alt;
			USB_Audio2_Descriptor_Interface_AS_t      Audio_StreamInterface1_SPC;
			USB_Audio2_Descriptor_Type3_Format_t      Audio_StreamInterface1_SPC1;
			USB_Descriptor_Endpoint_t                 Audio_StreamOutEndpoint;
			USB_Audio2_Descriptor_IsoAudioData_Endpoint_t Audio_StreamIsoAudioDataEndpoint;
			USB_Descriptor_Endpoint_t                 Audio_StreamInEndpoint;

			// Audio Streaming Interface #2
			USB_Descriptor_Interface_t                Audio_StreamInterface2;
			USB_Descriptor_Interface_t                Audio_StreamInterface2alt;
			USB_Audio2_Descriptor_Interface_AS_t      Audio_StreamInterface2_SPC;
			USB_Audio2_Descriptor_Type3_Format_t      Audio_StreamInterface2_SPC1;
			USB_Descriptor_Endpoint_t                 Audio_StreamInEndpoint2;
			USB_Audio2_Descriptor_IsoAudioData_Endpoint_t Audio_StreamIsoAudioDataEndpoint2;

			// MIDI Streaming Interface
			USB_Descriptor_Interface_t                MIDI_StreamInterface;
			USB_MIDI_Descriptor_AudioInterface_AS_t   MIDI_StreamInterface_SPC;
			USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Emb;
			USB_MIDI_Descriptor_InputJack_t           MIDI_In_Jack_Ext;
			USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Emb;
			USB_MIDI_Descriptor_OutputJack_t          MIDI_Out_Jack_Ext;
			USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_In_Jack_Endpoint;
			USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_In_Jack_Endpoint_SPC;
			USB_Audio_Descriptor_StreamEndpoint_Std_t MIDI_Out_Jack_Endpoint;
			USB_MIDI_Descriptor_Jack_Endpoint_t       MIDI_Out_Jack_Endpoint_SPC;
		} USB_Descriptor_Configuration_t;

		/** Enum for the device interface descriptor IDs within the device. Each interface descriptor
		 *  should have a unique ID index associated with it, which can be used to refer to the
		 *  interface from other descriptors.
		 */
		enum InterfaceDescriptors_t
		{
			INTERFACE_ID_AudioControl = 0, /**< Audio control interface descriptor ID */
			INTERFACE_ID_AudioStream1  = 1, /**< Audio streaming interface descriptor ID */
			INTERFACE_ID_AudioStream2  = 2, /**< Audio streaming interface descriptor ID */
			INTERFACE_ID_MidiStream  = 3, /**< Audio streaming interface descriptor ID */
		};

		/** Enum for the device string descriptor IDs within the device. Each string descriptor should
		 *  have a unique ID index associated with it, which can be used to refer to the string from
		 *  other descriptors.
		 */
		enum StringDescriptors_t
		{
			STRING_ID_Language     = 0, /**< Supported Languages string descriptor ID (must be zero) */
			STRING_ID_Manufacturer = 1, /**< Manufacturer string ID */
			STRING_ID_Product      = 2, /**< Product string ID */
		};

	/* Function Prototypes: */
		uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue,
		                                    const uint16_t wIndex,
		                                    const void** const DescriptorAddress)
		                                    ATTR_WARN_UNUSED_RESULT ATTR_NON_NULL_PTR_ARG(3);

#endif

