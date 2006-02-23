// ===========================================================================
// File: "RezillaPluginInterface.h"
// 
//                        Created: 2005-09-08 15:49:50
//              Last modification: 2006-02-22 14:35:27
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================
// From /Developer/ADC%20Reference%20Library/documentation/CoreFoundation/Conceptual/CFPlugIns/index.html?file:/Developer/ADC%20Reference%20Library/documentation/CoreFoundation/Conceptual/CFPlugIns/CFPlugIns.html
// By passing a this pointer to each interface function, you allow the
// plug-in writer to implement in C++ and to have access to the plug-in
// object when the function executes in any language.


#ifndef REZILLAPLUGININTERFACE_H
#define REZILLAPLUGININTERFACE_H
#pragma once


#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFPlugInCOM.h>


// Define the UUID for the type: 
// "306A0EF3-206E-11DA-8320-000A95B1FF7C"
#define kRezillaEditorTypeID (CFUUIDGetConstantUUIDWithBytes(NULL, 0x30,0x6A,0x0E,0xF3,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


// Define the UUID for the interface. RezillaEditorType objects must
// implement RezillaEditorInterface:
// "306AE167-206E-11DA-8320-000A95B1FF7C"
#define kRezillaEditorInterfaceID (CFUUIDGetConstantUUIDWithBytes(NULL, 0x30,0x6A,0xE1,0x67,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


/* WindowAttributes */
enum {
	kPlugWinHasNoAttributes		= 0L,
	kPlugWinHasSaveButton		= (1L << 1),
	kPlugWinHasCancelButton		= (1L << 2),
	kPlugWinHasRevertButton		= (1L << 3),
	kPlugWinHasLockIcon			= (1L << 4),
	kPlugWinHasNameField		= (1L << 5),
	kPlugWinHasCollapseBox		= (1L << 6),
	kPlugWinIsResizable			= (1L << 7),
	kPlugWinStandardAttributes	= (kPlugWinHasSaveButton 
								   | kPlugWinHasCancelButton 
								   | kPlugWinHasRevertButton 
								   | kPlugWinHasLockIcon)
};


// A RezPlugRef is a pointer to plugin defined client data. All the
// interface functions (except AcceptResource which defines this pointer)
// will pass this reference number in their first argument.
typedef void *	RezPlugRef;


// Structure received from the plugin to define its requirements and 
// initialisations
typedef struct RezPlugInfo {
	RezPlugRef	plugref;
	UInt32		winattrs;
	Rect		winbounds;
	UInt8		menucount;
	MenuID *	menuIDs;
	OSErr		error;
} RezPlugInfo;


// Structure sent by the host with post-initialisation info
typedef struct RezHostInfo {
	WindowRef	winref;
	UInt8		menucount;
	MenuRef	*	menurefs;
	Rect		contents;
	Boolean		readonly;
} RezHostInfo;


typedef struct SRezillaPluginInterface {
	IUNKNOWN_C_GUTS;
	Boolean	(*AcceptResource)(void *myInstance, ResType inType, short inID, Handle inDataH, RezPlugInfo * outInfo);
	OSErr	(*EditResource)(RezPlugRef inPlugref, RezHostInfo inInfo);
	Handle	(*ReturnResource)(RezPlugRef inPlugref, Boolean * outRelease, OSErr * outError);
	OSErr	(*RevertResource)(RezPlugRef inPlugref, Handle inDataH);
	Boolean	(*IsModified)(RezPlugRef inPlugref);
	void	(*CleanUp)(RezPlugRef inPlugref);
	void	(*Refresh)(RezPlugRef inPlugref);
	void	(*ResizeBy)(RezPlugRef inPlugref, SInt16 inWidthDelta, SInt16 inHeightDelta);
	void	(*HandleMenu)(RezPlugRef inPlugref, MenuRef menu, SInt16 inMenuItem);
	void	(*HandleClick)(RezPlugRef inPlugref, const EventRecord * inMacEvent, Point inPortCoords);
	void	(*HandleKeyDown)(RezPlugRef inPlugref, const EventRecord * inKeyEvent);
} SRezillaPluginInterface;


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

