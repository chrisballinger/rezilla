// ===========================================================================
// CAete_EditorWindow.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-02-05 14:41:39
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

	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void		ListenToMessage( MessageT inMessage,void *ioParam);
	
	OSErr				InstallAete(Handle inHandle);
	void				RetrieveAete(CAeteStream * outStream);
		
	virtual void		RevertContents();

	CAete *				GetAete() {return mAete;}

	static LMenu		*sAeteMenu;
	static Str31		sAddEventStr, sAddClassStr, sAddCompOpStr, sAddEnumerationStr,
						sRemoveEventStr, sRemoveClassStr, sRemoveCompOpStr, sRemoveEnumerationStr;

protected:
	CAete *					mAete;
	UInt8					mCurrentPanel;
	LPopupButton *			mSuitesPopup;
	LView					*mEventPane,
							*mClassPane,
							*mCompOpPane,
							*mEnumerationPane;
	Boolean					mIgnoreSliderMessage;
	
	virtual void		FinishCreateSelf();
	virtual void		PutOnDuty(LCommander *inNewTarget);
	virtual void		TakeOffDuty();

private:

	ArrayIndexT			GetCurrentIndex(SInt8 inKind);
	void				SetCurrentIndex(SInt8 inKind, ArrayIndexT inIndex);
	SInt32				GetCurrentCount(SInt8 inKind);
	
	void				InstallResourceInfo();
	void				InstallSuiteValues();
	void				InstallPanelValues();
	void				InstallEventValues(CAeteEvent * inEvent);
	void				InstallParameterValues(CAeteParameter* inParameter);
	void				InstallClassValues(CAeteClass * inClass);
	void				InstallPropertyValues(CAeteProperty * inProperty);
	void				InstallElementValues(CAeteElement * inElement);
	void				InstallKeyFormValues(OSType inKeyForm);
	void				InstallCompOpValues(CAeteCompOp * inCompOp);
	void				InstallEnumerationValues(CAeteEnumeration * inEnum);
	void				InstallEnumeratorValues(AeteEnumerator inEnumerator);
	void				InstallFlags(SInt32 inKind, UInt16 inFlags);
	
	void				RetrieveResourceInfo();
	void				RetrieveSuiteValues();
	void				RetrievePanelValues();
	void				RetrieveEventValues(CAeteEvent * inEvent);
	void				RetrieveParameterValues(CAeteParameter* inParameter);
	void				RetrieveClassValues(CAeteClass * inClass);
	void				RetrievePropertyValues(CAeteProperty * inProperty);
	void				RetrieveElementValues(CAeteElement * inElement);
	void				RetrieveKeyFormValues(OSType & outKeyForm);
	void				RetrieveCompOpValues(CAeteCompOp * inCompOp);
	void				RetrieveEnumerationValues(CAeteEnumeration * inEnum);
	void				RetrieveEnumeratorValues(AeteEnumerator & outEnumerator);
	void				RetrieveFlags(SInt32 inKind, UInt16 & outFlags);

	void *				FindCurrentObject(SInt8 inKind);
	void				RebuildSuitePopup();
	void				RemoveAeteMenu();
	void				SetIndicator(LStaticText * inIndicator, 
									 SInt32 inValue, 
									 SInt32 inTotal);
	void				UpdateSlider(SInt32 inSliderID, 
									 SInt32 inValue, 
									 SInt32 inTotal, 
									 Boolean inOnlyIndicator = false, 
									 Boolean inIgnoreBroadcast = false);
	void				HandleSliderMessage(SInt32 inKind, SInt32 inValue);
	void				HandleOptionsPopup(SInt32 inKind, SInt32 inIndex);
	
};


#endif
