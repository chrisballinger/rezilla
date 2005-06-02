// ===========================================================================
// CHexEditorWindow.h				
// 
//                       Created: 2003-05-02 07:33:06
//             Last modification: 2005-06-02 11:33:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
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

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);
	
	virtual void	SetLineValues();
	virtual void	SetLineRange(SInt32 inStart, SInt32 inEnd);
	
	virtual void	SetOffsetValues();
	virtual void	SetOffsetRange(SInt32 inStart, SInt32 inEnd);
	
	void			ClearFields();

	void			InstallResourceData(Handle inHandle);
	
	virtual SInt32	InstallContentsFromLine(SInt32 inFromLine);

	Boolean			IsDirty();
		
	void			DisplayBothSelections(SInt32 inStart, SInt32 inEnd);

	// AppleEvents
// 	virtual void	GetAEProperty(
// 								DescType			inProperty,
// 								const AEDesc&		inRequestedType,
// 								AEDesc&				outPropertyDesc) const;
	
// 	virtual void		GetSubModelByPosition(
// 								DescType			inModelID,
// 								SInt32				inPosition,
// 								AEDesc&				outToken) const;

// 	virtual bool	AEPropertyExists(
// 								DescType		inProperty) const;
	
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


