// ===========================================================================
// CRangeEditText.h					
//                       Created: 2003-05-08 07:30:29
//             Last modification: 2003-05-08 10:51:55
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// ¬© Copyright: Bernard Desgraupes 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#ifndef _H_CRangeEditText
#define _H_CRangeEditText
#pragma once

#include <LEditText.h>
#include <UKeyFilters.h>

#include <TextEdit.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LTETypingAction;
class	LString;

// ---------------------------------------------------------------------------

class CRangeEditText : public LEditText {

public:
	enum {	class_ID		= FOUR_CHAR_CODE('Retx'),
			imp_class_ID	= FOUR_CHAR_CODE('ietx') };

						CRangeEditText(
								LStream* inStream,
								ClassIDT inImpID = imp_class_ID);

						CRangeEditText(
								const SPaneInfo&	inPaneInfo,
								LCommander*			inSuperCommander,
								ConstStringPtr		inInitialText,
								ResIDT				inTextTraitsID,
								MessageT			inMessage,
								SInt16				inMaxChars,
								UInt8				inAttributes,
								TEKeyFilterFunc		inKeyFilter,
								bool				inPasswordField = false,
								ClassIDT			inImpID = imp_class_ID);

	virtual				~CRangeEditText();

	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );
	
	void				GetRangeValues(SInt32 & outRangeStart, SInt32 & outRangeEnd);

	virtual void		UserChangedText();

private:
	void				InitRangeEditText();

};


PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

