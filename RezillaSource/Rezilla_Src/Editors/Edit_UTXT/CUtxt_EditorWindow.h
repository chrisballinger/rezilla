// ===========================================================================
// CUtxt_EditorWindow.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-01-08 21:31:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"


class CUtxt_EditorView;
class LStaticText;


class CUtxt_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('UTXW') };

							CUtxt_EditorWindow();
							CUtxt_EditorWindow( const SWindowInfo &inWindowInfo );
							CUtxt_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CUtxt_EditorWindow( LStream *inStream );
							~CUtxt_EditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	void			InstallText(Handle inTextHandle);

	void			SetLengthField();
					
	CUtxt_EditorView *	GetContentsView() const { return mContentsView;}

protected:
	CUtxt_EditorView *	mContentsView;
	LStaticText *		mLengthField;

	virtual void	FinishCreateSelf();
	
private:

};


