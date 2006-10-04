// ===========================================================================
// CXMLFileStream.h
// 
//                       Created : 2006-09-29 17:28:30
//             Last modification : 2006-10-01 13:41:19
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2006
// All rights reserved.
// ===========================================================================
//

#ifndef _H_CXMLFileStream
#define _H_CXMLFileStream
#pragma once

#include "CTextFileStream.h"

enum {
	tag_open,
	tag_close,
	tag_empty
};


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class CXMLFileStream : public CTextFileStream {
public:

							CXMLFileStream();

							CXMLFileStream( const FSSpec& inFileSpec,
										   UInt32 inEncoding = kCFStringEncodingUTF8,
										   Boolean inEncodeTags = false);
							
				virtual		~CXMLFileStream();

	virtual SInt32	WriteTag(const char *inName, UInt32 inKind, Boolean addNewLine = true, UInt8 indent = 0);
	
	virtual SInt32	WriteTag(ConstStringPtr inName, UInt32 inKind, Boolean addNewLine = true, UInt8 indent = 0);
		
	virtual SInt32	WritePStringEnclosed( ConstStringPtr inString, ConstStringPtr inTag, UInt8 indent = 0);
	
	virtual SInt32	WriteCStringEnclosed( const char *inString, const char *inTag, UInt8 indent = 0);
	
	virtual SInt32	WriteOSTypeEnclosed(OSType inType, ConstStringPtr inTag, UInt8 indent = 0);

	virtual SInt32	WriteOSTypeEnclosed(OSType inType, const char *inTag, UInt8 indent = 0);

	virtual SInt32	WriteSInt32Enclosed(const SInt32 inValue, const char *inTag, UInt8 indent = 0);

	virtual SInt32	WriteSInt16Enclosed(const SInt16 inValue, const char *inTag, UInt8 indent = 0);

	virtual SInt32	WriteBooleanEnclosed( Boolean inBool, ConstStringPtr inTag, UInt8 indent = 0);

	virtual SInt32	WriteBooleanEnclosed( Boolean inBool, const char *inTag, UInt8 indent = 0);

protected:
	Boolean		mEscapeEntities;
	Boolean		mEncodeTags;
	
	virtual SInt32	WriteCoreString(CFStringRef	inStr);

private:
							// Copy and Assignment not allowed
							CXMLFileStream( const CXMLFileStream& );
	CXMLFileStream&			operator = ( const CXMLFileStream& );
	
	SInt32			WriteEscapedString(CFStringRef inEscStr, UInt8 trim);
	
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
