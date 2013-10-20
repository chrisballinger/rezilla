/*
File:		CScrollWheelHandler.h
Contact:	Richard Buckle, Sailmaker Software Ltd
			<mailto:richardb@sailmaker.co.uk>
			<http://www.sailmaker.co.uk/>
Version:	1.2.3
Purpose:	Mix-in class to add Carbon scroll wheel support
Status:		Public domain
*/

/*
*********** Licensing  *************
This code is placed "as is" in the public domain in the hope that it may be useful.
You may use and modify it free of charge, however it comes with no warranty whatsoever.
It is your responsibility to determine its fitness for use and no liability, whether 
express or implied, will be accepted.

I would however appreciate being advised of any bug fixes or enhancements that 
you make.

If you found CScrollWheelHandler useful, please email me to let me know. 
I like hearing from users, and it will encourage me to keep it up to date.


*********** Requirements  *************
PowerPlant version of CW7 or later.
Version 1.2 only obeys the scroll wheel on Mac OS X 10.1 or later (but is much faster about it).


*********** Credits  *************
The core code was generously provided by Matthew Vosburgh. 
I then added LScrollerView support and wrapped it as an attachment to make version 1.0.
See also the "Change History" below.


*********** Usage *************
Suppose "CMyApp" to be your application subclass, "CMyApp.h" to be its header file 
and "CMyApp.cp" to be its implementation file.

0. 	The changes to LScroller and LScrollerView that version 1.0 required are no longer
	necessary. If you made these changes, you can keep them or undo them as you see fit.

1.	Add the following files to your project:
		CScrollWheelHandler.cp
		LEventHandler.cp (if it's not already in your project)
		
1a.	If you want support for LDataBrowser, change the #define for qSupportLDataBrowser
	in CScrollWheelHandler.cp to 1 and add the necessary access paths for wherever 
	you keep LDataBrowser.h etc.
	
2.	In "CMyApp.h", add a forward declaration:
		class	CScrollWheelHandler;
	and add a private member to the CMyApp class:
		StDeleter<CScrollWheelHandler>	mScrollWheelHandlerOwner;
		
3.	In "CMyApp.cp", add:
		#include "CScrollWheelHandler.h"
		
4.	In your the Initialize override of CMyApp, add this call:
		mScrollWheelHandlerOwner.Adopt(new CScrollWheelHandler);
	
4a.	If you are brave, have a good set of asbestos underwear,
	and want to experiment with scrolling background windows, call:
		mScrollWheelAttachmentOwner.Adopt( new CScrollWheelHandler(true) );
	instead.


Technical Note:
---------------
We could simply add a private CScrollWheelHandler member to CMyApp.
I prefer a StDeleter<CScrollWheelHandler> member for two reasons:-

(i) It minimises coupling: "CMyApp.h" file doesn't need to 
#include "CScrollWheelHandler.h". 

My experience with PowerPlant is that it is often necessary for other classes to 
#include "CMyApp.h". This way, new releases of CScrollWheelHandler 
will cause only CScrollWheelHandler.cp and "CMyApp.cp" to be recompiled: 
other classes that #include "CMyApp.h" will be unaffected.

(ii) It is easier to customise the construction of the CScrollWheelHandler instance, as in
step 4a above. If you need to subclass CScrollWheelHandler, you need only change step 4a.


*********** Remarks *************
It seems to me that there is an awful lot of common code between LScroller and LScrollerView
that could profitably be factored up into a common abstract base class.


*********** Change history  *************
1.2.3	Added optional LDataBrowser support, courtesy of James W. Walker.

1.2.2	Added forward declarations of LView and LPane, for people who don't
		use the PowerPlant precompiled headers.

1.2.1	If no kEventParamWindowRef parameter, fall back to calling FindWindow() for
		compatibility with 10.1.

1.2		Use the kEventParamWindowRef parameter rather than the slow
		FindWindow() call to find the desired window. Big win.
		
		Not an LAttachment any more. Saves space and time by staying out of
		the LAttachment lists.
		
		Renamed from CScrollWheelAttachment to CScrollWheelHandler.


1.1.1	Fixes to CScrollWheelHandler::DoScrollEvent.
		
		Pass CScrollWheelHandler::HandleScroll to
		mScrollHandler.Install() to keep CodeWarrior Pro 8 happy.
		
1.1		mScrollWheelFactor now defaults to 1, for compatibility with
		USBOverdrive etc.
		Previously, we recommended kScrollWheelFactor = 3.
		However, drivers such as USBOverdrive are now available
		for Mac OS X, so we should allow them to set the scroll
		wheel factor and leave kScrollWheelFactor at 1. 
		See also <http://www.usboverdrive.com/trouble.html#scroll>
		
		Parameterised the option to scroll background windows,
		since many people feel it is against current UI principles.
		It is now controlled by mAllowScrollBackgroundWindows,
		which defaults to false.
		Use the ctor or GetAllowScrollBackgroundWindows() and
		SetAllowScrollBackgroundWindows() to control this.
		
1.0.2	Conditionalised for correct behaviour on PowerPlant 2.2
1.0.1	No longer requires modifications to LScroller and LScrollerView.
1.0.1	Respects the magnitude of the mouse wheel delta -- it can
		exceed +/-1 if you really thrash the mouse wheel.
1.0.1	Put Carbon-specific code inside #if PP_Target_Carbon blocks.

*/

#pragma once

#if PP_Target_Carbon
	#include <TEventHandler.h>
#endif	

class LView;
class LPane;

class	CScrollWheelHandler {
public:
	// Instance methods
					CScrollWheelHandler( bool inAllowScrollBackgroundWindows = false,
											SInt32 inScrollWheelFactor = 1
											);
	virtual			~CScrollWheelHandler();
	
	// Accessors
	SInt32			GetScrollWheelFactor() const
									{return mScrollWheelFactor;}
	void			SetScrollWheelFactor(const SInt32 inVal) 
									{mScrollWheelFactor = inVal;}
	bool			GetAllowScrollBackgroundWindows() const
									{return mAllowScrollBackgroundWindows;}
	void			SetAllowScrollBackgroundWindows(const bool inVal) 
									{mAllowScrollBackgroundWindows = inVal;}

protected:
	// Implementation
#if PP_Target_Carbon
	OSStatus		HandleScroll(
									EventHandlerCallRef	inCallRef,
									EventRef			inEventRef);
	bool			DoScrollEvent(
									EventRef inEvent,
									WindowRef inWindowRef,
									Boolean isVertical, 
									SInt32 delta, 
									Point mouseLoc,
									UInt32	inModifiers);
									
	LView*			FindScrollerFromHitPane( const LPane* inPane );
#endif	

private:
	// Members
#if PP_Target_Carbon
	TEventHandler<CScrollWheelHandler>	mScrollHandler;
#endif	
	
	bool			mAllowScrollBackgroundWindows;
	SInt32			mScrollWheelFactor;
	
	// Disallowed methods
	CScrollWheelHandler( CScrollWheelHandler& );
	CScrollWheelHandler& operator= (const CScrollWheelHandler&);
};