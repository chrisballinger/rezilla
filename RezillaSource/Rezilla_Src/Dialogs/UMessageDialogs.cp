// ===========================================================================
// UMessageDialogs.h					
// 
//                       Created: 2002-05-31 19:50:34
//             Last modification: 2005-09-25 22:03:11
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// ===========================================================================

#include "UMessageDialogs.h"
#include "UMiscUtils.h"
#include "UDialogBoxHandler.h"
#include "CRezillaApp.h"
#include "RezillaConstants.h"
#include "CThreeButtonsBox.h"

#include <CFString.h>
#include <LThemeTextBox.h>
#include <LCheckBox.h>
#include <LStaticText.h>


// ---------------------------------------------------------------------------
//  ¥ SimpleMessage											
// ---------------------------------------------------------------------------

void
UMessageDialogs::SimpleMessage(LStr255 inString, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(inString);
		
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ AskIfMessage											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskIfMessage(LStr255 inString, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(inString);
		
	SInt16		theAnswer = answer_Cancel;
	
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			theAnswer = answer_Do;
			break;
		} else if (hitMessage == msg_Cancel) {
			break;
		}
	}
	return theAnswer;
}

	
// ---------------------------------------------------------------------------
//  ¥ AskYesNoMessage											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskYesNoMessage(LStr255 inString, ResIDT inPpobID)
{

	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(inString);
		
	SInt16		theAnswer = answer_Dont;
	
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			theAnswer = answer_Do;
			break;
		} else if (hitMessage == msg_Cancel) {
			theAnswer = answer_Cancel;
			break;
		} else if (hitMessage == msg_Dont)  {
			break;
		}
	}
	return theAnswer;
}


// ---------------------------------------------------------------------------
//  ¥ SimpleMessageFromRes											
// ---------------------------------------------------------------------------

void
UMessageDialogs::SimpleMessageFromRes(ResIDT inSTRxResID, SInt32 inIndex, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	Str255	theTxt;
	::GetIndString(theTxt, inSTRxResID, inIndex);
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(theTxt);
		
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ AskIfFromRes											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskIfFromRes(ResIDT inSTRxResID, SInt32 inIndex, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	Str255	theTxt;
	::GetIndString(theTxt, inSTRxResID, inIndex);
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(theTxt);
		
	SInt16		theAnswer = answer_Cancel;
	
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			theAnswer = answer_Do;
			break;
		} else if (hitMessage == msg_Cancel) {
			break;
		}
	}
	return theAnswer;
}


// ---------------------------------------------------------------------------
//  ¥ AskYesNoFromRes											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskYesNoFromRes(ResIDT inSTRxResID, SInt32 inIndex, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	Str255	theTxt;
	::GetIndString(theTxt, inSTRxResID, inIndex);
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(theTxt);
		
	SInt16		theAnswer = answer_Dont;
	
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			theAnswer = answer_Do;
			break;
		} else if (hitMessage == msg_Cancel) {
			theAnswer = answer_Cancel;
			break;
		} else if (hitMessage == msg_Dont) {
			break;
		}
	}
	return theAnswer;
}


// ---------------------------------------------------------------------------
//  ¥ SimpleMessageFromLocalizable											
// ---------------------------------------------------------------------------

void
UMessageDialogs::SimpleMessageFromLocalizable(CFStringRef inCFStringRef, ResIDT inPpobID)
{
	CFStringRef ourCFString = NULL;

	ourCFString = ::CFCopyLocalizedString(inCFStringRef, NULL);
	if (ourCFString != NULL) {
		SimpleMessageFromCFString(ourCFString, inPpobID);
		::CFRelease(ourCFString);                             
	}
}


// ---------------------------------------------------------------------------
//  ¥ SimpleMessageFromCFString											
// ---------------------------------------------------------------------------

