/*******************************************************************************\
|																				|
| CURLPushButton.h	 ©1997-1998 John C. Daub.  All rights reserved				|
|																				|
| See the file "CURLPushButton README" for full details, instructions, changes, |
| licensing agreement, etc.  Due to the important information included in that	|
| file, if you did not receive a copy of it, please contact the author for		|
| a copy.																		|
|																				|
| John C. Daub <mailto:hsoi@eden.com>											|
| <http://www.eden.com/~hsoi/>  <http://www.eden.com/~hsoi/prog.html>			|
|																				|
\*******************************************************************************/

#ifndef _H_CURLPushButton
#define _H_CURLPushButton

#pragma once

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

// Having this macro true will enhance CURLPushButton by giving it drag and
// drop support. If you desire no such thing (and all the extra code it can
// bring in), #define this to be false somewhere (e.g. prefix file) and all
// the drag and drop code will be preprocessed out.

#ifndef _CURLPushButton_DO_DND_
#define _CURLPushButton_DO_DND_			1
#endif


#include <PP_Prefix.h>
#include <LControl.h>
#include <LString.h>
#include <string>

// the following struct were created for and should only be
// used for the parameterized constructor

#pragma options align=mac68k

typedef struct {
	// following 4 are input params for an LControl
	
	MessageT		valueMessage;
	SInt32			value;
	SInt32			minValue;
	SInt32			maxValue;
		
	Str255			titleText;
	ResIDT			textTraitsID;
	
	ResIDT			hiliteTextTraitsID;
	Boolean			useHiliteColor;
	RGBColor		hiliteColor;
	Str255			URL;
	
	Boolean			useInvertRect;		// no longer supported, but left in for compatability
										// (e.g. sizeof(SURLpbInfo) remains the same)
	
} SURLpbInfo, *SURLpbInfoPtr, **SURLpbInfoHandle;

#pragma options align=reset



class CURLPushButton : public LControl {

public:

		enum { class_ID = 'URpb' };

#if ( __PowerPlant__ < 0x01608000 ) // version 1.6/CW11
	static CURLPushButton*	CreateFromStream( LStream *inStream );
#endif

								CURLPushButton();
								CURLPushButton(const CURLPushButton &inOriginal );
								CURLPushButton(const SPaneInfo		&inPaneInfo,
												const SURLpbInfo	&inParamInfo,
												const ResIDT		inCursorID = 0 );
								CURLPushButton( LStream *inStream );
		virtual					~CURLPushButton();
		
				CURLPushButton&	operator=( const CURLPushButton &inOriginal );

		virtual	void			SetValue( SInt32 inValue );
		
		virtual	std::string		GetURL();
		virtual	StringPtr		GetURL( Str255 outURL ) const;
		virtual	void			SetURL( ConstStringPtr inURL );
		virtual void			SetURL( const char * inURL );

		virtual StringPtr		GetDescriptor();
		virtual	StringPtr		GetDescriptor( Str255 outDescriptor ) const;
		virtual	void			SetDescriptor( ConstStringPtr inDescriptor );

		virtual	ResIDT			GetTextTraitsID() const;
		virtual	void			SetTextTraitsID( const ResIDT inResID );

		virtual	ResIDT			GetHiliteTextTraitsID() const;
		virtual	void			SetHiliteTextTraitsID( const ResIDT inResID );

		virtual bool			GetUseHiliteColor() const;
		virtual void			SetUseHiliteColor( bool inUseHiliteColor );

		virtual	void			GetHiliteColor( RGBColor &outColor ) const;
		virtual	void			SetHiliteColor( const RGBColor &inHiliteColor );
		virtual	void			SetHiliteColor( const UInt8 inRed, 
												const UInt8 inGreen, const UInt8 inBlue );

#if _CURLPushButton_DO_DND_
		virtual	bool			GetDoDragAndDrop() const;
		virtual	void			SetDoDragAndDrop( const bool inDoDragAndDrop );
#endif

		virtual	ResIDT			GetCursorID() const;
		virtual	void			SetCursorID( const ResIDT inResID );

		virtual Boolean			IsHitBy(
										SInt32	inHorizPort,
										SInt32	inVertPort);
		
		virtual void			MoveBy(
										SInt32	inHorizDelta,
										SInt32	inVertDelta,
										Boolean	inRefresh);
		
protected:

#if _CURLPushButton_DO_DND_
		virtual	void			ClickSelf(const SMouseDownEvent &inMouseDown );
		virtual	void			CreateDragEvent( const SMouseDownEvent &inMouseDown );
#endif
		virtual void			FinishCreateSelf();
		virtual	void			DrawSelf();

