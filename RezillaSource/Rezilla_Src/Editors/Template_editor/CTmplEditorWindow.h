// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-06-22 18:48:48
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
#include "RezillaConstants.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
/* #include <LActiveScroller.h> */

class CTmplEditorDoc;
class CRezObj;
class CTmplList;
class LStaticText;
class LScrollerView;


enum {
	tmpl_titleYesNo = 0,
	tmpl_titleOnOff
};


class CTmplEditorWindow : public CEditorWindow {
public:
	enum { class_ID = 'TmpW' };
	friend class CTmplList;

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

	void			ParseDataWithTemplate(Handle inHandle);
	Handle			RetrieveDataWithTemplate();
	
	Boolean			IsDirty();
		
	void			InstallReadOnlyIcon();

	void			CreateTemplateStream();
		
	LView*			GetContentsView() const { return mContentsView;}


protected:
	LView *				mContentsView;
	LScrollerView *		mContentsScroller;
	SInt32				mYCoord;
	SInt32				mCurrentID;
	SInt32				mLastID;
	SInt32				mIndent;
	short				mItemsCount;
	Boolean				mStopList;
	SPaneInfo			mEditPaneInfo;
	SPaneInfo			mStaticPaneInfo;
	SPaneInfo			mRgvPaneInfo;
	SPaneInfo			mRadioPaneInfo;
	SPaneInfo			mRectLabelInfo;
	SPaneInfo			mRectPaneInfo;
	SPaneInfo			mScrollPaneInfo;
	SPaneInfo			mTgbPaneInfo;
	SPaneInfo			mWastePaneInfo;
	SPaneInfo			mPushPaneInfo;
	LHandleStream *		mTemplateStream;
	LHandleStream *		mRezStream;
	LHandleStream *		mOutStream;
	ResIDT				mLeftLabelTraitsID;
	ResIDT				mRightLabelTraitsID;
	ResIDT				mHeaderTraitsID;
	ResIDT				mEditTraitsID;

	virtual void	FinishCreateSelf();

private:
	OSErr			ParseDataForType(ResType inType, Str255 inString);
	OSErr			RetrieveDataForType(ResType inType);
	
	void			ParseList(SInt32 inStartMark, 
							  ResType inType, 
							  Str255 inLabel, 
							  SInt32 inCount);

	void			RetrieveList(SInt32 inStartMark, 
								 ResType inType, 
								 SInt32 inCount);

	Boolean			EndOfList(ResType inType);
	
	void			AddStaticField(Str255 inLabel, ResIDT inTextTraitsID = Txtr_GenevaTenBoldUlRight);
	
	void			AddEditField(Str255 inValue, 
								OSType inType,
								MessageT inMessage,
								SInt16 inMaxChars, 
								UInt8 inAttributes = 0,
								TEKeyFilterFunc inKeyFilter = NULL);
	
	void			AddBooleanField(Boolean inValue,
									  OSType inType,
									  SInt16 inTitleType);
	
	void			AddWasteField(OSType inType);
	
	void			AddHexDumpField(OSType inType);
	
	void			AddRectField(SInt16 inTop, 
									SInt16 inLeft, 
									SInt16 inBottom, 
									SInt16 inRight, 
									OSType inType,
									MessageT inMessage,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter);

	void			AddListHeaderField(OSType inType, 
								  Str255 inLabel, 
								  short inCount, 
								  Str255 inCountLabel);
	
	ExceptionCode	AlignBytesRead(UInt8 inStep);
	
	ExceptionCode	AlignBytesWrite(UInt8 inStep);
	
	void			DoParseWithTemplate(SInt32 inRecursionMark);
	void			DoRetrieveWithTemplate(SInt32 inRecursionMark);
	
};


