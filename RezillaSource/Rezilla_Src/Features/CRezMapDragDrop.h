// ===========================================================================
// CRezMapDragDrop.h					
//                       Created: 2003-05-30 22:23:58
//             Last modification: 2004-02-22 19:29:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRezMapDragDrop
#define _H_CRezMapDragDrop
#pragma once

#include <TArray.h>
#include <UMemoryMgr.h>

#include <LDragAndDrop.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


class	CRezMapDragDrop : public LDragAndDrop {
public:
						CRezMapDragDrop(
								WindowPtr	inMacWindow,
								LPane*		inPane);

	virtual				~CRezMapDragDrop();

	virtual Boolean		PointInDropArea( Point inGlobalPt );
	
	virtual void		FocusDropArea();

	static pascal OSErr	MySendDataProc(    
							   FlavorType theType,    
							   void * dragSendRefCon,    
							   DragItemRef theItemRef,    
							   DragRef theDrag);
	
protected:

	PenState	mHilitePenState;

	virtual void		HiliteDropArea( DragReference inDragRef );
	
	virtual void		UnhiliteDropArea( DragReference inDragRef );
};



#pragma mark -

// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StDragSendDataUPP
// ---------------------------------------------------------------------------

class StDragSendDataUPP {
public:
			StDragSendDataUPP(
						DragRef           	inDragRef,	 
						DragSendDataProcPtr	inProcPtr,
						WindowPtr			inWindow,
						void*				inRefCon);
					
			~StDragSendDataUPP();
			
			operator DragSendDataUPP()	{ return mSendDataUPP; }
			
protected:
	DragSendDataUPP		mSendDataUPP;
	WindowPtr			mWindow;
};



// class	LDropArea {
// public:
// 						LDropArea( WindowPtr inWindow );
// 
// 	virtual				~LDropArea();
// 
// 						// Pure Virtual. Concrete subclasses MUST override
// 	virtual Boolean		PointInDropArea( Point inGlobalPt) = 0;
// 
// 	virtual void		FocusDropArea();
// 
// 	static bool			DragAndDropIsPresent();
// 
// 	static void			RemoveHandlers();
// 
// protected:
// 	WindowPtr	mDragWindow;
// 	DragRef		mAcceptableDrag;
// 	Boolean		mCanAcceptCurrentDrag;
// 	Boolean		mIsHilited;
// 
// 	virtual void		HiliteDropArea( DragReference inDragRef );
// 	
// 	virtual void		UnhiliteDropArea( DragReference inDragRef );
// 
// 	virtual Boolean		DragIsAcceptable( DragReference inDragRef );
// 	
// 	virtual Boolean		ItemIsAcceptable(
// 								DragReference		inDragRef,
// 								ItemReference		inItemRef);
// 
// 	virtual void		EnterDropArea(
// 								DragReference		inDragRef,
// 								Boolean				inDragHasLeftSender);
// 								
// 	virtual void		LeaveDropArea( DragReference inDragRef );
// 								
// 	virtual void		InsideDropArea( DragReference inDragRef );
// 
// 	virtual void		DoDragReceive( DragReference inDragRef );
// 	
// 	virtual void		ReceiveDragItem(
// 								DragReference		inDragRef,
// 								DragAttributes		inDragAttrs,
// 								ItemReference		inItemRef,
// 								Rect&				inItemBounds);
// 
// 	virtual void		DoDragSendData(
// 								FlavorType			inFlavor,
// 								ItemReference		inItemRef,
// 								DragReference		inDragRef);
// 
// 	virtual void		DoDragInput(
// 								Point*				ioMouse,
// 								SInt16*				ioModifiers,
// 								DragReference		inDragRef);
// 
// 	virtual void		DoDragDrawing(
// 								DragRegionMessage	inMessage,
// 								RgnHandle			inShowRgn,
// 								Point				inShowOrigin,
// 								RgnHandle			inHideRgn,
// 								Point				inHideOrigin,
// 								DragReference		inDragRef);
// 
// 	// === Static Members ===
// 
// 
// 	static	StDeleter< TArray<SDropAreaEntry> >	sDropAreaList;
// 	static	LDropArea*							sCurrentDropArea;
// 	static	bool								sDragHasLeftSender;
// 
// 	static void			AddDropArea(
// 								LDropArea*			inDropArea,
// 								WindowPtr			inMacWindow);
// 								
// 	static void			RemoveDropArea(
// 								LDropArea*			inDropArea,
// 								WindowPtr			inMacWindow);
// 								
// 	static LDropArea*	FindDropArea(
// 								WindowPtr			inMacWindow,
// 								Point				inGlobalPoint,
// 								DragReference		inDragRef);
// 
// 	static void			InTrackingWindow(
// 								WindowPtr			inMacWindow,
// 								DragReference		inDragRef);
// 
// 	static pascal OSErr	HandleDragTracking(
// 								DragTrackingMessage	inMessage,
// 								WindowPtr			inMacWindow,
// 								void*				inRefCon,
// 								DragReference		inDragRef);
// 
// 	static pascal OSErr	HandleDragReceive(
// 								WindowPtr			inMacWindow,
// 								void*				inRefCon,
// 								DragReference		inDragRef);
// 
// 	static pascal OSErr	HandleDragSendData(
// 								FlavorType			inFlavor,
// 								void*				inRefCon,
// 								ItemReference		inItemRef,
// 								DragReference		inDragRef);
// 
// 	static pascal OSErr	HandleDragInput(
// 								Point*				ioMouse,
// 								SInt16*				ioModifiers,
// 								void*				inRefCon,
// 								DragReference		inDragRef);
// 
// 	static pascal OSErr	HandleDragDrawing(
// 								DragRegionMessage	inMessage,
// 								RgnHandle			inShowRgn,
// 								Point				inShowOrigin,
// 								RgnHandle			inHideRgn,
// 								Point				inHideOrigin,
// 								void*				inRefCon,
// 								DragReference		inDragRef);
// };
// 

// ---------------------------------------------------------------------------


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
