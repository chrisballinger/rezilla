// ===========================================================================
// CRangeEditText.cp					
//                       Created: 2003-05-08 07:30:29
//             Last modification: 2003-05-08 10:51:43
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================



#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRangeEditText.h"
#include "UHexFilters.h"

#include "regex.h"
#include <string.h>

#include <LEditField.h>
#include <LControlImp.h>
#include <PP_KeyCodes.h>

PP_Begin_Namespace_PowerPlant


// ---------------------------------------------------------------------------
//	¥ CRangeEditText						Stream Constructor		  [public]
// ---------------------------------------------------------------------------

CRangeEditText::CRangeEditText(
	LStream*	inStream,
	ClassIDT	inImpID)
	: LEditText(inStream, inImpID)
{
	InitRangeEditText();
}


// ---------------------------------------------------------------------------
//	¥ CRangeEditText						Parameterized Constructor [public]
// ---------------------------------------------------------------------------

CRangeEditText::CRangeEditText(
	const SPaneInfo&	inPaneInfo,
	LCommander*			inSuperCommander,
	ConstStringPtr		inInitialText,
	ResIDT				inTextTraitsID,
	MessageT			inMessage,
	SInt16				inMaxChars,
	UInt8				inAttributes,
	TEKeyFilterFunc		inKeyFilter,
	bool				inPasswordField,
	ClassIDT			inImpID)

	: LEditText( inPaneInfo, inSuperCommander, inInitialText,
		inTextTraitsID, inMessage, inMaxChars, inAttributes,
		inKeyFilter, inPasswordField, inImpID)
{
	InitRangeEditText();
}


// ---------------------------------------------------------------------------
//	¥ InitRangeEditText							Initializer		   [protected]
// ---------------------------------------------------------------------------

void
CRangeEditText::InitRangeEditText()
{
	SetKeyFilter( &UHexFilters::IntegerRangeField );
}


// ---------------------------------------------------------------------------
//	¥ ~CRangeEditText							Destructor			  [public]
// ---------------------------------------------------------------------------

CRangeEditText::~CRangeEditText()
{}


#pragma mark -

// ---------------------------------------------------------------------------
//	¥ HandleKeyPress												  [public]
// ---------------------------------------------------------------------------

Boolean
CRangeEditText::HandleKeyPress(
	const EventRecord&	inKeyEvent)
{
	UInt16 theChar = (UInt16) (inKeyEvent.message & charCodeMask);
	
	if (theChar == '\r' || theChar == '\n') {
		if (mValueMessage != msg_Nothing) {
			BroadcastMessage(mValueMessage, this);
			return true;
		}
	} else {
		return LEditText::HandleKeyPress(inKeyEvent);
	}
}


// ---------------------------------------------------------------------------
//	¥ UserChangedText
// ---------------------------------------------------------------------------
//	Text of EditText has changed as a result of user action

void
CRangeEditText::UserChangedText()
{
	// Do nothing
}


// ---------------------------------------------------------------------------
//	¥ GetRangeValues												  [public]
// ---------------------------------------------------------------------------

void
CRangeEditText::GetRangeValues(SInt32 & outRangeStart, SInt32 & outRangeEnd)
{
	struct re_pattern_buffer regex;
	struct re_registers regs;
	const char *		s;
	int 				n;
	long				theNum;
	Str255				theString;
	LStr255				subString("\p");
	Size				dataSize;
	const char * 		thepattern = "([0-9]+)(-[0-9]*)?";
	int 				startpos = 0;
	
	// Get the contents of the edit field
	GetDescriptor(theString);
	dataSize = theString[0] ;
	char * theBuffer = new char[dataSize+1];
	theBuffer[dataSize] = 0;
	::CopyPascalStringToC( theString, theBuffer );			
	
	// Compile the regexp
	memset(&regex, '\0', sizeof(regex));
	regs.start = regs.end = NULL;
	regs.num_regs = 0;
	
	::re_set_syntax(RE_SYNTAX_POSIX_EXTENDED);
	
	s = ::re_compile_pattern( thepattern, strlen(thepattern), &regex);
	// Error if re_compile_pattern returned non-NULL value
	ThrowIfNot_(s == NULL);
	
	if ( ::re_search(&regex, theBuffer, dataSize, startpos, dataSize, &regs) >= 0 )
	{
		subString.Assign( theBuffer + regs.start[1], regs.end[1] - regs.start[1]);
		// Convert string to num
		::StringToNum( subString , &theNum);		
		outRangeStart = theNum;
		
		// Convert string to num
		if (regs.end[2] == regs.start[2]) {
			// No end value specified
			outRangeEnd = outRangeStart;
		} else if (regs.end[2] == regs.start[2] + 1) {
			// No value specified after the dash. Set to -1 which 
			// will be interpreted as end of text.
			outRangeEnd = -1;
		} else {
			subString.Assign( theBuffer + regs.start[2] + 1, regs.end[2] - regs.start[2] - 1);
			::StringToNum( subString , &theNum);
			// Make sure outRangeStart is smaller than outRangeEnd
			if (theNum < outRangeStart) {
				outRangeEnd = outRangeStart;
				outRangeStart = theNum;
			} else {
				outRangeEnd = theNum;
			}
		}
	}
	regfree(&regex);
}



PP_End_Namespace_PowerPlant
