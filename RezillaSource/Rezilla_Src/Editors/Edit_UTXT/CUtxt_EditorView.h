// ===========================================================================
// CUtxt_EditorView.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-01-16 12:56:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CUtxt_EditorView
#define _H_CUtxt_EditorView
#pragma once

#include <LTextEditView.h>
#include <LMLTEPane.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CUtxt_EditorWindow;


class CUtxt_EditorView : public LMLTEPane {
public:
	enum { class_ID = FOUR_CHAR_CODE('UTXV') };

								CUtxt_EditorView();
								CUtxt_EditorView( LStream* inStream );
		virtual					~CUtxt_EditorView();

	virtual Boolean			ObeyCommand(
									CommandT			inCommand,
									void*				ioParam);
	
	virtual void 			FindCommandStatus(
									CommandT			inCommand,
									Boolean&			outEnabled,
									Boolean&			outUsesMark,
									UInt16&				outMark,
									Str255				outName);

	ByteCount				GetDataSize();
	
	OSStatus				CountChanges(ByteCount & outCount);
	
	OSStatus				ResetChangesCount();
	
	void					SetUnicodePtr(
									const void *	inTextP,
									ByteCount		inTextLength);
	
	virtual	void			SpendTime( const EventRecord& inMacEvent );

	virtual Boolean			GetFontSize( Fixed & outSize );
	virtual Boolean			ChangeFontSizeBy( SInt16 inDeltaSize );
	virtual	Boolean			GetFontStyle( Style & outStyle );
	virtual	Boolean			GetFontColor( const RGBColor & inColor) ;
	
	CUtxt_EditorWindow*		GetOwnerWindow() { return mOwnerWindow;}
	void					SetOwnerWindow(CUtxt_EditorWindow* inOwnerWindow) {mOwnerWindow = inOwnerWindow;}

	virtual Handle			GetModifiedText();

	static LMenu		*sUtxtSizeMenu, 
						*sUtxtStyleMenu;  // sUtxtFontMenu

protected:
		CUtxt_EditorWindow *	mOwnerWindow;

		virtual void	FinishCreateSelf();
		virtual void	PutOnDuty(LCommander *inNewTarget);
		virtual void	TakeOffDuty();
		virtual void	RemoveUnicodeMenus();
};



PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
