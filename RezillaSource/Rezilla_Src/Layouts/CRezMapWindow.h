// ===========================================================================
// CRezMapWindow.h				
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2005-03-22 12:53:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2004, 2005
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
	enum { class_ID = FOUR_CHAR_CODE('RzMW') };

									CRezMapWindow();
									CRezMapWindow( const SWindowInfo &inWindowInfo );
									CRezMapWindow( ResIDT inWINDid,
										UInt32 inAttributes, LCommander *inSuperCommander );
									CRezMapWindow( LStream *inStream );
									~CRezMapWindow();

	
	virtual void		ListenToMessage( MessageT inMessage, void *ioParam);

	virtual CRezMapTable*	GetRezMapTable() { return mRezMapTable;}
	void					SetRezMapTable(CRezMapTable* theRezMapTable) {mRezMapTable = theRezMapTable ;}

	virtual CRezMapDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CRezMapDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

	long					GetCountTypeField();
	long					GetCountRezField();
	void					SetCountTypeField(long inCount);
	void					SetCountRezField(long inCount);

	void					InstallWhichForkField();
	void					InstallReadOnlyIcon();
	void					RecalcCountFields();
	
protected:
	CRezMapTable *		mRezMapTable;
	CRezMapDoc *		mOwnerDoc;
	LStaticText *		mCountTypeField;
	LStaticText *		mCountRezField;
	
	virtual void		FinishCreateSelf();
};


