// ===========================================================================
// CEditorWindow.h				
// 
//                       Created: 2004-06-10 14:44:33
//             Last modification: 2004-11-06 07:24:32
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "UResources.h"

#include <LWindow.h>

class CEditorDoc;
class CRezObj;


class CEditorWindow : public LWindow, public LListener {
public:
	enum { class_ID = 'EdiW' };

							CEditorWindow();
							CEditorWindow( const SWindowInfo &inWindowInfo );
							CEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CEditorWindow( LStream *inStream );
							~CEditorWindow();

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

	virtual void	RevertContents();
	
	virtual Boolean	IsDirty();

	virtual void	SetDirty(Boolean inDirty);

	void			InstallReadOnlyIcon();

	virtual CEditorDoc*		GetOwnerDoc() { return mOwnerDoc;}
	void					SetOwnerDoc(CEditorDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

protected:
	CEditorDoc *		mOwnerDoc;
	Boolean				mIsDirty;

	virtual void		FinishCreateSelf();
};


