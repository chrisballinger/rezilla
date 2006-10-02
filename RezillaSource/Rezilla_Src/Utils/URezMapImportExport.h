// ===========================================================================
// URezMapImportExport.h
// 
//                       Created : 2004-02-29 10:41:09
//             Last modification : 2006-10-01 08:11:30
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_URezMapImportExport
#define _H_URezMapImportExport
#pragma once


PP_Begin_Namespace_PowerPlant

class CRezMap;
class CTextFileStream;
class CRezMapTable;

// ---------------------------------------------------------------------------

class StRezMapExporter {
	
public:
						StRezMapExporter( CTextFileStream * inFileStream);
						virtual ~StRezMapExporter();	
	
	void	WriteOutHtml(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding);
	void	WriteOutText(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding);
	void	WriteOutXml(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding);
	void	WriteOutDerez(CRezMap* inRezMap);
	
	// Accessors
	virtual CTextFileStream *	GetFileStream() { return mFileStream;}
	void						SetFileStream(CTextFileStream * theFileStream) 
										{mFileStream = theFileStream ;}
	
protected:
	CTextFileStream *	mFileStream;
	Str255				mName;

private:
	
};




// ---------------------------------------------------------------------------

class StRezMapImporter {
public:
					StRezMapImporter(CRezMapTable *	inRezMapTable, 
									 FSSpec 		inFSSpec);
					virtual ~StRezMapImporter();	
	
	OSErr			ReadXml();
		
protected:
	CRezMapTable *	mRezMapTable;
	FSSpec			mFileSpec;

private:
	OSErr			ParseTree(CFXMLTreeRef inXMLTree);
	
};


PP_End_Namespace_PowerPlant


#endif

