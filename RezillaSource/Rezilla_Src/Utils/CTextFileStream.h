// ===========================================================================
// CTextFileStream.h					
// 
//                       Created : 2002-06-09 19:38:34
//             Last modification : 2005-02-07 23:40:00
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2002-2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
//

#ifndef _H_CTextFileStream
#define _H_CTextFileStream
#pragma once

#include <LFileStream.h>


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CTextFileStream : public LFileStream {
public:
							CTextFileStream();

							CTextFileStream( const FSSpec& inFileSpec );

							CTextFileStream(
									AliasHandle		inAlias,
									Boolean&		outWasChanged,
									FSSpec*			inFromFile = nil);

	virtual					~CTextFileStream();

	CTextFileStream&	operator << ( ConstStringPtr inString)	// Pascal string
						{
							WritePString(inString);
							return (*this);
						}

	CTextFileStream&	operator << (const char* inString)	// C string
						{
							WriteCString(inString);
							return (*this);
						}

	CTextFileStream&		operator << (char inChar)		// Single char like 'a'
						{
							WriteBlock(&inChar, sizeof(inChar));
							return (*this);
						}


	CTextFileStream&	operator << (SInt32 inNum);
	
	CTextFileStream&	operator << (Boolean inBool);
	

	SInt32			WriteOSType(OSType inType);
	
	SInt32			WriteOSTypeWithTag(OSType inType, ConstStringPtr inTag);

	SInt32			WriteOSTypeWithTag(OSType inType, const char *inTag);

	SInt32			WritePString( ConstStringPtr inString );
	
	SInt32			WritePStringWithTag( ConstStringPtr inString, ConstStringPtr inTag);
	
	SInt32			WriteCString( const char* inString );

	SInt32			WriteCStringWithTag( const char *inString, const char *inTag);

	SInt32			WriteSInt32WithTag( SInt32 inNum, ConstStringPtr inTag);

	SInt32			WriteSInt32WithTag( SInt32 inNum, const char *inTag);

	SInt32			WriteBooleanWithTag( Boolean inBool, ConstStringPtr inTag);

	SInt32			WriteBooleanWithTag( Boolean inBool, const char *inTag);

	SInt32			WriteByChunks(const char *inString, 
								Str255	inPrefix, 
								Str255	inSuffix, 
								SInt32	inLen,
								SInt32	inChunkSize);

private:			// Copy and Assignment not allowed
							CTextFileStream( const CTextFileStream& );

	CTextFileStream&			operator = ( const CTextFileStream& );
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
