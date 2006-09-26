// ===========================================================================
// RezillaMachODebugPrefix.h				
//                       Created: 2003-05-08 09:21:29
//             Last modification: 2006-09-26 07:47:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2006
// All rights reserved.
// ===========================================================================

#include "DebugMach-OHeaders++"

#undef __STDC__
#define __STDC__ 1

// Characterize our Mach-O target
#define REZILLA_MACH_O 1

// Define to 1 if debugging the bitmap editor. This will disable the 
// PP_Debug_VerifyFocusCache macro constant because the bitmap editor 
// windows have their own definition for EstablishPort() which interferes 
// with PP debugging code.
#define REZILLA_DEBUG_BITMAP 1

// Debugging code: define PP_Debug_VerifyFocusCache as 1
// to enable focus verification. This helps diagnose
// problems where the focus is not being invalidated
// after changing the port state.
#if REZILLA_DEBUG_BITMAP
#define PP_Debug_VerifyFocusCache 0
#else
#define PP_Debug_VerifyFocusCache 1
#endif