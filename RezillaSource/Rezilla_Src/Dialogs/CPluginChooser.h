// ===========================================================================
// CPluginChooser.h
// 
//                       Created: 2006-09-25 07:02:55
//             Last modification: 2006-09-25 07:09:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#pragma once


#include <LCommander.h>

class CDragTable;
class CThreeButtonsBox;
class LPopupButton;
class LPopupGroupBox;
class LStaticText;
class LPageController;
class LMultiPanelView;
class LView;
class CRezillaPlugin;


class CPluginChooser : public LCommander {
public:
							CPluginChooser(LCommander * inCommander);
							~CPluginChooser();

	OSErr		RunDialog();
	
protected:
	CThreeButtonsBox *	mDialogBox;
	LPageController*	mPageCtrl;
	LMultiPanelView*	mMultiPanel;
	LView*				mInfoPane;
	LView*				mOrderPane;
	CDragTable *		mPluginOrderTable;
	LPopupButton *		mSupportedTypes;
	LPopupGroupBox *	mInfoPgbx;
	LPopupGroupBox *	mOrderPgbx;
	LStaticText *		mTypeField;
	LStaticText *		mCreatorField;
	LStaticText *		mVersionField;
	LStaticText *		mLoadedField;
	LStaticText *		mHelpField;
	SInt32 				mOrderTypeIndex;
	ResType				mCurrType;	

private:
	void		FinishCreateChooser();
	void		PopulateGroupBoxes();
	void		UpdatePluginInfo(CRezillaPlugin * inPlugin);
	void		UpdateOrderTableForType(ResType inType);
	
};