void
UMessageDialogs::SimpleMessageFromCFString(CFStringRef inCFStringRef, ResIDT inPpobID)
{
	Str255      stringBuf;

	if (inCFStringRef != NULL)
	{
		if (::CFStringGetPascalString(inCFStringRef, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding()))
		{
			if (CRezillaApp::sCalledFromAE) {
				OSErr error = err_RezillaErrorStart;
				::AEPutParamPtr( LModelDirector::GetCurrentAEReply(), keyErrorString, typeChar, stringBuf+1, stringBuf[0]);
				::AEPutParamPtr( LModelDirector::GetCurrentAEReply(), keyErrorNumber, typeSInt16, &error, sizeof(OSErr));
			} else {
				UMessageDialogs::RunSimpleMessage(stringBuf, inPpobID);
			}
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ RunSimpleMessage											
// ---------------------------------------------------------------------------

void
UMessageDialogs::RunSimpleMessage(Str255 inString, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);

	LThemeTextBox * theCaption = (LThemeTextBox *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(inString);
	theCaption->Draw(nil);
	
	MessageT 	hitMessage;
	while (true) {
		hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ AskIfFromLocalizable											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskIfFromLocalizable(CFStringRef inCFStringRef, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	CFStringRef ourCFString = NULL;
	Str255      stringBuf;
	MessageT 	hitMessage;
	SInt16		theAnswer = answer_Cancel;
	
	ourCFString =  ::CFCopyLocalizedString(inCFStringRef, NULL);
	if (ourCFString != NULL)
	{
		if (::CFStringGetPascalString(ourCFString, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding()))
		{
			LThemeTextBox * theCaption = (LThemeTextBox *)theDialog->FindPaneByID( item_MessageField );
			theCaption->SetDescriptor(stringBuf);
			theCaption->Draw(nil);
			
			while (true) {
				hitMessage = dialog.DoDialog();
				if (hitMessage == msg_OK) {
					theAnswer = answer_Do;
					break;
				} else if (hitMessage == msg_Cancel) {
					break;
				}
			}
		}
		::CFRelease(ourCFString);                             
	}
	return theAnswer;
}
	

// ---------------------------------------------------------------------------
//  ¥ AskYesNoFromLocalizable											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskYesNoFromLocalizable(CFStringRef inCFStringRef, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	CFStringRef ourCFString = NULL;
	Str255      stringBuf;
	MessageT 	hitMessage;
	SInt16		theAnswer = answer_Dont;
	
	ourCFString =  ::CFCopyLocalizedString(inCFStringRef, NULL);
	if (ourCFString != NULL)
	{
		if (::CFStringGetPascalString(ourCFString, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding()))
		{
			LThemeTextBox * theCaption = (LThemeTextBox *)theDialog->FindPaneByID( item_MessageField );
			theCaption->SetDescriptor(stringBuf);
			theCaption->Draw(nil);
			
			while (true) {
				hitMessage = dialog.DoDialog();
				if (hitMessage == msg_OK) {
					theAnswer = answer_Do;
					break;
				} else if (hitMessage == msg_Cancel) {
					theAnswer = answer_Cancel;
					break;
				} else if (hitMessage == msg_Dont) {
					break;
				}
			}
		}
		::CFRelease(ourCFString);                             
	}
	return theAnswer;
	
}


// ---------------------------------------------------------------------------
//  ¥ ErrorMessage											
// ---------------------------------------------------------------------------

void
UMessageDialogs::ErrorMessage(LStr255 inString, OSErr inError, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	inString += "\p (err ";
	inString += (LStr255) inError;
	inString += "\p)";
	
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(inString);
		
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ ErrorMessageFromRes											
// ---------------------------------------------------------------------------

void
UMessageDialogs::ErrorMessageFromRes(ResIDT inSTRxResID, SInt32 inIndex, OSErr inError, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	Str255	theTxt;
	::GetIndString(theTxt, inSTRxResID, inIndex);
	LStr255	theLine(theTxt);
	theLine += "\p (err ";
	theLine += (LStr255) inError;
	theLine += "\p)";
	
	LCaption * theCaption = (LCaption *)theDialog->FindPaneByID( item_MessageField );
	theCaption->SetDescriptor(theLine);
		
	while (true) {
		MessageT hitMessage = dialog.DoDialog();
		if (hitMessage == msg_OK) {
			break;
		}
	}
}


// ---------------------------------------------------------------------------
//  ¥ ErrorMessageFromLocalizable											
// ---------------------------------------------------------------------------

void
UMessageDialogs::ErrorMessageFromLocalizable(CFStringRef inCFStringRef, OSErr inError, ResIDT inPpobID)
{
	StDialogBoxHandler dialog(inPpobID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	CFStringRef ourCFString = NULL;
	Str255      stringBuf;
	MessageT 	hitMessage;
	ourCFString =  ::CFCopyLocalizedString(inCFStringRef, NULL);
	if (ourCFString != NULL)
	{
		if (::CFStringGetPascalString(ourCFString, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding()))
		{
			LStr255	theLine(stringBuf);
			theLine += "\p (err ";
			theLine += (LStr255) inError;
			theLine += "\p)";
									
			LThemeTextBox * theCaption = (LThemeTextBox *)theDialog->FindPaneByID( item_MessageField );
			theCaption->SetDescriptor(theLine);
			theCaption->Draw(nil);
			
			while (true) {
				hitMessage = dialog.DoDialog();
				if (hitMessage == msg_OK) {
					break;
				}
			}
		}
		::CFRelease(ourCFString);                             
	}
}


// ---------------------------------------------------------------------------
//  ¥ AskSolveUidConflicts											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskSolveUidConflicts(ResType inType, 
									  short inID, 
									  Boolean& ioApplyToOthers, 
									  Boolean askSimilar)
{
	CFStringRef formatStr = NULL, messageStr = NULL, conflictString = NULL;
	Str255      stringBuf;
	MessageT 	theMessage;
	SInt16		theAnswer = answer_Dont;
	char *		theType = new char[5];
	
	StDialogBoxHandler dialog(PPob_AskUniqueID, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	*(OSType*)theType = inType;
	theType[4] = 0;
	
	LCheckBox *	conflictsCheckBox = dynamic_cast<LCheckBox *>(theDialog->FindPaneByID( item_UidOtherConflicts ));
	ThrowIfNil_(conflictsCheckBox);
	conflictsCheckBox->SetValue(ioApplyToOthers);
	
	if (askSimilar) {
		conflictString = ::CFCopyLocalizedString(CFSTR("SolveConflictSimilarlyForNext"), NULL);
		if (conflictString != NULL) {
			if (::CFStringGetPascalString(conflictString, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding())) {
				conflictsCheckBox->SetDescriptor(stringBuf);
				conflictsCheckBox->Draw(nil);
			}
			::CFRelease(conflictString);                     
		}
	} else {
		conflictsCheckBox->Hide();
	}
	
	formatStr = ::CFCopyLocalizedString(CFSTR("AlreadyExistTypeAndID"), NULL);
	if (formatStr != NULL) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, theType, inID);
		if (messageStr != NULL)
		{
			if (::CFStringGetPascalString(messageStr, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding()))
			{
				LThemeTextBox * theCaption = (LThemeTextBox *)theDialog->FindPaneByID( item_MessageField );
				theCaption->SetDescriptor(stringBuf);
				theCaption->Draw(nil);
				
				while (true) {
					theMessage = dialog.DoDialog();
					if (theMessage == msg_UidOtherConflicts) {
						ioApplyToOthers = conflictsCheckBox->GetValue();
					} if (theMessage == msg_OK) {
						theAnswer = answer_Do;
						break;
					} else if (theMessage == msg_Cancel) {
						theAnswer = answer_Cancel;
						break;
					} else if (theMessage == msg_Dont) {
						break;
					}
				}
			}
			::CFRelease(messageStr);                             
		}
		::CFRelease(formatStr);                             
	}
	
	return theAnswer;
}


// ---------------------------------------------------------------------------
//  ¥ GetOneValue											
// ---------------------------------------------------------------------------

Boolean
UMessageDialogs::GetOneValue(
		 LCommander*	inSuper,
		 CFStringRef	inCFStringRef, 
		 ResIDT			inDialogID,
		 PaneIDT		inStaticFieldID,
		 PaneIDT		inEditFieldID,
		 SInt32&		ioValue)
{
	StDialogHandler	theHandler(inDialogID, inSuper);
	LWindow			*theDialog = theHandler.GetDialog();

	LStaticText *theStatic = dynamic_cast<LStaticText*>
								(theDialog->FindPaneByID(inStaticFieldID));
	if (theStatic == nil) {
		SignalStringLiteral_("No EditField with specified ID");
		return false;
	}

	LEditField *theField = dynamic_cast<LEditField*>
								(theDialog->FindPaneByID(inEditFieldID));
	if (theField == nil) {
		SignalStringLiteral_("No StaticField with specified ID");
		return false;
	}

	// Set the title and a default value
	Str255		promptStr;
	CFStringRef	ourCFString = NULL;

	ourCFString = ::CFCopyLocalizedString(inCFStringRef, NULL);
	if (ourCFString != NULL)
	{
		if (::CFStringGetPascalString(ourCFString, promptStr, sizeof(promptStr), ::GetApplicationTextEncoding()))
		{
			theStatic->SetDescriptor(promptStr);
		}
		::CFRelease(ourCFString);                             
	}
	theField->SetValue(ioValue);
	theField->SelectAll();
	theDialog->SetLatentSub(theField);
	theDialog->Show();

	bool		entryOK = false;

	while (true) {
		MessageT	hitMessage = theHandler.DoDialog();

		if (hitMessage == msg_Cancel) {
			break;

		} else if (hitMessage == msg_OK) {
			ioValue = theField->GetValue();
			entryOK = true;
			break;
		}
	}

	return entryOK;

}
		  	

// ---------------------------------------------------------------------------
//  ¥ AlertWithValue											
// ---------------------------------------------------------------------------

void
UMessageDialogs::AlertWithValue(CFStringRef inCFStringRef, SInt32 inValue)
{
	CFStringRef formatStr = NULL, messageStr = NULL;
	
	formatStr = CFCopyLocalizedString(inCFStringRef, NULL);
	if (formatStr != NULL) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, inValue);
		if (messageStr != NULL) {
			UMessageDialogs::SimpleMessageFromCFString(messageStr, PPob_SimpleMessage);
			CFRelease(messageStr);                     
		}
		CFRelease(formatStr);                             
	}		  	
}


// ---------------------------------------------------------------------------
//  ¥ AlertWithType											
// ---------------------------------------------------------------------------

void
UMessageDialogs::AlertWithType(CFStringRef inCFStringRef, ResType inType)
{
	Str255		theString;
	UMiscUtils::OSTypeToPString(inType, theString);	
	AlertWithString(inCFStringRef, theString);
}


// void
// UMessageDialogs::AlertWithType(CFStringRef inCFStringRef, ResType inType)
// {
// 	CFStringRef formatStr = NULL, messageStr = NULL;
// 	
// 	formatStr = CFCopyLocalizedString(inCFStringRef, NULL);
// 	if (formatStr != NULL) {
// 		char typeStr[5];
// 		*(OSType*)typeStr = inType;
// 		typeStr[4] = 0;
// 		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, typeStr);
// 		if (messageStr != NULL) {
// 			UMessageDialogs::SimpleMessageFromCFString(messageStr, PPob_SimpleMessage);
// 			CFRelease(messageStr);                     
// 		}
// 		CFRelease(formatStr);                             
// 	}		  	
// }


// ---------------------------------------------------------------------------
//  ¥ AlertWithString											
// ---------------------------------------------------------------------------

void
UMessageDialogs::AlertWithString(CFStringRef inCFStringRef, Str255 inString)
{
	char nameStr[256];
	CFStringRef formatStr = NULL, messageStr = NULL;
	
	CopyPascalStringToC(inString, nameStr);
	formatStr = CFCopyLocalizedString(inCFStringRef, NULL);
	
	if (formatStr) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, nameStr);
		
		if (messageStr) {
			UMessageDialogs::SimpleMessageFromCFString(messageStr, PPob_SimpleMessage);
			CFRelease(messageStr);       
		} 
		CFRelease(formatStr);       
	} 
}


