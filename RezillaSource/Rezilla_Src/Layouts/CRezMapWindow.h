// ===========================================================================
// CRezMapWindow.h				
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2003-04-29 07:18:18
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>

class LFile;
class CRezMapTable;
class CRezMapDoc;
class LStaticText;

class CRezMapWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'RzMW' };

									CRezMapWindow();
									CRezMapWindow( const SWindowInfo &inWindowInfo );
									CRezMapWindow( ResIDT inWINDid,
										UInt32 inAttributes, LCommander *inSuperCommander );
									CRezMapWindow( LStream *inStream );
									~CRezMapWindow();

// 	virtual void			FindCommandStatus(
// 								CommandT	inCommand,
// 								Boolean&	outEnabled,
// 								Boolean&	outUsesMark,
// 								UInt16&		outMark,
// 								Str255		outName);

	virtual void			ListenToMessage( MessageT inMessage,void *ioParam);
// 	void					InstallText(FSSpec *inFileSpec, SInt32 inSide);
	
	virtual Boolean			HandleKeyPress( const EventRecord&	inKeyEvent);

	virtual CRezMapTable*	GetRezMapTable() { return mRezMapTable;}
	void					SetRezMapTable(CRezMapTable* theRezMapTable) {mRezMapTable = theRezMapTable ;}

	virtual CRezMapDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CRezMapDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

	void					InstallCountTypeValue(short inCount);
	void					InstallCountRezValue(short inCount);
	void					InstallWhichForkField();
	void					UpdateCountFields();
	
protected:
	CRezMapTable *		mRezMapTable;
	CRezMapDoc *		mOwnerDoc;
	LStaticText *		mCountTypeField;
	LStaticText *		mCountRezField;
	
	virtual void		FinishCreateSelf();
// 	Boolean				AskReplaceAll(SInt32 inSide);
};



