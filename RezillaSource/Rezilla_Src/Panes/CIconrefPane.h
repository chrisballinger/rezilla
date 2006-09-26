// ===========================================================================
// CIconrefPane.h
// 
//                       Created : 2006-09-26 13:19:49
//             Last modification : 2006-09-26 13:22:51
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CIconrefPane
#define _H_CIconrefPane
#pragma once

#include <LPane.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CIconrefPane : public LPane {
public:
	enum { class_ID = FOUR_CHAR_CODE('IrfP') };

						CIconrefPane();

						CIconrefPane(
									 const SPaneInfo&	inPaneInfo,
									 IconAlignmentType	inAlignment = kAlignNone,
									 IconTransformType	inTransform = kTransformNone);

						CIconrefPane( LStream* inStream );

	virtual				~CIconrefPane();

	virtual void		DrawSelf();

	IconRef				GetIconRef() { return mIconRef;}
	void				SetIconRef(IconRef inIconRef) {mIconRef = inIconRef;}
	
	IconAlignmentType	GetAlignment() { return mAlignment;}
	void				SetAlignment(IconAlignmentType inAlignment) {mAlignment = inAlignment;}

	IconTransformType	GetTransform() { return mTransform;}
	void				SetTransform(IconTransformType inTransform) {mTransform = inTransform;}


protected:
	IconRef				mIconRef;
	IconAlignmentType	mAlignment;
	IconTransformType	mTransform;

};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
