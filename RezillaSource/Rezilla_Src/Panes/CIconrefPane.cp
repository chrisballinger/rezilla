// ===========================================================================
// CIconrefPane.cp
// 
//                       Created : 2006-09-26 13:19:49
//             Last modification : 2006-09-26 13:44:15
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// 
// typedef SInt16                          IconAlignmentType;
// typedef SInt16                          IconTransformType;
// 
// 		/* Alignment type values. */
// 		enum {
// 		  kAlignNone                    = 0x00,
// 		  kAlignVerticalCenter          = 0x01,
// 		  kAlignTop                     = 0x02,
// 		  kAlignBottom                  = 0x03,
// 		  kAlignHorizontalCenter        = 0x04,
// 		  kAlignAbsoluteCenter          = kAlignVerticalCenter | kAlignHorizontalCenter,
// 		  kAlignCenterTop               = kAlignTop | kAlignHorizontalCenter,
// 		  kAlignCenterBottom            = kAlignBottom | kAlignHorizontalCenter,
// 		  kAlignLeft                    = 0x08,
// 		  kAlignCenterLeft              = kAlignVerticalCenter | kAlignLeft,
// 		  kAlignTopLeft                 = kAlignTop | kAlignLeft,
// 		  kAlignBottomLeft              = kAlignBottom | kAlignLeft,
// 		  kAlignRight                   = 0x0C,
// 		  kAlignCenterRight             = kAlignVerticalCenter | kAlignRight,
// 		  kAlignTopRight                = kAlignTop | kAlignRight,
// 		  kAlignBottomRight             = kAlignBottom | kAlignRight
// 		};
// 
// 		/* Transform type values. */
// 		enum {
// 		  kTransformNone                = 0x00,
// 		  kTransformDisabled            = 0x01,
// 		  kTransformOffline             = 0x02,
// 		  kTransformOpen                = 0x03,
// 		  kTransformLabel1              = 0x0100,
// 		  kTransformLabel2              = 0x0200,
// 		  kTransformLabel3              = 0x0300,
// 		  kTransformLabel4              = 0x0400,
// 		  kTransformLabel5              = 0x0500,
// 		  kTransformLabel6              = 0x0600,
// 		  kTransformLabel7              = 0x0700,
// 		  kTransformSelected            = 0x4000,
// 		  kTransformSelectedDisabled    = kTransformSelected | kTransformDisabled,
// 		  kTransformSelectedOffline     = kTransformSelected | kTransformOffline,
// 		  kTransformSelectedOpen        = kTransformSelected | kTransformOpen
// 		};

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIconrefPane.h"
#include "UResources.h"

#include <LStream.h>
#include <PP_Constants.h>

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CIconrefPane							Default Constructor		  [public]
// ---------------------------------------------------------------------------

CIconrefPane::CIconrefPane()
{
	mIconRef = 0;
	mAlignment = kAlignNone;
	mTransform = kTransformNone;
}


// ---------------------------------------------------------------------------
//   CIconrefPane							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CIconrefPane::CIconrefPane(
				 const SPaneInfo&	inPaneInfo,
				 IconAlignmentType	inAlignment,
				 IconTransformType	inTransform)

	: LPane(inPaneInfo)
{
	mIconRef = 0;
	mAlignment = inAlignment;
	mTransform = inTransform;
}


// ---------------------------------------------------------------------------
//   CIconrefPane							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CIconrefPane::CIconrefPane(
	LStream*	inStream)

	: LPane(inStream)
{
	*inStream >> mAlignment;
	*inStream >> mTransform;
}


// ---------------------------------------------------------------------------
//     ~CIconrefPane						Destructor				  [public]
// ---------------------------------------------------------------------------

CIconrefPane::~CIconrefPane()
{
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CIconrefPane::DrawSelf()
{
	Rect	frame;
		
	FocusDraw();
	CalcLocalFrameRect(frame);
	::PlotIconRef(&frame, mAlignment, mTransform, kIconServicesNormalUsageFlag, mIconRef);
}


PP_End_Namespace_PowerPlant
