// ===========================================================================
// CIconTextAction.h
//                       Created: 2004-12-11 18:57:12
//             Last modification: 2004-12-14 18:57:12
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CIconTextAction
#define _H_CIconTextAction
#pragma once

#include "CIconActions.h"
#include "UTextTraits.h"


// ---------------------------------------------------------------------------
// 	CIconTextAction 
// ---------------------------------------------------------------------------

class CIconTextAction : public CIconTrackingPaintAction, public LBroadcaster
{
	public:
							CIconTextAction( const SPaintAction & );
		virtual				~CIconTextAction();
		
		virtual void 		HandleMouseDown( const SMouseDownEvent &inEvent );
		virtual void		HandleKeyDown( const EventRecord &inEvent );
		virtual void		Idle();
		
		virtual void		CloseEditSession();
		virtual void		ChangeTextTraits( const TextTraitsRecord & );
		virtual void		UndoSelf();
		
		virtual void		DrawInsertionPoint( Boolean inDraw = true );
		
		// These are in CIconTextActionCmds.cp
		static Boolean		FindCommandStatus( 
								const TextTraitsRecord &inTraits,
								CommandT inCommand, Boolean &outEnabled, 
								Boolean &outUsesMark, UInt16 &outMark, 
								Str255 outName, LMenu *inFontMenu );
								
		static Boolean		ObeyCommand( 	CIcon_EditorWindow *inPaintView,
											CIconTextAction *inTextAction,
											MessageT inMessage, 
											TextTraitsRecord *ioRec,
											Boolean *outChanged );
									
	protected:
		TEHandle			mText;
		COffscreen			*mTextBuffer;
		
		COffscreen			*mImageBuffer, *mUndoBuffer;
		SInt32				mImageWidth, mImageHeight;
				
		SInt32				mTextLeft, mTextTop;
		SInt32				mCurrentH, mCurrentV;
		
		Boolean				mDrawnInsertionPoint;
		UInt32				mNextInsertionTime;
		
		TextTraitsRecord	mTextTraits;
		FontInfo			mFontInfo;
		
		virtual void		CopyTextBufferToMainBuffer();
		virtual void		RestoreMainBufferFromUndoBuffer();
		virtual void		CopyMainBufferToCanvas( Rect *inDestR  = nil );
				
		virtual Boolean		GetRectRelativeToImageBuffer( Rect *outR );
		virtual Boolean		GetRectRelativeToTextBuffer( Rect *outR );
		virtual Boolean 	GetInsertionPoint( Rect *outR );
		
		virtual void		CopyAndColorize( 	COffscreen *inSource, COffscreen *inDest,
												const Rect &inSourceR, const Rect &inDestR,
												RGBColor &inRGBColor );
		virtual SInt32		CalcTextAreaHeight();
};

#endif // _H_CIconTextAction