		virtual	void			ActivateSelf();
		virtual	void			DeactivateSelf();

#if __PowerPlant__ < 0x02118000
		virtual	void			AdjustCursorSelf( 
										Point inPortPt, 
										const EventRecord &inMacEvent );
#else
		virtual	void			AdjustMouseSelf( 
										Point inPortPt, 
										const EventRecord &inMacEvent,
										RgnHandle ioMouseRgn );
#endif

		virtual	void			HotSpotResult( SInt16 inHotSpot );
		virtual	void			HotSpotAction(
										SInt16	inHotSpot,
										Boolean	inCurrInside,
										Boolean	inPrevInside);

				void			UpdateCachedFrame();

private:
		
				LStr255			mTitleText;
				ResIDT			mTextTraitsID;
				LStr255			mURL;
				ResIDT			mHiliteTextTraitsID;
				Boolean			mUseHiliteColor;
				RGBColor		mHiliteColor;
				Boolean			mUseInvertRect;		// no longer used, but left in for
													// compatability.
				ResIDT			mCursorID;
				Rect			mTextFrame;

#if _CURLPushButton_DO_DND_				
				bool			mDoDragAndDrop;
#endif

};


//========================================================================
//	¥¥¥ Inlines
//========================================================================


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetTextTraitsID							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Return the Txtr ResIDT

inline
ResIDT
CURLPushButton::GetTextTraitsID() const
{
	return mTextTraitsID;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetTextTraitsID							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set the text traits to the given ResIDT

inline
void
CURLPushButton::SetTextTraitsID(
	const ResIDT inResIDT )
{
	mTextTraitsID = inResIDT;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetHiliteTextTraitsID						[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Return the Txtr ResIDT

inline
ResIDT
CURLPushButton::GetHiliteTextTraitsID() const
{
	return mHiliteTextTraitsID;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetHiliteTextTraitsID						[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set the hilite text traits to the given ResIDT

inline
void
CURLPushButton::SetHiliteTextTraitsID(
	const ResIDT inResIDT )
{
	mHiliteTextTraitsID = inResIDT;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetUseHiliteColor							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Return true if using hilite color or false if not

inline
bool
CURLPushButton::GetUseHiliteColor() const
{
	return mUseHiliteColor;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetUseHiliteColor							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Used to set if we should use the hilite color or not

inline
void
CURLPushButton::SetUseHiliteColor(
	const bool inUseHiliteColor )
{
	mUseHiliteColor = inUseHiliteColor;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetHiliteColor							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Return the hilite color

inline
void
CURLPushButton::GetHiliteColor( RGBColor &outColor ) const
{
	outColor.red = mHiliteColor.red;
	outColor.green = mHiliteColor.green;
	outColor.blue = mHiliteColor.blue;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetHiliteColor							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set the hilite color to the given RGBColor

inline
void
CURLPushButton::SetHiliteColor(
	const RGBColor &inHiliteColor )
{
	mHiliteColor.red = inHiliteColor.red;
	mHiliteColor.green = inHiliteColor.green;
	mHiliteColor.blue = inHiliteColor.blue;
}

// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetHiliteColor							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set the hilite color to the given red, green, and blue values

inline
void
CURLPushButton::SetHiliteColor(
	const UInt8	inRed,
	const UInt8 inGreen,
	const UInt8 inBlue )
{
	mHiliteColor.red = inRed;
	mHiliteColor.green = inGreen;
	mHiliteColor.blue = inBlue;
}


// these functions are only used if we are supporting drag and drop

#if _CURLPushButton_DO_DND_

// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetDoDragAndDrop							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Return true if this object does drag and drop support

inline
bool
CURLPushButton::GetDoDragAndDrop() const
{
	return mDoDragAndDrop;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetDoDragAndDrop							[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set if this object will support drag and drop or not

inline
void
CURLPushButton::SetDoDragAndDrop(
	const bool inDoDragAndDrop )
{
	mDoDragAndDrop = inDoDragAndDrop;
}


#endif // _CURLPushButton_DO_DND_


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ GetCursorID								[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Returns the ResIDT of the 'CURS'

inline
ResIDT
CURLPushButton::GetCursorID() const
{
	return mCursorID;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ SetCursorID								[public, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Set the 'CURS' to the given ID

inline
void
CURLPushButton::SetCursorID(
	const ResIDT inResID )
{
	mCursorID = inResID;
}


// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	¥ FinishCreateSelf							[protected, virtual]
// ÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑÑ
//	Update the cached text frame (in case text was pre-loaded into the object)

inline
void
CURLPushButton::FinishCreateSelf()
{
	UpdateCachedFrame();
}


#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif

#endif /* _H_CURLPushButton */
