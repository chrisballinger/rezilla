// ===========================================================================
// CAete_EditorWindow.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2004-07-01 18:12:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAete_EditorWindow
#define _H_CAete_EditorWindow
#pragma once

#include "CEditorWindow.h"

#include <stdarg.h>

class LPageController;
class LMultiPanelView;
class LSlider;
class LPopupButton;
class LScrollerView;
class LStaticText;
class CAete;


class CAete_EditorWindow : public CEditorWindow {
public:
	enum { class_ID = FOUR_CHAR_CODE('AETW') };

							CAete_EditorWindow();
							CAete_EditorWindow( const SWindowInfo &inWindowInfo );
							CAete_EditorWindow( ResIDT inWINDid,
											   UInt32 inAttributes, 
											   LCommander *inSuperCommander );
							CAete_EditorWindow( LStream *inStream );
							~CAete_EditorWindow();

	virtual void		FindCommandStatus(
								CommandT			inCommand,
								Boolean&			outEnabled,
								Boolean&			outUsesMark,
								UInt16&				outMark,
								Str255				outName);

	virtual void		ListenToMessage( MessageT inMessage,void *ioParam);

// 	virtual void		Activate();
	
	void				InstallAete(Handle inHandle);

	void				FillSuitePopup();
	void				InstallSuiteValues();
	void				InstallPanelValues();
	
	void				InstallValuesInPane();
	void				RetrieveValuesFromPane();
		
	// Accessors

	static LMenu		*sAeteMenu;

protected:
	CAete *					mAete;
	UInt8					mCurrentPanel;
	LPageController *		mController;
	LMultiPanelView *		mMultiPanel;
	LSlider *				mMainSlider;
	LStaticText *			mIndicator;
	LPopupButton *			mSuitesPopup;
	
	virtual void		FinishCreateSelf();
	virtual void		PutOnDuty(LCommander *inNewTarget);
	virtual void		TakeOffDuty();

private:
};


#endif
