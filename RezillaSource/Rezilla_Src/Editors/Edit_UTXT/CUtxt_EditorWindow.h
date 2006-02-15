// ===========================================================================
// CUtxt_EditorWindow.h
// 
//                       Created: 2004-12-08 18:21:21
//             Last modification: 2005-01-15 12:16:25
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
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

	void			InstallText(Handle inTextHandle);

	Boolean			IsDirty();
	
	void			SetLengthField(ByteCount theLength);
					
	CUtxt_EditorView *	GetContentsView() const { return mContentsView;}

protected:
	CUtxt_EditorView *	mContentsView;
	LStaticText *		mLengthField;
	ByteCount			mOldSize;
	
	virtual void	FinishCreateSelf();
	
private:

};


