// ===========================================================================
// CAete_EditorDoc.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-21 10:19:21
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAete_EditorDoc
#define _H_CAete_EditorDoc
#pragma once


#include "CEditorDoc.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant


class CAete_EditorWindow;
class CAeteSuite;
class CAeteStream;


class CAete_EditorDoc : public CEditorDoc {
public:
						CAete_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						
						virtual ~CAete_EditorDoc();

	virtual void			FindCommandStatus( CommandT inCommand,
									Boolean &outEnabled, Boolean &outUsesMark,
									UInt16 &outMark, Str255 outName );

	virtual Boolean			AllowSubRemoval( LCommander* inSub );

	virtual Boolean			IsModified();
	
// 	SInt16					AskSaveChanges(bool	inQuitting);

	virtual StringPtr		GetDescriptor( Str255 outDescriptor ) const;

	CAete_EditorWindow*		GetAeteEditWindow() { return mAeteEditWindow;}

	virtual TArray<CAeteStream *> *		GetAeteStreamsArrayPtr() { return mAeteStreamsArrayPtr;}
	
protected:
	CAete_EditorWindow*			mAeteEditWindow;

	SInt32						mTotalCount[5];
	SInt32						mCurrCategory;
	TArray<CAeteStream*> *      mAeteStreamsArrayPtr;
	CAeteStream *               mCurrentStreamPtr;
	CAeteSuite *                mCurrentSuitePtr;
	
/* 	virtual Handle		GetModifiedResource(Boolean &releaseIt); */

private:

	void				Initialize();
};



PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

