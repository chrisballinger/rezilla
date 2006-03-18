// ===========================================================================
// TPickerView.h
// 
//                       Created: 2006-02-24 09:49:42
//             Last modification: 2006-03-16 06:05:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CPickerView.h"
#include "RezillaConstants.h"

#include <LStaticText.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif


PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

template <class T> class TPickerView : public CPickerView {
public:
						TPickerView(SInt16 inStampWidth, SInt16 inStampHeight, ResIDT inID)
							: CPickerView(inID) 
								{
									InitPickerView(inStampWidth, inStampHeight, inID);
								}

						~TPickerView() {}

protected:
	T *					mStampView;
	
private:

// ---------------------------------------------------------------------------
//   InitPickerView
// ---------------------------------------------------------------------------
void 
InitPickerView(SInt16 inStampWidth, SInt16 inStampHeight, ResIDT inID)
{
	SPaneInfo	pi;
	SViewInfo	vi;
	SInt16		theWidth, theHeight;
	SInt16		horizMargin = kPickerViewHorizMargin;
	SInt16		vertMargin = kPickerViewVertMargin;
	
	theWidth = inStampWidth + 2 * kPickerViewHorizMargin;
	theHeight = inStampHeight + 2 * kPickerViewVertMargin + kPickerViewIDFieldHeight;
	
	if (theWidth < kPickerViewMinWidth) {
		theWidth = kPickerViewMinWidth;
		horizMargin = (kPickerViewMinWidth - inStampWidth)/2;
	} 
	if (theHeight < kPickerViewMinHeight) {
		theHeight = kPickerViewMinHeight;
		vertMargin = (kPickerViewMinHeight - inStampHeight -kPickerViewIDFieldHeight)/2;
	} 
	
	ResizeFrameTo(theWidth, theHeight, false);
	ResizeImageTo(theWidth, theHeight, false);
	
	pi.paneID			= 0;
	pi.width			= inStampWidth;
	pi.height			= inStampHeight;
	pi.visible			= true;
	pi.enabled			= true;
	pi.bindings.top		= false;
	pi.bindings.left	= false;
	pi.bindings.bottom	= false;
	pi.bindings.right	= false;
	pi.left				= horizMargin;
	pi.top				= vertMargin;
	pi.userCon			= 0;
	pi.superView		= this;
	
	vi.imageSize.width		= pi.width;
	vi.imageSize.height		= pi.height;
	vi.scrollPos.h			= vi.scrollPos.v	= 0;
	vi.scrollUnit.h			= theWidth;
	vi.scrollUnit.v			= theHeight;
	vi.reconcileOverhang	= false;

	mStampView = new T(pi, vi);
	ThrowIfNil_(mStampView);

	pi.top		= pi.height + vertMargin;
	pi.left		= 2;
	pi.width	= theWidth - 4;
	pi.height	= kPickerViewIDFieldHeight;
	
	mIDField = new LStaticText(pi, "\p", Txtr_MonacoBlackNineCenter);
	ThrowIfNil_(mIDField);

	SetIDField(inID);
}


};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

