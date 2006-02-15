// ===========================================================================
// CTextHandleStream.h					
// 
//                       Created: 2002-06-15 10:36:17
//             Last modification: 2004-02-22 19:48:07
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003, 2004
// All rights reserved.
// ===========================================================================
//

#ifndef _H_CTextHandleStream
#define _H_CTextHandleStream
#pragma once

#include <LFileStream.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CTextHandleStream : public LHandleStream {
public:
							CTextHandleStream();

							CTextHandleStream( const LHandleStream& inOriginal );

							CTextHandleStream( Handle inHandle );

	virtual					~CTextHandleStream();

	CTextHandleStream&	operator << ( ConstStringPtr inString)	// Pascal string
						{
							WritePString(inString);
							return (*this);
						}

	CTextHandleStream&	operator << (const char* inString)	// C string
						{
							WriteCString(inString);
							return (*this);
						}

	CTextHandleStream&		operator << (char inChar)		// Single char like 'a'
						{
							WriteBlock(&inChar, sizeof(inChar));
							return (*this);
						}


	CTextHandleStream&	operator << (SInt32 inNum);
	
	CTextHandleStream&	operator << (Boolean inBool);
	

	SInt32			WritePString( ConstStringPtr inString );
	
	SInt32			WriteCString( const char* inString );

	SInt32			WritePStringWithTag( ConstStringPtr inString, ConstStringPtr inTag);
	
	SInt32			WriteCStringWithTag( const char *inString, const char *inTag);

	SInt32			WriteSInt32WithTag( SInt32 inNum, ConstStringPtr inTag);

	SInt32			WriteSInt32WithTag( SInt32 inNum, const char *inTag);

	SInt32			WriteBooleanWithTag( Boolean inBool, ConstStringPtr inTag);

	SInt32			WriteBooleanWithTag( Boolean inBool, const char *inTag);

private:			// Copy and Assignment not allowed
							CTextHandleStream( const CTextHandleStream& );

	CTextHandleStream&			operator = ( const CTextHandleStream& );
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
