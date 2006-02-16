// ===========================================================================
// File: "RezillaPluginInterface.h"
// 
//                        Created: 2005-09-08 15:49:50
//              Last modification: 2006-02-16 11:52:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2005-2006
// All rights reserved.
// ===========================================================================

#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFPlugInCOM.h>


// Define the UUID for the type: 
// "306A0EF3-206E-11DA-8320-000A95B1FF7C"
#define kRezillaEditorTypeID (CFUUIDGetConstantUUIDWithBytes(NULL, 0x30,0x6A,0x0E,0xF3,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


// Define the UUID for the interface. RezillaEditorType objects must
// implement RezillaEditorInterface:
// "306AE167-206E-11DA-8320-000A95B1FF7C"
#define kRezillaEditorInterfaceID (CFUUIDGetConstantUUIDWithBytes(NULL, 0x30,0x6A,0xE1,0x67,0x20,0x6E,0x11,0xDA,0x83,0x20,0x00,0x0A,0x95,0xB1,0xFF,0x7C))


typedef struct SRezillaPluginInterface {
	IUNKNOWN_C_GUTS;
	void (*editResource)( void *myInstance, ResType inType, short inID );
} SRezillaPluginInterface;


typedef SInt32	RezPlugRef;

enum {
	kPlugWinHasNoAttributes = 0L,
	kPlugWinHasSaveButton = (1L << 1),
	kPlugWinHasCancelButton = (1L << 2),
	kPlugWinHasRevertButton = (1L << 3),
	kPlugWinHasLockIcon = (1L << 4),
	kPlugWinHasNameField = (1L << 5),
	kPlugWinStandardAttributes = (kPlugWinHasSaveButton | kPlugWinHasCancelButton | kPlugWinHasRevertButton | kPlugWinHasLockIcon)
};


/* 
 * #define IUNKNOWN_C_GUTS \
 *     void *_reserved; \
 *     HRESULT (STDMETHODCALLTYPE *QueryInterface)(void *thisPointer, REFIID iid, LPVOID *ppv); \
 *     ULONG (STDMETHODCALLTYPE *AddRef)(void *thisPointer); \
 *     ULONG (STDMETHODCALLTYPE *Release)(void *thisPointer)
 */

// requiredWinAttributes
// menuCount
// menuTitles
// 
// AcceptResource
// EditResource
// ReturnResource

// Boolean	AcceptResource( void *myInstance, ResType inType, short inID );
// void	EditResource( void *myInstance, RezPlugRef inRef, ResType inType, short inID, Handle inDataH );
// Handle	ReturnResource( void *myInstance );


