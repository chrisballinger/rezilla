// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2004-09-24 08:55:33
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2004
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
class LStaticText;
class LScrollerView;


enum {
	tmpl_titleYesNo = 0,
	tmpl_titleOnOff
};


class CTmplListItemView;
class CWasteEditView;


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

	OSErr			ParseDataWithTemplate(Handle inHandle);
	
	OSErr			RetrieveDataWithTemplate();
	
	Boolean			IsDirty();
	void			SetDirty(Boolean inDirty) {mIsDirty = inDirty;}
		
	void			InstallReadOnlyIcon();

	void			AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta);
	
	LView*			GetContentsView() const { return mContentsView;}
	
	LHandleStream*		GetOutStream() { return mOutStream;}

	static ResIDT		sCommentTraitsID,
						sLeftLabelTraitsID,
						sRightLabelTraitsID,
						sHeaderTraitsID,
						sEditTraitsID;

	static SPaneInfo	sEditPaneInfo,
						sStaticPaneInfo,
						sRgvPaneInfo,
						sRadioPaneInfo,
						sCheckPaneInfo,
						sRectLabelInfo,
						sRectPaneInfo,
						sScrollPaneInfo,
						sTgbPaneInfo,
						sWastePaneInfo,
						sPushPaneInfo,
						sListItemInfo,
						sSeparatorPaneInfo,
						sBevelPaneInfo,
						sColorPaneInfo;
						
	static void			InitPaneInfos();
	
	static Boolean	SplitCaseValue(Str255 inString, Str255 ** outRightPtr);
	
protected:
	LView *				mContentsView;
	LScrollerView *		mContentsScroller;
	SInt32				mYCoord;
	PaneIDT				mCurrentID;
	PaneIDT				mLastID;
	SInt32				mIndent;
	SInt32				mSkipOffset;
	SInt32				mListCountMark;
	ResType				mCountType;
	short				mItemsCount;
	Boolean				mIsDirty;
	Boolean				mFixedCount;
	LHandleStream *		mTemplateStream;
	LHandleStream *		mRezStream;
	LHandleStream *		mOutStream;
	TArray<CWasteEditView *>	mWasteFieldsList;
	TArray<ResType>		mOffsetTypesList;
	TArray<SInt32>		mOffsetMarksList;
	Boolean				mBitSeqInProgress;
	UInt32				mBitSeqValue;
	UInt8				mBitSeqBytesLen;
	SInt8				mBitSeqIndex;
// 	UInt8				mBitSeqMax;

	virtual void	FinishCreateSelf();

	OSErr			CreateTemplateStream();
		
private:
	OSErr			ParseDataForType(ResType inType, Str255 inLabelString, LView * inContainer);
	OSErr			RetrieveDataForType(ResType inType);
	
	OSErr			ParseList(SInt32 inStartMark, 
							  ResType inType, 
							  SInt32 inCount, 
							  LView * inContainer, 
							  PaneIDT inCountPane);

	OSErr			RetrieveList(SInt32 inStartMark, 
								 ResType inType, 
								 SInt32 inCount);

	OSErr			ParseKeyedSection(ResType inType, 
								   Str255 inLabelString, 
								   LView * inContainer);

	OSErr			RetrieveKeyedSection(ResType inType);

	Boolean			EndOfList(ResType inType, OSErr * outError);
	
	void			AddStaticField(OSType inType, 
								   Str255 inLabel, 
								   LView * inContainer, 
								   ResIDT inTextTraitsID = Txtr_GenevaTenBoldUlRight);
	
	void			AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								LView * inContainer);
	
	void			AddBooleanField(Boolean inValue,
									OSType inType,
									SInt16 inTitleType, 
									LView * inContainer);
	
	void			AddBitField(OSType inType,
								   Str255 inLabel,
								   UInt16 inBitCount, 
								   UInt16 inBytesLen,
								   LView * inContainer);
	
	void			AddCheckField(Boolean inValue,
								   OSType inType,
								   LView * inContainer);
	
	void			AddWasteField(OSType inType, 
								  LView * inContainer);
	
	void			AddHexDumpField(OSType inType, 
									LView * inContainer);
	
	void			AddPointField(SInt16 inX, 
									SInt16 inY, 
									OSType inType,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter,
									LView * inContainer);

	void			AddRectField(SInt16 inTop, 
									SInt16 inLeft, 
									SInt16 inBottom, 
									SInt16 inRight, 
									OSType inType,
									SInt16 inMaxChars, 
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter, 
								 	LView * inContainer);

	PaneIDT			AddListHeaderField(Str255 inLabel, 
								   short inCount, 
								   Str255 inCountLabel, 
								   LView * inContainer,
								   Boolean isFixedCount);
	
	CTmplListItemView *	AddListItemView(CTmplListItemView * inPrevListItemView, LView * inContainer);
	
	void			AddSeparatorLine(LView * inContainer);

	void			AddCasePopup(ResType inType, 
									 Str255 inLabel, 
									 SInt32 inStartMark,
									 LView * inContainer);
	
	void			AddEditPopup(Str255 inValue, 
									OSType inType,
									SInt16 inMaxChars, 
									SInt16 inWidth,
									UInt8 inAttributes,
									TEKeyFilterFunc inKeyFilter, 
									ResIDT inResourceID,
									LView * inContainer);
	
	void			AddColorPane(LView * inContainer, 
								RGBColor * inRGB);
	
	ExceptionCode	AlignBytesRead(UInt8 inStep);
	
	ExceptionCode	AlignBytesWrite(UInt8 inStep);
	
	void			BuildFormatString(char * ioString, UInt8 inLength);

	OSErr			BuildScanString(char * inString, char * ioFormat, UInt8 inLength);
	
	OSErr			DoParseWithTemplate(SInt32 inRecursionMark, 
										Boolean inDrawControls, 
										LView * inContainer);

	OSErr			DoRetrieveWithTemplate(SInt32 inRecursionMark, 
										   Boolean inReadControls);
	
	void			RenumberSubPanes(LView * inView, 
									 PaneIDT inOldLastID, 
									 PaneIDT inNewFirstID, 
									 Boolean adding);
	
	void			RecalcPositions(LView * inView, 
									SInt32 inVertPos, 
									SInt32 inPosDelta);

	Boolean			IsValidBitField(OSType inType, 
									Str255 ioString, 
									UInt16 & ioBitsCount, 
									UInt16 & ioBytesLen);
	
	OSErr			RetrieveBitField(UInt16 inBitCount, UInt16 inBytesLen);
	
	OSErr			RetrieveCountValue();
	
	void			KeyValueToString(ResType inType, Str255 keyString);
	
	OSErr			FindKeyStartForValue(Str255 keyString, SInt32 * outStart);
	
	OSErr			FindMatchingKeyEnd(SInt32 * outEnd);
	
	OSErr			SkipNextKeyCases(UInt16 inPreCount);
	
	Boolean			SelectValueFromKeyCases(Str255 inLabelString);
	
};


