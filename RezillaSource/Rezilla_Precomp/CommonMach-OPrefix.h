// ===========================================================================
// CommonMach-OPrefix.h
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2005-03-13 22:07:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2004, 2005
// All rights reserved.
// ===========================================================================
//	Common options for a Mach-O Target

// ---------------------------------------------------------------------------
//	Mach-O Target

#define PP_Target_Carbon		1

#define PP_Target_Classic		(!PP_Target_Carbon)

#define TARGET_API_MAC_CARBON	PP_Target_Carbon
#define TARGET_API_MAC_OS8		PP_Target_Classic
#define TARGET_API_MAC_OSX		PP_Target_Carbon


// ---------------------------------------------------------------------------
//	Options
	
#define PP_Uses_PowerPlant_Namespace	0
#define PP_Supports_Pascal_Strings		1
#define PP_StdDialogs_Option			PP_StdDialogs_NavServicesOnly
#define PP_Uses_Aqua_MenuBar			1

#define	PP_Uses_Old_Integer_Types		0
#define PP_Obsolete_AllowTargetSwitch	0
#define PP_Obsolete_ThrowExceptionCode	0
#define PP_Warn_Obsolete_Classes		1

#define PP_Suppress_Notes_221			1

// This will enable ClickInTitleBar for windows with a proxy
#define PP_Uses_WindowMgr20_Routines	1

#include <MSLCarbonPrefix.h>
#include <cmath>
