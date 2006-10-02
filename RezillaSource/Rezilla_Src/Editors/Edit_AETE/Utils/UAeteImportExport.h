// ===========================================================================
// UAeteImportExport.h
// 
//                       Created : 2004-06-10 11:41:29
//             Last modification : 2006-10-01 08:19:00
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_UAeteImportExport
#define _H_UAeteImportExport
#pragma once

#include <CFXMLNode.h>

PP_Begin_Namespace_PowerPlant

class CAeteStream;
class CTextFileStream;
class CXMLFileStream;
class CRezObj;
class CAete;

// ---------------------------------------------------------------------------

class StAeteExporter {
	
public:
						StAeteExporter(CAete *	inAete,
									   FSSpec	inFileSpec,
									   SInt16	inFormat);
						virtual ~StAeteExporter();	
	
	void			WriteOut();
	
	void			SetRezObj(CRezObj* inRezObj) {mRezObj = inRezObj;}

protected:
	CRezObj *			mRezObj;
	CAete *				mAete;
	CAeteStream *		mStream;
	CTextFileStream *	mFileStream;
	SInt16				mFormat;

private:
	void			WriteOutXml();
	void			WriteOutDerez();
	void			WriteOutSdef();
	void			WriteOutText();
	void			WriteOutHtml();
	
	void			ConvertToSdefForm(CXMLFileStream * inFileStream, OSType inType);
	void			ConvertToSdefType(CXMLFileStream * inFileStream, OSType inType, UInt16 inFlags);
	Boolean			FindClassNameForType(OSType inType, Str255 & outName);
	Boolean			FindEnumNameForType(OSType inType, Str255 & outName);

};



// ---------------------------------------------------------------------------

class StAeteImporter {
public:
						StAeteImporter(CAete *	inAete,
									   FSSpec 	inFSSpec );
						virtual ~StAeteImporter();	
	
	OSErr			ReadXml();
		
protected:
	CAete *				mAete;
	FSSpec				mFileSpec;

private:
	OSErr			ParseTree(CFXMLTreeRef inXMLTree);
	
};



PP_End_Namespace_PowerPlant


#endif

