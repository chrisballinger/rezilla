// ===========================================================================
// 	CCursor_PickerStamp.cp
// 
//                       Created : 2006-09-23 07:56:20
//             Last modification : 2006-09-27 12:44:16
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

#include "CCursor_PickerStamp.h"
#include "CPickerView.h"
#include "CPickerWindow.h"
#include "COffscreen.h"
#include "UResources.h"
#include "UIconMisc.h"
#include "UColorUtils.h"

#include <Icons.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//   CCursor_PickerStamp					Default Constructor		  [public]
// ---------------------------------------------------------------------------

CCursor_PickerStamp::CCursor_PickerStamp(
									CPickerView *		inParent,
									const SPaneInfo&	inPaneInfo,
									const SViewInfo&	inViewInfo)
	: CPickerStamp(inParent, inPaneInfo, inViewInfo)
{
}


// ---------------------------------------------------------------------------
//   ~CCursor_PickerStamp					Destructor				  [public]
// ---------------------------------------------------------------------------

CCursor_PickerStamp::~CCursor_PickerStamp()
{
}


// ---------------------------------------------------------------------------
//   StampSize														  [public]
// ---------------------------------------------------------------------------

void
CCursor_PickerStamp::StampSize(ResType inType, SInt16 &outWidth, SInt16 &outHeight)
{
#pragma unused(inType)
	outWidth = 16;
	outHeight = 16;
}


// ---------------------------------------------------------------------------
// 	DrawBuffer
// ---------------------------------------------------------------------------

void
CCursor_PickerStamp::DrawBuffer(COffscreen * inBuffer, Rect inFrame)
{	
	StGWorldSaver	aSaver;
	GrafPtr			macPort = this->GetMacPort();
	
	if ( !macPort || !inBuffer ) return;

	LocalToPortPoint( topLeft(inFrame) );
	LocalToPortPoint( botRight(inFrame) );
	inBuffer->CopyTo( macPort, &inFrame );
}


// ---------------------------------------------------------------------------
//   DrawSelf														  [public]
// ---------------------------------------------------------------------------

void
CCursor_PickerStamp::DrawSelf()
{
	// The resID is the paneID of the PickerView
	ResIDT		theID = mParent->GetPaneID();
	short		theRefNum = mParent->GetUserCon();
	ResType		theType = mParent->GetOwnerWindow()->GetType();
	
	if (theRefNum != kResFileNotOpened) {
		Rect			frame;
		SInt32			theWidth, theHeight, theDepth, theRowBytes;
		COffscreen *	theBuffer = NULL;
		Handle			theResHandle = NULL;
		CTabHandle		theTable;
		UInt8*			dataPtr;
		
		theResHandle = ::Get1Resource(theType, theID);
		if (!theResHandle) return;
		
		CalcLocalFrameRect(frame);
		StRezRefSaver saver(theRefNum);		
		
		if (!UIconMisc::GetCursorInfoForType(theType, theResHandle, theWidth, theHeight, 
										   theDepth, theRowBytes, theTable, dataPtr)) {
			return;
		} 
		
		// Create the offscreen buffer
		theBuffer = COffscreen::CreateBuffer( theWidth, theHeight, theDepth, theTable );
		// Fill the buffer with the resource data
		if (theBuffer) {
			theBuffer->CopyFromRawData(dataPtr, theRowBytes);	
		} 
		DrawBuffer(theBuffer, frame);
			
		if ( theBuffer ) delete theBuffer;
		if ( theTable ) ::DisposeCTable( theTable );
	}
}




PP_End_Namespace_PowerPlant
