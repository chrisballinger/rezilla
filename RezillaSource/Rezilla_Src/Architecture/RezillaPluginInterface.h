// ===========================================================================
// File: "RezillaPluginInterface.h"
// 
//                        Created: 2005-09-08 15:49:50
//              Last modification: 2006-03-08 09:16:15
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================
// From /Developer/ADC%20Reference%20Library/documentation/CoreFoundation/Conceptual/CFPlugIns/index.html?file:/Developer/ADC%20Reference%20Library/documentation/CoreFoundation/Conceptual/CFPlugIns/CFPlugIns.html
//    "By passing a this pointer to each interface function, you allow the
//    plug-in writer to implement in C++ and to have access to the plug-in
//    object when the function executes in any language."


#ifndef REZILLAPLUGININTERFACE_H
#define REZILLAPLUGININTERFACE_H
#pragma once


#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFPlugInCOM.h>

// Editor UUIDs
// ============
// Define the UUID for the editor type: 
// "306A0EF3-206E-11DA-8320-000A95B1FF7C"
#define kRezillaPluginEditorTypeID (CFUUIDGetConstantUUIDWithBytes(NULL,0x30,0x6A,0x0E,0xF3,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))

// Define the UUID for the editor interface. RezillaEditorType objects must
// implement RezillaEditorInterface.
// This is version 1 (Vs1) of the interface. There might be different 
// interfaces in the future.
// "306AE167-206E-11DA-8320-000A95B1FF7C"
#define kRezillaPluginEditorInterfaceVs1 (CFUUIDGetConstantUUIDWithBytes(NULL,0x30,0x6A,0xE1,0x67,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


// Picker UUIDs
// ============
// Define the UUID for the picker type: 
// "D93257A6-A50B-11DA-893D-000A95B1FF7C"
#define kRezillaPluginPickerTypeID (CFUUIDGetConstantUUIDWithBytes(NULL,0xD9,0x32,0x57,0xA6,0xA5,0x0B,0x11,0xDA,0x89,0x3D,0x00,0x0A,0x95,0xB1,0xFF,0x7C))

// Define the UUID for the picker interface. RezillaPickerType objects must
// implement RezillaPickerInterface:
// "1C1EC256-A50C-11DA-81FC-000A95B1FF7C"
#define kRezillaPluginPickerInterfaceID (CFUUIDGetConstantUUIDWithBytes(NULL,0x1C,0x1E,0xC2,0x56,0xA5,0x0C,0x11,0xDA,0x81,0xFC,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


enum {
	kPluginWinHasNoAttributes		= 0L,
	kPluginWinHasSaveButton			= (1L << 0),
	kPluginWinHasCancelButton		= (1L << 1),
	kPluginWinHasRevertButton		= (1L << 2),
	kPluginWinHasLockIcon			= (1L << 3),
	kPluginWinHasNameField			= (1L << 4),
	kPluginWinHasCollapseBox		= (1L << 5),
	kPluginWinIsResizable			= (1L << 6),
	kPluginWinStandardControls		= (kPluginWinHasSaveButton 
								   | kPluginWinHasCancelButton 
								   | kPluginWinHasRevertButton 
								   | kPluginWinHasLockIcon),
	kPluginSupportCut				= (1L << 10),
	kPluginSupportCopy				= (1L << 11),
	kPluginSupportPaste				= (1L << 12),
	kPluginSupportClear				= (1L << 13),
	kPluginSupportSelectAll			= (1L << 14),
	kPluginSupportFind				= (1L << 15),
	kPluginSupportFindNext			= (1L << 16),
	kPluginSupportExport			= (1L << 17),
	kPluginSupportEditCommands		= (kPluginSupportCut 
								   | kPluginSupportCopy 
								   | kPluginSupportPaste 
								   | kPluginSupportClear)
};

enum {
	kPluginCommandCut		= 1,
	kPluginCommandCopy,
	kPluginCommandPaste,
	kPluginCommandClear,
	kPluginCommandSelectAll,
	kPluginCommandFind,
	kPluginCommandFindNext,
	kPluginCommandExport
};



// A RezPlugRef is a pointer to plugin defined client data. All the
// interface functions (except AcceptResource which defines this pointer)
// will pass this reference number in their first argument.
typedef void *	RezPlugRef;


// Structure received from the plugin to define its requirements and 
// initialisations
typedef struct RezPlugInfo {
	RezPlugRef	plugref;
	UInt32		attributes;
	Rect		winbounds;
	UInt8		menucount;
	MenuID *	menuIDs;
	OSErr		error;
} RezPlugInfo;


// Structure sent by the host with post-initialisation info
typedef struct RezHostInfo {
	short		refnum;
	WindowRef	winref;
	UInt8		menucount;
	MenuRef	*	menurefs;
	Rect		editrect;
	Boolean		readonly;
} RezHostInfo;


typedef struct SPluginEditorInterface {
	IUNKNOWN_C_GUTS;
	Boolean	(*AcceptResource)(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo);
	OSErr	(*EditResource)(RezPlugRef inPlugref, RezHostInfo inInfo);
	Handle	(*ReturnResource)(RezPlugRef inPlugref, Boolean * outRelease, OSErr * outError);
	OSErr	(*RevertResource)(RezPlugRef inPlugref, Handle inDataH);
	Boolean	(*IsModified)(RezPlugRef inPlugref);
	void	(*CleanUp)(RezPlugRef inPlugref);
	void	(*Refresh)(RezPlugRef inPlugref);
	OSErr	(*ResizeBy)(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta);
	void	(*HandleMenu)(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem);
	void	(*HandleClick)(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords);
	void	(*HandleKeyDown)(RezPlugRef inPlugref, const EventRecord * inKeyEvent);
	Boolean	(*HandleCommand)(RezPlugRef inPlugref, SInt16 inCommand);
} SPluginEditorInterface;


typedef struct SPluginPickerInterface {
	IUNKNOWN_C_GUTS;
	Boolean	(*AcceptType)(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo);
	OSErr	(*EditPicker)(RezPlugRef inPlugref, RezHostInfo inInfo);
	Handle	(*UpdatePicker)(RezPlugRef inPlugref, Boolean * outRelease, OSErr * outError);
	void	(*CleanUp)(RezPlugRef inPlugref);
	OSErr	(*ResizeBy)(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta);
	void	(*HandleMenu)(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem);
	void	(*HandleDoubleClick)(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords);
	void	(*HandleKeyDown)(RezPlugRef inPlugref, const EventRecord * inKeyEvent);
} SPluginPickerInterface;


// Rezilla plugins error codes
enum PluginErrors {
	plugErr_Generic				= 5000,	
	plugErr_InitializationFailed,
	plugErr_UnsupportedType,
	plugErr_UnsupportedID,
	plugErr_InvalidData,
	plugErr_UnsupportedResourceFormat,
	plugErr_UnsupportedResourceVersion,
	plugErr_EditResourceFailed,
	plugErr_ReturnResourceFailed,
	plugErr_RevertResourceFailed,
	plugErr_CantResizeWindow,
	plugErr_CantHandleMenuCommand,
	plugErr_LastError
};


#endif  // REZILLAPLUGININTERFACE_H

