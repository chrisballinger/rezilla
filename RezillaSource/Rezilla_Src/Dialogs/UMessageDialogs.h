// ===========================================================================
// UMessageDialogs.h					
// 
//                       Created: 2002-05-31 19:50:34
//             Last modification: 2005-09-25 08:27:50
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// ===========================================================================


#ifndef _H_UMessageDialogs
#define _H_UMessageDialogs
#pragma once

#include <LPeriodical.h>

// 'answer_Cancel' already defined in "PP_Resources.h" ( = 2)
// 'answer_Do' is the same as 'answer_Save' ( = 1)
const SInt16	answer_Do		= answer_Save;
const SInt16	answer_Dont		= 3;

// AskYesNo alert box
const MessageT	 msg_Dont		= 9502 ;

// Messaging windows: the text caption
const PaneIDT   item_MessageField		= FOUR_CHAR_CODE('MESG') ;
const PaneIDT   item_ExplainField		= FOUR_CHAR_CODE('EXPL') ;

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

namespace UMessageDialogs {

	void		SimpleMessage(LStr255 inString, 
								ResIDT inPpobID);
	
	SInt16		AskIfMessage(LStr255 inString, 
								ResIDT inPpobID);
	
	SInt16		AskYesNoMessage(LStr255 inString, 
								ResIDT inPpobID);

	void		SimpleMessageFromRes(ResIDT inStringResID, 
								SInt32 inIndex, 
								ResIDT inPpobID);
	
	SInt16		AskIfFromRes(ResIDT inStringResID, 
								SInt32 inIndex, 
								ResIDT inPpobID);
	
	SInt16		AskYesNoFromRes(ResIDT inStringResID, 
								SInt32 inIndex, 
								ResIDT inPpobID);
	
	void		SimpleMessageFromLocalizable(
								 CFStringRef inCFStringRef, 
								 ResIDT inPpobID);
	
	void		SimpleMessageFromCFString(
								 CFStringRef inCFStringRef, 
								 ResIDT inPpobID);
	
	void		RunSimpleMessage(Str255 inString, ResIDT inPpobID);
	
	SInt16		AskIfFromLocalizable(
								 CFStringRef inCFStringRef, 
								 ResIDT inPpobID);
	
	SInt16		AskYesNoFromLocalizable(
								 CFStringRef inCFStringRef, 
								 ResIDT inPpobID);
	
	void		ErrorMessage(LStr255 inString, 
								OSErr inError,
								ResIDT inPpobID);
	
	void		ErrorMessageFromRes(ResIDT inStringResID, 
								SInt32 inIndex, 
								OSErr inError,
								ResIDT inPpobID);
	
	void		ErrorMessageFromLocalizable(
								CFStringRef inCFStringRef, 
								OSErr inError,
								ResIDT inPpobID);
	
	SInt16		AskSolveUidConflicts(ResType inType, 
									 short inID, 
									 Boolean& ioApplyToOthers,
									 Boolean askSimilar = true);
	
	Boolean		GetOneValue(
							 LCommander*	inSuper,
							 CFStringRef	inCFStringRef, 
							 ResIDT			inDialogID,
							 PaneIDT		inStaticFieldID,
							 PaneIDT		inEditFieldID,
							 SInt32&		ioValue);
	
	void		AlertWithValue(CFStringRef inCFStringRef, SInt32 inValue);
	
	void		AlertWithType(CFStringRef inCFStringRef, ResType inType);
	
	void		AlertWithString(CFStringRef inCFStringRef, Str255 inString);

	SInt16		AskIfWithString(CFStringRef inCFStringRef, Str255 inString);
	
	void		DescribeError(CFStringRef inCFStringRef, SInt32 inError);
	
	void		DisplayPostponedError(CFStringRef inCFStringRef, SInt32 inError);
	
}



// ============================================================
// 	Class CPostponedError
// ============================================================
// 	Used internally to display errors at "bad" times (during Drag&Drop, etc).

class CPostponedError : public LPeriodical {
	public:
						CPostponedError(CFStringRef inCFStringRef, SInt32 inError);
		virtual void	SpendTime( const EventRecord & );
		
	protected:
		SInt32			mErrorNum;
		CFStringRef		mErrorString;
};




PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
