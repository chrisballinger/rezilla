// ===========================================================================
// CTmplEditorWindow.h
// 
//                       Created: 2004-06-12 15:08:01
//             Last modification: 2006-09-18 18:53:00
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "RezillaConstants.h"
#include "UResources.h"

#include <LPane.h>
#include <LView.h>
/* #include <LActiveScroller.h> */

class CTmplEditorDoc;
class CTmplListButton;
class CRezObj;
class LEditText;
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
	enum { class_ID = FOUR_CHAR_CODE('TmpW') };

							CTmplEditorWindow();
							CTmplEditorWindow( const SWindowInfo &inWindowInfo );
							CTmplEditorWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CTmplEditorWindow( LStream *inStream );
							~CTmplEditorWindow();

	virtual void	Draw( RgnHandle inSuperDrawRgnH );
							
	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual void	RevertContents();

	virtual Boolean	HandleKeyPress( const EventRecord& inKeyEvent );

	OSErr			ParseDataWithTemplate(Handle inHandle);
	
	OSErr			RetrieveDataWithTemplate();
	
	OSErr			RevertWithTemplate();
	
	void			AdjustCounterField(PaneIDT inPaneID, SInt32 inDelta);
	
	static void			InitPaneInfos();
	
	static UInt32		CountAllSubPanes(LView * inView);
	
	LHandleStream*		GetOutStream() { return mOutStream;}
						
	LView*				GetContentsView() const { return mContentsView;}
	
	CTmplListItemView*	GetSelectedListItem() { return mSelectedListItem;}
	void				SetSelectedListItem(CTmplListItemView* inSelectedListItem) {mSelectedListItem = inSelectedListItem;}
	
	bool 			IsFlipped () const	{ return mFlipped; }
	void			SetFlipped ( bool isFlipped ) { mFlipped = isFlipped; }
	

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
						sColorPaneInfo,
						sPopupPaneInfo;
	
protected:
	LView *				mContentsView;
	LScrollerView *		mContentsScroller;
	CTmplListItemView *	mSelectedListItem;
	SInt32				mYCoord;
	PaneIDT				mCurrentID;
	PaneIDT				mPaneIndex;
	PaneIDT				mLastID;
	SInt32				mIndent;
	SInt32				mSkipOffset;
	SInt32				mListCountMark;
	ResType				mCountType;
	short				mListCount;
	Boolean				mFixedCount;
	SInt32				mRectFormat;
	LHandleStream *		mTemplateStream;
	LHandleStream *		mRezStream;
	LHandleStream *		mOutStream;
	TArray<PaneIDT>		mPaneIDs;
	TArray<ResType>		mOffsetTypes;
	TArray<SInt32>		mOffsetMarks;
	TArray<SInt32>		mKeyValues;
	TArray<SInt32>		mKeyMarks;
	TArray<PaneIDT>		mKeyIDs;
	Boolean				mBitSeqInProgress;
	UInt32				mBitSeqValue;
	UInt8				mBitSeqBytesLen;
	SInt8				mBitSeqIndex;
	LEditText*			mPrevTnam;		// ZP feature #9
	bool 				mFlipped;		// Resource is flipped by system

	virtual void	FinishCreateSelf();

	OSErr			CreateTemplateStream();
		
