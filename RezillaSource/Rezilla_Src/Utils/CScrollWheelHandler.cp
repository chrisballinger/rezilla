/*
File:		CScrollWheelHandler.cp
Contact:	Richard Buckle, Sailmaker Software Ltd
			<mailto:richardb@sailmaker.co.uk>
			<http://www.sailmaker.co.uk/>
Version:	1.2.3
Purpose:	Mix-in class to add Carbon scroll wheel support
Status:		Public domain
*/

// IMPORTANT: see CScrollWheelHandler.h for usage notes and lack of warranty

#include "CScrollWheelHandler.h"
#include <LScrollerView.h>
#include <LScroller.h>
#include <UDesktop.h>
#include <UEnvironment.h>

#ifndef qSupportLDataBrowser
	#define qSupportLDataBrowser 0 // set this to 1 if you want LDataBrowser support
#endif

#if qSupportLDataBrowser
	#include "LDataBrowser.h"
#endif

#if PP_Target_Carbon && (__PowerPlant__	< 0x02208000)
	EventHandlerUPP	TEventHandler<CScrollWheelHandler>::sHandlerUPP = 0;
#endif

//
CScrollWheelHandler::CScrollWheelHandler(	bool inAllowScrollBackgroundWindows,
											SInt32 inScrollWheelFactor
											)
	:
	mScrollWheelFactor(inScrollWheelFactor),
	mAllowScrollBackgroundWindows(inAllowScrollBackgroundWindows)
{
#if PP_Target_Carbon
	mScrollHandler.Install( ::GetApplicationEventTarget(), 
								kEventClassMouse, 
								kEventMouseWheelMoved, this, 
								&CScrollWheelHandler::HandleScroll );
#endif	
}
	
//
CScrollWheelHandler::~CScrollWheelHandler()
{}


#if PP_Target_Carbon
//
OSStatus
CScrollWheelHandler::HandleScroll(
								EventHandlerCallRef	/*inCallRef*/,
								EventRef			inEvent)
{
	OSStatus result = eventNotHandledErr;
	bool handledEvent = false;

	EventMouseWheelAxis axis;
	::GetEventParameter(inEvent, kEventParamMouseWheelAxis, typeMouseWheelAxis,
							0, sizeof(axis), 0, &axis);
	
	SInt32 delta;
	::GetEventParameter(inEvent, kEventParamMouseWheelDelta, typeLongInteger,
							0, sizeof(delta), 0, &delta);

	Point mouseLoc;
	::GetEventParameter(inEvent, kEventParamMouseLocation, typeQDPoint,
							0, sizeof(mouseLoc), 0, &mouseLoc);

	UInt32 modifiers = 0;
	::GetEventParameter(inEvent, kEventParamKeyModifiers, typeUInt32,
							0, sizeof(modifiers), 0, &modifiers);
	
	// the kEventParamWindowRef parameter is only supplied with 10.2 and later
	WindowRef window = 0;
	::GetEventParameter(inEvent, kEventParamWindowRef, typeWindowRef,
							0, sizeof(window), 0, &window);
	
	if( !window )
	{
		short hitPart = ::FindWindow(mouseLoc, &window);
	}
	
	if( window )
	{
		handledEvent = DoScrollEvent( inEvent, window, (axis == kEventMouseWheelAxisY), delta,
									mouseLoc, modifiers );
	}
	
	if (handledEvent) result = noErr;
	
	return result;
}

// We can allow the scroll wheel to scroll background windows of our app.
// This is controlled by mAllowScrollBackgroundWindows.
// It is somewhat questionable UI, as it breaks the fundamental principle of
// consistency. "My Mom" might become rather confused by some background windows
// scrolling and others not.
// However, scrolling is such an innocuous, non-destructive process that I've
// decided to go with it.
// Maybe some day both Carbon and Cocoa apps will all support scrolling of 
// background windows.
bool
CScrollWheelHandler::DoScrollEvent(
	EventRef inEvent,
	WindowRef inWindowRef,
	Boolean	inIsVertical, 
	SInt32	inDelta, 
	Point	inMouseLoc,
	UInt32	/*inModifiers*/)
{

	LWindow* 		hitWindow = 0;
	bool			handledEvent = false;
	LView*			viewToScroll = 0;
#if qSupportLDataBrowser
	LDataBrowser*	hitBrowser = 0;
#endif
	
	(void)&inEvent; // unused if qSupportLDataBrowser is 0
	
	SignalIf_(!inWindowRef);
	hitWindow = LWindow::FetchWindowObject(inWindowRef);
	
	if (	hitWindow 
			&& (
				GetAllowScrollBackgroundWindows() 
				|| UDesktop::WindowIsSelected(hitWindow)
				)
			)
	{
		hitWindow->GlobalToPortPoint(inMouseLoc);
		
		LPane*	hitPane = hitWindow->FindDeepSubPaneContaining(inMouseLoc.h, inMouseLoc.v);
#if qSupportLDataBrowser
		hitBrowser = dynamic_cast<LDataBrowser*>(hitPane);
#endif
		viewToScroll = FindScrollerFromHitPane(hitPane);
	}
	
#if qSupportLDataBrowser
	if ( hitBrowser && (UEnvironment::GetOSVersion() >= 0x1020) )
	{
		SendEventToControl( inEvent, hitBrowser->GetMacControl() );
		handledEvent = true;
	}
#endif
	
	if( !handledEvent && viewToScroll )
	{
		SPoint32 scrollUnit;
		viewToScroll->GetScrollUnit(scrollUnit);
		if (inIsVertical)
		{
			scrollUnit.h = 0;
			scrollUnit.v *= -inDelta * GetScrollWheelFactor();
		}
		else
		{
			scrollUnit.h *= -inDelta * GetScrollWheelFactor();
			scrollUnit.v = 0;
		}
		viewToScroll->ScrollPinnedImageBy(scrollUnit.h, scrollUnit.v, Refresh_Yes);
		handledEvent = true;
	}
	
	return handledEvent;
}


// starting with inPane and walking up the containment hierarchy, look for a scrollable view.
// If none found, return 0.
// If inPane is nil, return 0.
LView*			
CScrollWheelHandler::FindScrollerFromHitPane( const LPane* inPane )
{
	LView* 					result = 0;
	const LPane* 			theTargetPane = inPane;
	
	while(theTargetPane && !result)
	{
		const LScroller* scroller = dynamic_cast<const LScroller*>(theTargetPane);
		if (scroller)
		{
			result = scroller->GetScrollingView();
		}
		else
		{
			const LScrollerView* scrollerView = dynamic_cast<const LScrollerView*>(theTargetPane);
			if (scrollerView)
			{
				result = scrollerView->GetScrollingView();
			}
		}
		
		theTargetPane = theTargetPane->GetSuperView();
	}	
	
	return result;
}
	
#endif // PP_Target_Carbon
