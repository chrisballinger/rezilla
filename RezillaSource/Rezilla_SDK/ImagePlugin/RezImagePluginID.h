// ===========================================================================
// File: "RezJPEGPluginID.h"
// 
//                        Created: 2006-02-20 14:21:43
//              Last modification: 2006-03-02 09:13:51
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

// Version number for this plugin
#define IMAGE_PLUGIN_VERSION "0.1"

// The UUID for the factory function: 
// "0905F836-A20C-11DA-BC6C-000A95B1FF7C"
#define kRezillaImageFactoryID (CFUUIDGetConstantUUIDWithBytes(NULL,0x09,0x05,0xF8,0x36,0xA2,0x0C,0x11,0xDA,0xBC,0x6C,0x00,0x0A,0x95,0xB1,0xFF,0x7C))

// The string form is used in the plc file
#define kRezillaImageFactoryString "0905F836-A20C-11DA-BC6C-000A95B1FF7C"