// ---------------------------------------------------------------------------
//  ¥ AskIfWithString											
// ---------------------------------------------------------------------------

SInt16
UMessageDialogs::AskIfWithString(CFStringRef inCFStringRef, Str255 inString)
{
	char nameStr[256];
	CFStringRef formatStr = NULL, messageStr = NULL;
	SInt16		theAnswer = answer_Cancel;

	CopyPascalStringToC(inString, nameStr);
	formatStr = CFCopyLocalizedString(inCFStringRef, NULL);
	
	if (formatStr) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, nameStr);
		
		if (messageStr) {
			theAnswer = UMessageDialogs::AskIfFromLocalizable(messageStr, PPob_AskIfMessage);
			CFRelease(messageStr);       
		} 
		CFRelease(formatStr);       
	} 
	return theAnswer;
}


// ---------------------------------------------------------------------------
//  ¥ DescribeError										
// ---------------------------------------------------------------------------

void
UMessageDialogs::DescribeError(CFStringRef inCFStringRef, SInt32 inError)
{
	CFStringRef formatStr = NULL, messageStr = NULL;
	CFStringRef errorRef = NULL, errorStr = NULL;
	Str255      stringBuf;
	MessageT 	hitMessage;
	LStaticText * theStaticText;
	
	if (inError < err_RezillaErrorStart || inError > err_RezillaErrorEnd) {
		// This is not a Rezilla error
		UMessageDialogs::AlertWithValue(inCFStringRef, inError);
		return;
	} 
	
	StDialogBoxHandler dialog(PPob_ExplainedError, LCommander::GetTopCommander());		
	CThreeButtonsBox * theDialog = dialog.GetDialog();
	Assert_(theDialog != nil);
	
	formatStr = CFCopyLocalizedString(inCFStringRef, NULL);
	if (formatStr != NULL) {
		messageStr = ::CFStringCreateWithFormat(NULL, NULL, formatStr, inError);
		
		if (messageStr != NULL) {
			if (::CFStringGetPascalString(messageStr, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding())) {
				theStaticText = (LStaticText *)theDialog->FindPaneByID( item_MessageField );
				theStaticText->SetDescriptor(stringBuf);
				theStaticText->Draw(nil);

				errorRef = ::CFStringCreateWithFormat(NULL, NULL, CFSTR("%d"), inError);
				if (errorRef != NULL) {
					errorStr = CFBundleCopyLocalizedString( CFBundleGetMainBundle(), errorRef, errorRef, CFSTR("Errors") );
					if (errorStr != NULL) {
						if (::CFStringGetPascalString(errorStr, stringBuf, sizeof(stringBuf), ::GetApplicationTextEncoding())) {
							theStaticText = (LStaticText *)theDialog->FindPaneByID( item_ExplainField );
							theStaticText->SetDescriptor(stringBuf);
							theStaticText->Draw(nil);
							
							while (true) {
								hitMessage = dialog.DoDialog();
								if (hitMessage == msg_OK) {
									break;
								}
							}
						}
						::CFRelease(errorStr);                     
					}
					::CFRelease(errorRef);                             
				} 
			}
			::CFRelease(messageStr);                     
		}
		::CFRelease(formatStr);                             
	}
}


