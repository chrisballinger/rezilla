// ===========================================================================
// CStaticTextURL.cp
// 
//                       Created: 2004-06-20 20:22:41
//             Last modification: 2004-06-21 14:05:10
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// ===========================================================================

#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CStaticTextURL.h"
#include "RezillaConstants.h"

#include <LString.h>

// Standard headers
#include <string.h>

#include <LaunchServices.h>

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
	theCurs = ::GetCursor(CURS_HandOneFinger);
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
	return outDescriptor;
}


// ---------------------------------------------------------------------------
//	¥ AdjustMouseSelf
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
	if (PtInRect(inPortPt, &frame)) {
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
	SendGurlGurlEvent();
}


// ---------------------------------------------------------------------------
//	¥  SendGurlGurlEvent
// ---------------------------------------------------------------------------

OSErr 
CStaticTextURL::SendGurlGurlEvent() 
{
	OSErr		error;
	char		urlCString[256];
	CFURLRef	theCFUrl, outLaunchedURL;
	
	CopyPascalStringToC(mUrlString, urlCString);
	
	theCFUrl = CFURLCreateWithBytes(kCFAllocatorDefault, (const UInt8 *) urlCString, strlen(urlCString),
									 CFStringGetSystemEncoding(), NULL);

	error = LSOpenCFURLRef(theCFUrl, &outLaunchedURL);

	return error;
}


PP_End_Namespace_PowerPlant
