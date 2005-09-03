// ===========================================================================
// CSTRx_EditorWindow.h
// 
//                       Created: 2005-08-31 18:26:24
//             Last modification: 2005-09-03 07:22:44
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"


class CIndexedEditField;
class LEditText;
class LStaticText;
class LHandleStream;
class LTabGroupView;


class CSTRx_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('STRW') };

							CSTRx_EditorWindow();
							CSTRx_EditorWindow( const SWindowInfo &inWindowInfo );
							CSTRx_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CSTRx_EditorWindow( LStream *inStream );
							~CSTRx_EditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT	inCommand,
								Boolean&	outEnabled,
								Boolean&	outUsesMark,
								UInt16&		outMark,
								Str255		outName);

	virtual Boolean	ObeyCommand(
							CommandT		inCommand,
							void*			ioParam);

	OSErr			InstallResourceData(Handle inHandle);
	
	virtual void	RevertContents();

	UInt16			GetFirstSelected();
	
	LView*			GetContentsView() const { return mContentsView;}
	
	static SPaneInfo 			sPaneInfo;
	static SViewInfo			sViewInfo;

protected:
	LHandleStream *				mOutStream;
	LView *						mContentsView;
// 	LTabGroupView *				mTGV;
	TArray<CIndexedEditField*>	mIndexedFields;

	virtual void	FinishCreateSelf();

private:	
	void			AddStringItem(Str255 inString);
	void			InsertStringItemAtIndex(UInt16 index, Str255 inString);
	void			RecalcPositionsFrom(UInt16 index);
	void			RecalcAllPositions();
	UInt16			DeleteSelected();
	
};


