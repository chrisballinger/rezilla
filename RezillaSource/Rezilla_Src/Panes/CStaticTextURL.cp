// ===========================================================================
// CStaticTextURL.cp
// 
//                       Created: 2004-06-20 20:22:41
//             Last modification: 2004-06-21 14:05:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CStaticTextURL.h"
#include "RezillaConstants.h"

// #include <UDesktop.h>
#include <LString.h>

#include <AEHelpers.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CStaticTextURL							Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CStaticTextURL::CStaticTextURL(
	LStream*	inStream,
	ClassIDT	inImpID)

	: LStaticText(inStream, inImpID)
{
	InitUrlPane();
}


// ---------------------------------------------------------------------------
//	¥ CStaticTextURL							Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CStaticTextURL::CStaticTextURL(
	const SPaneInfo&	inPaneInfo,
	ConstStringPtr		inTitle,
	ResIDT				inTextTraitsID,
	ClassIDT			inImpID)

	: LStaticText(inPaneInfo, inTitle, inTextTraitsID, inImpID)
{
	InitUrlPane();
}


// ---------------------------------------------------------------------------
//	¥ ~CStaticTextURL							Destructor				  [public]
// ---------------------------------------------------------------------------

CStaticTextURL::~CStaticTextURL()
{
}


// ---------------------------------------------------------------------------
//	¥ InitUrlPane
// ---------------------------------------------------------------------------

void 
CStaticTextURL::InitUrlPane()
{
	CursHandle	theCurs;
	theCurs = ::GetCursor(CURS_HandCursor);
	mHandCursor = **theCurs;
}



#pragma mark -

// ---------------------------------------------------------------------------
//	¥ SetUrlString													  [public]
// ---------------------------------------------------------------------------

void
CStaticTextURL::SetUrlString(
	ConstStringPtr	inDescriptor)
{
	LString::CopyPStr(inDescriptor, mUrlString);
}


// ---------------------------------------------------------------------------
//   ¥ GetUrlString                                                   [public]
// ---------------------------------------------------------------------------

StringPtr
CStaticTextURL::GetUrlString(
 Str255  outDescriptor) const
{
	LString::CopyPStr(mUrlString, outDescriptor);
	Size	strLen;
	GetText((Ptr) outDescriptor + 1, 255, &strLen);
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ AdjustCursorSelf
// ---------------------------------------------------------------------------

void
CStaticTextURL::AdjustMouseSelf(
	Point				inPortPt,
	const EventRecord&	/* inMacEvent */,
	RgnHandle			/* ioMouseRgn */)
{
	Rect	frame;
	CalcLocalFrameRect(frame);
	PortToLocalPoint(inPortPt);
	if (PtInRect(inPortPt, &frame))
	{
		::SetCursor(&mHandCursor);
	}
}


// ---------------------------------------------------------------------------
//	¥  ClickSelf
// ---------------------------------------------------------------------------

void 
CStaticTextURL::ClickSelf(
	const SMouseDownEvent &inMouseDown)
{
#pragma unused(inMouseDown)
	
// 	UDesktop::FetchTopRegular()->Hide();		
	SendGurlGurlEvent();
}


// ---------------------------------------------------------------------------
//	¥  SendGurlGurlEvent
// ---------------------------------------------------------------------------

OSErr 
CStaticTextURL::SendGurlGurlEvent() 
{
	OSErr		error;
	OSType		theSignature = kSystemEventsSig;
	char		urlCString[256];
	AppleEvent	theEvent = {typeNull, nil};
	AppleEvent	theReply = {typeNull, nil};

	CopyPascalStringToC(mUrlString, urlCString);
	
	error = AEBuildAppleEvent(
				'GURL', 'GURL',
				typeApplSignature, &theSignature, sizeof(OSType),
				kAutoGenerateReturnID, kAnyTransactionID,
				&theEvent,
				NULL,
				"'----':'TEXT'(@)", urlCString);

	if (error == noErr) {
		error = AESend( &theEvent, &theReply, kAENoReply, kAENormalPriority, kNoTimeOut, nil, nil );			
	} 	

	(void) AEDisposeDesc(&theEvent);
	(void) AEDisposeDesc(&theReply);
	return error;
}


PP_End_Namespace_PowerPlant
