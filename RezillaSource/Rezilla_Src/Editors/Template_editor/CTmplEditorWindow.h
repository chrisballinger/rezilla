// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-12 15:16:10
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

class CTmplEditorDoc;
class CRezObj;


class CTmplEditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'TmpW' };

							CTmplEditorWindow();
							CTmplEditorWindow( const SWindowInfo &inWindowInfo );
							CTmplEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CTmplEditorWindow( LStream *inStream );
							~CTmplEditorWindow();

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

	void			ParseTemplate(Handle inHandle);
	Handle			ReadValues();
	
	Boolean			IsDirty();
		
	void			InstallReadOnlyIcon();

	virtual SInt32		GetCurrFirstID() { return mCurrFirstID;}
	void				SetCurrFirstID(SInt32 theCurrFirstLine) {mCurrFirstID = theCurrFirstLine ;}

// 	virtual SInt32		GetCurrentSubView() { return mCurrentSubView;}
// 	void				SetCurrentSubView(SInt32 inCurrentSubView) {mCurrentSubView = inCurrentSubView;}

protected:
	LView *				mContentsView;
	SInt32				mCurrFirstID;
	SInt32				mCurrentItemID;
	SInt32				mItemsCOunt;
	
	virtual void		FinishCreateSelf();
};


