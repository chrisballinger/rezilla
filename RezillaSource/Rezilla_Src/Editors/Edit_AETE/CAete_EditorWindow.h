// ===========================================================================
// CAete_EditorWindow.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-24 14:48:38
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAete_EditorWindow
#define _H_CAete_EditorWindow
#pragma once

#include "CEditorWindow.h"
#include "CAeteStream.h"
#include "CAete.h"
#include "CAeteSuite.h"
#include "CAeteEvent.h"
#include "CAeteParameter.h"
#include "CAeteClass.h"
#include "CAeteProperty.h"
#include "CAeteElement.h"
#include "CAeteCompOp.h"
#include "CAeteEnumeration.h"


class LPageController;
class LMultiPanelView;
class LPopupButton;
class LStaticText;


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
	void				RetrieveAete(CAeteStream * outStream);
	
	void				FillSuitePopup();
	
	void				InstallResourceInfo();
	void				InstallSuiteInfo();
	void				InstallPanelValues();
	void				InstallEventValues(CAeteEvent * inEvent);
	void				InstallParameterValues(CAeteParameter* inParameter);
	void				InstallClassValues(CAeteClass * inClass);
	void				InstallPropertyValues(CAeteProperty * inProperty);
	void				InstallElementValues(CAeteElement * inElement);
	void				InstallCompOpValues(CAeteCompOp * inCompOp);
	void				InstallEnumerationValues(CAeteEnumeration * inEnum);
	void				InstallEnumeratorValues(AeteEnumerator * inEnumerator);

	void *				FindCurrentObject(SInt8 inKind);

	void				RetrieveResourceInfo();
	void				RetrieveSuiteInfo();
	void				RetrievePanelValues();
	void				RetrieveEventValues();
	void				RetrieveClassValues();
	void				RetrieveCompOpValues();
	void				RetrieveEnumerationValues();
		

	static LMenu		*sAeteMenu;
	static Str31		sAddEventStr, sAddClassStr, sAddCompOpStr, sAddEnumerationStr,
						sRemoveEventStr, sRemoveClassStr, sRemoveCompOpStr, sRemoveEnumerationStr;

protected:
	CAete *					mAete;
	UInt8					mCurrentPanel;
	LPageController *		mController;
	LMultiPanelView *		mMultiPanel;
	LPopupButton *			mSuitesPopup;
	LView					*mEventPane,
							*mClassPane,
							*mCompOpPane,
							*mEnumerationPane;
	
	virtual void		FinishCreateSelf();
	virtual void		PutOnDuty(LCommander *inNewTarget);
	virtual void		TakeOffDuty();

private:
	void				SetIndicator(LStaticText * inIndicator, SInt32 inValue, SInt32 inTotal);
	void				UpdateSlider(SInt32 inSliderID, SInt32 inValue, SInt32 inTotal);
	void				SetCurrentIndex(SInt32 inType, SInt32 inIndex);
	
};


#endif