// ---------------------------------------------------------------------------
// 	DisplayPostponedError
// ---------------------------------------------------------------------------
// 	This is useful during drag & drop, when we're not supposed to be
// 	bringing up dialogs.

void 
UMessageDialogs::DisplayPostponedError(CFStringRef inCFStringRef, SInt32 inError)
{
	try
	{
		LPeriodical		*theTask = new CPostponedError(inCFStringRef, inError);
		ThrowIfMemFail_( theTask );
		theTask->StartIdling();
	}
	catch( ... )
	{
		// Just don't display an error this time
	}
}



/****************************
*                           *
*   CPostponedError CLASS   *
*                           *
****************************/

// ---------------------------------------------------------------------------
// 	CPostponedError 											[constructor]
// ---------------------------------------------------------------------------

CPostponedError::CPostponedError(CFStringRef inCFStringRef, SInt32 inError)
{
	mErrorNum = inError;
	mErrorString = inCFStringRef;
}


// ---------------------------------------------------------------------------
// 	SpendTime
// ---------------------------------------------------------------------------

void 
CPostponedError::SpendTime( const EventRecord & )
{	
	// Remove ourself from the queue right away because otherwise we will
	// be called recursively from within the error dialog handler.
	this->StopIdling();
	
	if ( mErrorNum )
		UMessageDialogs::DescribeError( mErrorString, mErrorNum );
}
