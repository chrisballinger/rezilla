// ===========================================================================
// CRezMapDragDrop.cp					
//                       Created: 2003-05-30 22:23:58
//             Last modification: 2004-02-22 19:29:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezMapDragDrop.h"
#include "CRezMapTable.h"
#include "CRezMapWindow.h"
#include "RezillaConstants.h"

#include <LView.h>
#include <UDrawingState.h>
#include <UEnvironment.h>
#include <URegions.h>


PP_Begin_Namespace_PowerPlant


// ===========================================================================
// CLASS CRezMapDragDrop
// ===========================================================================
//	Mix-in class for adding Drag and Drop support to a RezMapTable

// ---------------------------------------------------------------------------
//	¥ CRezMapDragDrop						Constructor				  [public]
// ---------------------------------------------------------------------------
// inMacWindow is the Toolbox window containing the DragAndDrop.
// It may be nil if the DragAndDrop is not in a window (eg if printing
// the DragAndDrop).
// inPane is the PowerPlant Pane associated with the DragAndDrop.
// The drop area of the DragAndDrop is the Frame of the Pane.

CRezMapDragDrop::CRezMapDragDrop(
	WindowPtr	inMacWindow,
	LPane*		inPane)
	
	: LDragAndDrop(inMacWindow, inPane)
{
	mHilitePenState.pnLoc = Point_00;
	mHilitePenState.pnSize.h = kRzilDragHiliteSize;
	mHilitePenState.pnSize.v = kRzilDragHiliteSize;
	mHilitePenState.pnMode = patCopy;
	UQDGlobals::GetBlackPat(&mHilitePenState.pnPat);
}


// ---------------------------------------------------------------------------
//	¥ ~CRezMapDragDrop						Destructor				  [public]
// ---------------------------------------------------------------------------

CRezMapDragDrop::~CRezMapDragDrop()
{
}


// ---------------------------------------------------------------------------
//	¥ PointInDropArea												  [public]
// ---------------------------------------------------------------------------
//	Return whether a Point, in Global coords, is inside a DropArea

Boolean
CRezMapDragDrop::PointInDropArea(
	Point	inPoint)
{
	mPane->GlobalToPortPoint(inPoint);
	return mPane->IsHitBy(inPoint.h, inPoint.v);
}


// ---------------------------------------------------------------------------
//	¥ FocusDropArea													  [public]
// ---------------------------------------------------------------------------
//	Set up local coordinate system and clipping region for a DropArea

void
CRezMapDragDrop::FocusDropArea()
{
	mPane->FocusDraw();
}


// ---------------------------------------------------------------------------
//	¥ HiliteDropArea											   [protected]
// ---------------------------------------------------------------------------
//	Hilite a DropArea to indicate that it can accept the current Drag
//
//	For a DragAndDrop, the drop area is the Frame of its associated
//	Pane inset by one pixel to account for the border which usually
//	surrounds a Drop-capable Pane.

void
CRezMapDragDrop::HiliteDropArea(
	DragReference	inDragRef)
{
	StColorPenState	savePenState;
	Rect		dropRect;
	RGBColor	theForeColor = kRzilDragHiliteColor;
	RGBColor	theBackColor = Color_White;

	mPane->ApplyForeAndBackColors();

	mPane->CalcLocalFrameRect(dropRect);
	::SetPenState(&mHilitePenState);
	::RGBForeColor(&theForeColor);
	::RGBBackColor(&theBackColor);
	::MacFrameRect(&dropRect);
}


// ---------------------------------------------------------------------------
//	¥ UnhiliteDropArea											   [protected]
// ---------------------------------------------------------------------------
//	Unhilite a DropArea when a drag leaves the area

void
CRezMapDragDrop::UnhiliteDropArea(
	DragReference	inDragRef)
{
	StColorPenState	savePenState;
	Rect		dropRect;
	RGBColor	theForeColor = Color_White;
	RGBColor	theBackColor = Color_White;

	mPane->ApplyForeAndBackColors();

	mPane->CalcLocalFrameRect(dropRect);
	::SetPenState(&mHilitePenState);
	::RGBForeColor(&theForeColor);
	::RGBBackColor(&theBackColor);
	::MacFrameRect(&dropRect);
}


// ---------------------------------------------------------------------------
//	¥ MySendDataProc											   [protected]
// ---------------------------------------------------------------------------

pascal OSErr
CRezMapDragDrop::MySendDataProc(FlavorType theType,    
							   void * dragSendRefCon,    
							   DragItemRef theItemRef,    
							   DragRef theDrag)
{
	return noErr;
}



// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// =====================================
//  CLASS StDragSendDataUPP
// =====================================

// ---------------------------------------------------------------------------
//	¥ StDragSendDataUPP							Constructor			  [public]
// ---------------------------------------------------------------------------

//	Constructor allocates and installs a DragSendDataUPP
//	Destructor removes and disposes of it

StDragSendDataUPP::StDragSendDataUPP(
	DragRef           	inDragRef,	 
	DragSendDataProcPtr	inProcPtr,
	WindowPtr			inWindow,
	void*				inRefCon)
{
	// Dispose of the previous send data proc
	if (mSendDataUPP != nil) {
		DisposeDragSendDataUPP(mSendDataUPP);
		mSendDataUPP = nil;
	}
	mWindow = inWindow;
	
	if (inProcPtr != nil) {
		mSendDataUPP = NewDragSendDataUPP(inProcPtr);
		// 		::InstallReceiveHandler(mSendDataUPP, inWindow, inRefCon);
		OSErr error = SetDragSendProc(inDragRef, mSendDataUPP, nil);
	}
}


// ---------------------------------------------------------------------------
//	¥ ~StDragSendDataUPP					Destructor				  [public]
// ---------------------------------------------------------------------------

StDragSendDataUPP::~StDragSendDataUPP()
{
	if (mSendDataUPP != nil) {
// 		::RemoveReceiveHandler(mSendDataUPP, mWindow);
		::DisposeDragSendDataUPP(mSendDataUPP);
	}
}


// // ---------------------------------------------------------------------------
// //	¥ SetSendDataProc									[public, virtual]
// // ---------------------------------------------------------------------------
// //	Allows to specify an own data sending code.  
// //	Disposes of the existing SendDataProc, if any. 
// 
// void
// CRezMapDragDrop::SetSendDataProc(DragRef inDragRef, DragSendDataProcPtr inSendData )
// {
// 	if (inSendData != nil) {
// 		// Dispose of the previous send data proc
// 		if (mSendDataUPP != nil) {
// 			::DisposeDragSendDataUPP(mSendDataUPP);
// 			mSendDataUPP = nil;
// 		}
// 
// 		mSendDataUPP = ::NewDragSendDataUPP( inSendData );
// 		ThrowIfNil_(mSendDataUPP);
// 		
// 		OSErr error = ::SetDragSendProc(inDragRef, &mSendDataUPP, nil);
// 	}
// }


PP_End_Namespace_PowerPlant
