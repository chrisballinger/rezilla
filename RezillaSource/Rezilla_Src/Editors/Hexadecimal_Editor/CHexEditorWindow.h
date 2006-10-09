// ===========================================================================
// CHexEditorWindow.h				
// 
//                       Created: 2003-05-02 07:33:06
//             Last modification: 2006-10-09 13:59:05
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"
#include "WASTE.h"

class CHexEditorDoc;
class CDualDataView;
class CRangeEditText;
class CRezObj;
// class CSingleScrollBar;


class CHexEditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('HexW') };

							CHexEditorWindow();
							CHexEditorWindow( const SWindowInfo &inWindowInfo );
							CHexEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CHexEditorWindow( LStream *inStream );
							~CHexEditorWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual void	RevertContents();

	virtual void	SetLineValues();
	virtual void	SetLineRange(SInt32 inStart, SInt32 inEnd);
	
	virtual void	SetOffsetValues();
	virtual void	SetOffsetRange(SInt32 inStart, SInt32 inEnd);
	
	void			ClearFields();

	void			InstallResourceData(Handle inHandle);
	
	virtual SInt32	InstallContentsFromLine(SInt32 inFromLine);

	Boolean			IsDirty();
	virtual void	SetDirty(Boolean inDirty);
	
	void			DisplayBothSelections(SInt32 inStart, SInt32 inEnd);

	// AppleEvents
	virtual void	GetAEProperty(
								DescType		inProperty,
								const AEDesc&	inRequestedType,
								AEDesc&			outPropertyDesc) const;

	void			SetAEProperty(
								DescType		inProperty,
								const AEDesc&	inValue,
								AEDesc&			outAEReply);
	
	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	
	// Accessors
	CDualDataView*		GetDualView() { return mDualView;}

protected:
	CDualDataView *		mDualView;
	CRangeEditText *	mLineField;
	CRangeEditText *	mOffsetField;
	
	virtual void		FinishCreateSelf();

	virtual LModelObject*	GetModelProperty(
									DescType		inProperty) const;

};


