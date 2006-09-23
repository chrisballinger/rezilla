// ===========================================================================
// 	CIconFamily_PickerStamp.cp
// 
//                       Created : 2006-02-25 17:40:43
//             Last modification : 2006-09-23 07:57:58
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
// The stamp is the part of a picker view where the image is drawn. The
// StampSize method returns the dimensions of this drawing area.


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CIconFamily_PickerStamp.h"
#include "CPickerView.h"
#include "CPickerWindow.h"
#include "COffscreen.h"
#include "UResources.h"
#include "UIconMisc.h"
#include "UColorUtils.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CIconFamily_PickerStamp				Default Constructor		  [public]
// ---------------------------------------------------------------------------

CIconFamily_PickerStamp::CIconFamily_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CIconFamily_PickerStamp				Destructor				  [public]
// ---------------------------------------------------------------------------

CIconFamily_PickerStamp::~CIconFamily_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CIconFamily_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
	switch (inType) {
		case 'ics#':
		case 'ics4':
		case 'ics8':
		// 16x16 small icons
		outWidth = 16;
		outHeight = 16;
		break;
		
		case 'ICN#':
		case 'icl4':
		case 'icl8':
		// 32x32 large icons
		outWidth = 32;
		outHeight = 32;
		break;
		
		case 'icm#':
		case 'icm4':
		case 'icm8':
		// 16x12 medium icons
		outWidth = 16;
		outHeight = 12;
		break;
		
		default:
		break;
		
	}
}


// ---------------------------------------------------------------------------
// 	DrawBuffer
// ---------------------------------------------------------------------------

void
CIconFamily_PickerStamp::DrawBuffer(COffscreen * inBuffer, Rect inFrame)
{	
	StGWorldSaver		aSaver;
	StColorPenState		aPenState;	
	Rect				portRect;
	GrafPtr				macPort = this->GetMacPort();
	
	if ( !macPort ) return;

	portRect = inFrame;
	LocalToPortPoint( topLeft(inFrame) );
	LocalToPortPoint( botRight(inFrame) );

	if (inBuffer) {
		inBuffer->CopyTo( macPort, &portRect );
	} else {
		Pattern aPat;
		
		this->FocusDraw();
		aPenState.Normalize();
		::PenPat( UQDGlobals::GetLightGrayPat(&aPat) );
		::PaintRect( &inFrame );
	}
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CIconFamily_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT theID = mParent->GetPaneID();
	short theRefNum = mParent->GetUserCon();
	ResType		theType = mParent->GetOwnerWindow()->GetType();
	
	if (theRefNum != kResFileNotOpened) {
		Rect	frame;
		SInt32	theWidth, theHeight, theDepth, theRowBytes, theOffset;
		COffscreen *	theBuffer = NULL;
		Handle			theResHandle = NULL;
		CTabHandle		theTable;
		
// 		FocusDraw();
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);		
		
		UIconMisc::GetIconInfoForType(theType, theWidth, theHeight, theDepth, theRowBytes, theOffset);
		
		// Icon families use the standard color table for their depth
		theTable = UColorUtils::GetColorTable(theDepth);
		// Create the offscreen buffer
		theBuffer = COffscreen::CreateBuffer( theWidth, theHeight, theDepth, theTable );
		// Fill the buffer with the resource data
		theResHandle = ::Get1Resource(theType, theID);
		if (theResHandle) {
			if (theBuffer) {
				theBuffer->CopyFromRawData( (UInt8*) *theResHandle + theOffset, theRowBytes );	
			} 
			DrawBuffer(theBuffer, frame);
		} 
		
		if ( theBuffer ) delete theBuffer;
		if ( theTable ) ::DisposeCTable( theTable );

	}
}


PP_End_Namespace_PowerPlant
