// ===========================================================================
// CTextFileStream.h					
// 
//                       Created : 2002-06-09 19:38:34
//             Last modification : 2006-10-01 12:29:23
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2002-2006
// All rights reserved.
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

							CTextFileStream( const FSSpec& inFileSpec,
										   UInt32	inEncoding = kCFStringEncodingUTF8);

	virtual					~CTextFileStream();

	CTextFileStream&    operator << ( ConstStringPtr inString)  // Pascal string
						{
							WritePString(inString);
							return (*this);
						}

	CTextFileStream&    operator << (const char* inString)  // C string
						{
							WriteCString(inString);
							return (*this);
						}

	CTextFileStream&        operator << (char inChar)       // Single char like 'a'
						{
							WriteBlock(&inChar, sizeof(inChar));
							return (*this);
						}
	CTextFileStream&	operator << (SInt16 inNum);
	
	CTextFileStream&	operator << (SInt32 inNum);
						
	CTextFileStream&	operator << (Boolean inBool);
	

	virtual SInt32	WritePString( ConstStringPtr inString );
	
	virtual SInt32	WriteCString( const char* inString );

	virtual SInt32	WritePStringNoEnc( ConstStringPtr inString );
	
	virtual SInt32	WriteCStringNoEnc( const char* inString );

	virtual SInt32	WriteOSType(OSType inType);
	
	virtual SInt32	WriteSInt32(SInt32 inNum);

	virtual SInt32	WriteSInt16(SInt16 inNum);

	virtual SInt32	WriteBoolean(Boolean inBool);

	virtual SInt32	WriteByChunks(const char *inString, 
								Str255	inPrefix, 
								Str255	inSuffix, 
								SInt32	inLen,
								SInt32	inChunkSize);

protected:
	UInt32		mEncoding;
	
	virtual SInt32	WriteCoreString(CFStringRef	inStr);

private:			// Copy and Assignment not allowed
							CTextFileStream( const CTextFileStream& );

	CTextFileStream&			operator = ( const CTextFileStream& );
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
