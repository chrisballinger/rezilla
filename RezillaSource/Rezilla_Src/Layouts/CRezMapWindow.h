// ===========================================================================
// CRezMapWindow.h				
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2005-05-14 12:19:40
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
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

	// Apple events
	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	virtual CRezMapTable*	GetRezMapTable() { return mRezMapTable;}
	void					SetRezMapTable(CRezMapTable* theRezMapTable) {mRezMapTable = theRezMapTable ;}

	virtual CRezMapDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CRezMapDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

	long					GetCountTypeField() const;
	long					GetCountRezField() const;
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


