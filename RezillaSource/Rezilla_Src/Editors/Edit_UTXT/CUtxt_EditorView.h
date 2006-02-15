// ===========================================================================
// CUtxt_EditorView.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-07-03 15:26:20
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// ===========================================================================

#ifndef _H_CUtxt_EditorView
#define _H_CUtxt_EditorView
#pragma once

#include <LTextEditView.h>
#include <LMLTEPane.h>
#include <LPeriodical.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CUtxt_EditorWindow;

// CAVEAT: LMLTEPane inherits from LPeriodical if PP_MLTE_Manual_Idle
// is defined which basically means CarbonLib 1.3 maximum. If it is not 
// the case, derive here. SpedTime is needed for the bytes length field.

#if PP_MLTE_Manual_Idle

class CUtxt_EditorView : public LMLTEPane {

#else

class CUtxt_EditorView : public LMLTEPane,
						public LPeriodical {

#endif

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

// 	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );

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