private:
	OSErr			ParseDataForType(ResType inType, Str255 inLabelString, LView * inContainer);
	OSErr			RetrieveDataForType(ResType inType);
	
	OSErr			ParseList(SInt32 inStartMark, 
							  ResType inType, 
							  SInt32 inCount, 
							  LView * inContainer, 
							  PaneIDT inCountPaneID);

	OSErr			RetrieveList(SInt32 inStartMark, 
								 ResType inType, 
								 SInt32 inCount);

	OSErr			ParseKeyedSection(ResType inType, 
								   Str255 inLabelString, 
								   LView * inContainer);

	OSErr			RetrieveKeyedSection(ResType inType, PaneIDT inPaneID);

	Boolean			EndOfList(ResType inType, OSErr * outError);
	
	void			AddStaticField(OSType inType, 
								   Str255 inLabel, 
								   LView * inContainer,
								   ResIDT inTextTraitsID = Txtr_GenevaTenBoldRight, 
								   SInt32 inReqLength = 0,
								   Boolean fullWidth = false);
	
	void			AddEditField(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
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
								  LView * inContainer, 
								  SInt32 inReqLength = 0);
	
	void			AddHexDumpField(OSType inType, 
									LView * inContainer, 
									SInt32 inReqLength = 0);
	
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
	
	CTmplListItemView *	AddListItemView(CTmplListItemView * inPrevListItemView, 
										CTmplListItemView * inNextListItemView, 
										CTmplListButton * inMinusButton,
										LView * inContainer);
	
	void			AddSeparatorLine(LView * inContainer);
	
	void			AddEditPopup(Str255 inValue, 
								OSType inType,
								SInt16 inMaxChars, 
								SInt16 inWidth,
								UInt8 inAttributes,
								TEKeyFilterFunc inKeyFilter, 
								ResIDT inResourceID,
								LView * inContainer);
	
	OSErr			AddFlagPopup(ResType inType, 
								 Str255 inLabel, 
								 UInt32 inValue, 
								 LView * inContainer);

	void			AddColorPane(LView * inContainer, 
								RGBColor * inRGB);
	
	void			AddRSIDField(Str255 inValue,
								OSType inType,
								Str255 inLabelString,
								SInt16 inMaxChars,
								SInt16 inWidth,
								TEKeyFilterFunc inKeyFilter,
								LView * inContainer);
	
	ExceptionCode	AlignBytesRead(UInt8 inStep);
	
	ExceptionCode	AlignBytesWrite(UInt8 inStep);
	
	void			BuildFormatString(char * ioString, UInt8 inLength);

	OSErr			BuildScanString(char * inString, char * ioFormat, UInt8 inLength);
	
	OSErr			DoParseWithTemplate(SInt32 inRecursionMark, 
										Boolean inDrawControls, 
										LView * inContainer);

	OSErr			DoRetrieveWithTemplate(SInt32 inRecursionMark, 
										   Boolean inReadControls);
	
	void			IncrementIfCases(LEditText * inEditText);
	
	void			AdjustListOfPaneIDs(CTmplListItemView * inView,
									PaneIDT inStartID, 
									PaneIDT inPrevCurrID,
									Boolean adding);
	
	void			RecalcPositions(LView * inView, 
									SInt32 inVertPos, 
									SInt32 inPosDelta);

	Boolean			RecalcTextBoxHeight(SInt32 inTextSize, 
										CWasteEditView * inWEView,
										Boolean isFixed, 
										SInt32 inReqSize,
										SInt16 & delta);

	Boolean			CalcTextPositions(OSType inType, 
									  SInt32 & oldPos, 
									  SInt32 & newPos, 
									  SInt32 & nextPos,
									  SInt32 & reqLength, 
									  Boolean & isFixed);

	Boolean			IsValidBitField(OSType inType, 
									Str255 ioString, 
									UInt16 & ioBitsCount, 
									UInt16 & ioBytesLen);
	
	Boolean			NextIsCase();
	
	OSErr			RetrieveBitField(UInt16 inBitCount, UInt16 inBytesLen);
	
	OSErr			RetrieveCountValue();
	
	void			KeyValueToString(ResType inType, Str255 keyString);
	
	OSErr			KeyStringToValue(ResType inType, Str255 keyString);
	
	OSErr			FindKeyStartForValue(ResType inType, 
										 Str255 keyString, 
										 SInt32 * outStart);
	
	OSErr			FindMatchingKeyEnd(SInt32 * outEnd);
	
	OSErr			SkipNextKeyCases(UInt16 inPreCount);
	
	OSErr			WriteOutKeyValue(ResType inType, 
									 PaneIDT inPaneID, 
									 ArrayIndexT * outIndex);
	
	OSErr			SelectKeyValueFromKeyCases(Str255 inLabelString,
										   Str255 outKeyString);
	
	// ZP feature #11, part 2: declare the LTabGroup-like rotating
	// function. Implemented in CTmplWindowUtils.cp.
	void			RotateTarget( Boolean inBackward );	

};


