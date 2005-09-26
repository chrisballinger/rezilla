// ===========================================================================
// File: "RezillaPluginInterface.h"
// 
//                        Created: 2005-09-08 15:49:50
//              Last modification: 2005-09-26 10:14:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
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
    void (*testResource)( void *myInstance );
 } SRezillaPluginInterface;

