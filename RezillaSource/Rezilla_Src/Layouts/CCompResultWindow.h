// ===========================================================================
// CCompResultWindow.h				
// 
//                       Created: 2004-03-02 14:18:16
//             Last modification: 2004-03-05 14:59:02
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LWindow.h>
#include <LListener.h>


class CRezObj;
class LScrollBar;
class CRezCompare;
class CRezTypId;
class CHexDataWE;
class CBroadcasterTableView;

enum
{	
	compare_oldhexpane = 0,
	compare_newhexpane
};

// 'RcrW': Rez comparison result window

class CCompResultWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'RcrW' };

							CCompResultWindow();
							CCompResultWindow( const SWindowInfo &inWindowInfo );
							CCompResultWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CCompResultWindow( LStream *inStream );
							~CCompResultWindow();

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	void			DoClose();

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);


	Boolean			IsDirty();
	
	void			FillTableView( TArray<CRezTypId *> inList, SInt16 inWhichList);
	
		
protected:
	CRezCompare *			mRezCompare;
	CHexDataWE *			mOldHexDataWE;
	CHexDataWE *			mNewHexDataWE;
	CBroadcasterTableView *	mOnlyOldTable;
	CBroadcasterTableView *	mOnlyNewTable;
	CBroadcasterTableView *	mDifferTable;
	
	
	virtual void		FinishCreateSelf();
};



