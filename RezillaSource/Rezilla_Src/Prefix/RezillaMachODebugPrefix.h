// ===========================================================================
// RezillaMachODebugPrefix.h				
//                       Created: 2003-05-08 09:21:29
//             Last modification: 2005-01-02 14:34:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "DebugMach-OHeaders++"

#undef __STDC__
#define __STDC__ 1

#define REZILLA_MACH_O 1

// Debugging code: define PP_Debug_VerifyFocusCache as 1
// to enable focus verification. This helps diagnose
// problems where the focus is not being invalidated
// after changing the port state.

#define PP_Debug_VerifyFocusCache 1
