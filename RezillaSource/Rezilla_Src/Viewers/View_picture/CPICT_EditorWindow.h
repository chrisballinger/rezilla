// ===========================================================================
// CPICT_EditorWindow.h
// 
//                       Created: 2004-12-06 14:54:09
//             Last modification: 2004-12-06 20:35:53
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
#include <LActiveScroller.h>


class CPICT_EditorDoc;
class CPICT_EditorView;
class CRezObj;


class CPICT_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'PICW' };

							CPICT_EditorWindow();
							CPICT_EditorWindow( const SWindowInfo &inWindowInfo );
							CPICT_EditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CPICT_EditorWindow( LStream *inStream );
							~CPICT_EditorWindow();

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

	void			InstallPict(Handle inPictHandle);

	void			SetSizeFields(Rect inRect);
		
	CPICT_EditorView *	GetContentsView() const { return mContentsView;}

protected:
	CPICT_EditorView *	mContentsView;

	virtual void	FinishCreateSelf();
	
private:

};


