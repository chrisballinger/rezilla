// ===========================================================================
// URezMapImportExport.cp					
// 
//                       Created : 2004-02-29 10:41:09
//             Last modification : 2006-10-05 19:24:53
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@users.sourceforge.net>
// www : <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2004-2006
// All rights reserved.
// ===========================================================================


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CRezMap.h"
#include "CRezType.h"
#include "CRezObj.h"
#include "CTextFileStream.h"
#include "CXMLFileStream.h"
#include "CRezMapDoc.h"
#include "RezillaConstants.h"
#include "URezMapImportExport.h"
#include "UCodeTranslator.h"
#include "UCompareUtils.h"
#include "UMiscUtils.h"

#include <stdio.h>


PP_Begin_Namespace_PowerPlant


// ======================
// Class StRezMapExporter
// ======================



// ---------------------------------------------------------------------------
//   StRezMapExporter								Constructor	 		[public]
// ---------------------------------------------------------------------------


StRezMapExporter::StRezMapExporter(CTextFileStream * inFileStream)
{	
	FSSpec		theFileSpec;
	ThrowIfNil_(inFileStream);
	mFileStream = inFileStream;
	mFileStream->GetSpecifier(theFileSpec);
	LString::CopyPStr(theFileSpec.name, mName);
}


// ---------------------------------------------------------------------------
//     ~StRezMapExporter						Destructor			  [public]
// ---------------------------------------------------------------------------

StRezMapExporter::~StRezMapExporter()
{}


// ---------------------------------------------------------------------------------
//   WriteOutText
// ---------------------------------------------------------------------------------

void
StRezMapExporter::WriteOutText(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding)
{
	CTypeComparator* theComparator = new CTypeComparator;
	TArray<ResType>* theTypesArray = new TArray<ResType>( theComparator, true);
	TArrayIterator<ResType>	typeIterator(*theTypesArray);
	Str255		tempString, typeString;
	CRezType *	theRezType;
	CRezObj *	theRezObj;
	ResType		theType;
	short		theID;	
	Handle		theData;

	*mFileStream << mName;
	*mFileStream << "\r\r";

	*mFileStream << "TYPE\tID\tSIZE\tFLAGS\tNAME\r\r";
	
	inRezMap->GetAllTypes(theTypesArray);
	while (typeIterator.Next(theType)) {
		LLongComparator* theIDComparator = new LLongComparator;
		TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
		TArrayIterator<short>	idIterator(*theIdArray);
		
		UMiscUtils::OSTypeToPString(theType, typeString);			

		theRezType = new CRezType(theType, inRezMap);
		theRezType->GetAllRezIDs(theIdArray);
		
		while (idIterator.Next(theID)) {
			theRezObj = new CRezObj(theRezType, theID);
			*mFileStream << typeString;
			*mFileStream << "\t";
			
			::NumToString(theRezObj->GetID(), tempString);
			*mFileStream << tempString;
			*mFileStream << "\t";
			::NumToString(theRezObj->GetSize(), tempString);
			*mFileStream << tempString;
			*mFileStream << "\t";
			::NumToString(theRezObj->GetAttributes(), tempString);
			*mFileStream << tempString;
			*mFileStream << "\t";
			*mFileStream << *(theRezObj->GetName());
			if (includeData) {
				theData = theRezObj->GetData();
				if (theData != nil) {
					switch (dataEncoding) {
					  case export_Base64Enc: {
						StByteToBase64Translator translator(theData);
						translator.Convert();
						(*mFileStream).WriteByChunks( *(translator.GetOutHandle()), 
									"\p\r\t", "\p", 
									translator.GetOutSize(), 48);
						break;
					  }
					  
					  case export_HexEnc: {
						StByteToHexTranslator translator(theData);
						translator.Convert();
						(*mFileStream).WriteByChunks( *(translator.GetOutHandle()), 
									"\p\r\t", "\p", 
									translator.GetOutSize(), 60);
						break;
					  }
					}
				}
			}
			
			*mFileStream << "\r";
			delete theRezObj;
		}
		idIterator.ResetTo(0);
		delete theIdArray;
		delete theRezType;
	}
}


// ---------------------------------------------------------------------------------
//   WriteOutXml
// ---------------------------------------------------------------------------------
// Written according to the Rezilla (previously Rezmap1) DTD. Resource data
// are either Base64 or Hex encoded depending on the preference.
// For XML format, mExportStream is a CXMLFileStream.

void
StRezMapExporter::WriteOutXml(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding)
{
	CRezType *	theRezType;
	CRezObj *	theRezObj;
	ResType		theType;
	short		theID;	
	short		theAttrs;
	Handle		theData;

	CTypeComparator* theComparator = new CTypeComparator;
	TArray<ResType>* theTypesArray = new TArray<ResType>( theComparator, true);
	TArrayIterator<ResType>	typeIterator(*theTypesArray);

	CXMLFileStream * theStream = dynamic_cast<CXMLFileStream *>(mFileStream);
	
	if (theStream == NULL) {
		return;
	} 
	
	theStream->WriteCStringNoEnc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r");
	theStream->WriteCStringNoEnc("<!DOCTYPE RezMap SYSTEM \"file://localhost/System/Library/DTDs/Rezilla.dtd\">\r");
	
	theStream->WriteTag("RezMap", tag_open);
	theStream->WritePStringEnclosed(mName, "\pRezMapName");
	inRezMap->GetMapAttributes(theAttrs);	
	theStream->WriteSInt16Enclosed(theAttrs, "RezMapFlags");
	theStream->WriteTag("TypesArray", tag_open, true, 1);

	inRezMap->GetAllTypes(theTypesArray);
	while (typeIterator.Next(theType)) {
		LLongComparator* theIDComparator = new LLongComparator;
		TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
		TArrayIterator<short>	idIterator(*theIdArray);
		
		theStream->WriteTag("Type", tag_open, true, 2);
		theStream->WriteOSTypeEnclosed(theType, "TypeCode", 3);
				
		theStream->WriteTag("ResourcesArray", tag_open, true, 3);

		theRezType = new CRezType(theType, inRezMap);
		theRezType->GetAllRezIDs(theIdArray);
		
		while (idIterator.Next(theID)) {
			theRezObj = new CRezObj(theRezType, theID);
			theStream->WriteTag("Resource", tag_open, true, 4);
			
			theStream->WriteSInt16Enclosed(theRezObj->GetID(), "ResourceID", 5);

			theStream->WritePStringEnclosed( *(theRezObj->GetName()), "\pResourceName", 5);

			theStream->WriteSInt16Enclosed(theRezObj->GetAttributes(), "ResourceFlags", 5);
			
			// Note: the ResourceSize tag is optional in the DTD. Let's skip it.
			// theStream->WriteSInt16Enclosed(theRezObj->GetSize(), "ResourceSize", 5);
			
			if (includeData) {
				theStream->WriteTag("ResourceData", tag_open, false, 5);
				theData = theRezObj->GetData();
				if (theData != nil) {
					// Note: since version 1.1, XML output is always Base64 encoded
					switch (dataEncoding) {
					  case export_Base64Enc: {
						StByteToBase64Translator translator(theData);
						translator.Convert();
						theStream->WriteByChunks( *(translator.GetOutHandle()), 
									"\p\r\t\t\t\t\t", "\p", 
									translator.GetOutSize(), 48);
						break;
					  }
					  
					  case export_HexEnc: {
						StByteToHexTranslator translator(theData);
						translator.Convert();
						theStream->WriteByChunks( *(translator.GetOutHandle()), 
									"\p\r\t\t\t\t\t", "\p", 
									translator.GetOutSize(), 60);
						break;
					  }
					}
				}
				*theStream << "\r";
				theStream->WriteTag("ResourceData", tag_close, true, 5);
			} else {
				theStream->WriteTag("ResourceData", tag_empty, true, 5);
			}
				
			theStream->WriteTag("Resource", tag_close, true, 4);
			delete theRezObj;
		}
		theStream->WriteTag("ResourcesArray", tag_close, true, 3);
		theStream->WriteTag("Type", tag_close, true, 2);

		idIterator.ResetTo(0);
		delete theIdArray;
		delete theRezType;
	}
	
	theStream->WriteTag("TypesArray", tag_close, true, 1);
	theStream->WriteTag("RezMap", tag_close);
}


// ---------------------------------------------------------------------------------
//   WriteOutHtml
// ---------------------------------------------------------------------------------
// 			// substitute %20 for spaces in the string
// 			for (UInt8 i = tempStr.Find("\p "); i > 0; i = tempStr.Find("\p "))
// 				tempStr.Replace(i, 1, "\p%20");

void
StRezMapExporter::WriteOutHtml(CRezMap* inRezMap, Boolean includeData, SInt32 dataEncoding)
{
#pragma unused(includeData, dataEncoding)
		
	CTypeComparator* theComparator = new CTypeComparator;
	TArray<ResType>* theTypesArray = new TArray<ResType>( theComparator, true);
	TArrayIterator<ResType>	typeIterator(*theTypesArray);
	Str255		tempString;
	CRezType *	theRezType;
	CRezObj *	theRezObj;
	ResType		theType;
	short		theID;	

	CXMLFileStream * theStream = dynamic_cast<CXMLFileStream *>(mFileStream);
	
	if (theStream == NULL) {
		return;
	} 
	
	theStream->WriteCStringNoEnc("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">");
	theStream->WriteCStringNoEnc("<HTML>\r<HEAD>\r<TITLE>");
	*theStream << mName;
	theStream->WriteCStringNoEnc("</TITLE>\r");
	theStream->WriteCStringNoEnc("<META NAME=GENERATOR CONTENT=\"Rezilla\">\r");
	theStream->WriteCStringNoEnc("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\r");
	theStream->WriteCStringNoEnc("</HEAD>\r<BODY>\r<TABLE border=\"1\">\r");

	theStream->WriteCStringNoEnc("\r\t<TR>\r\t\t<TD><B>Type</B></TD><TD><B>ID</B></TD><TD><B>Size</B></TD><TD><B>Flags</B></TD><TD><B>Name</B></TD>\r\t</TR>\r");

	inRezMap->GetAllTypes(theTypesArray);
	while (typeIterator.Next(theType)) {
		LLongComparator* theIDComparator = new LLongComparator;
		TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
		TArrayIterator<short>	idIterator(*theIdArray);
		
		UMiscUtils::OSTypeToPString(theType, tempString);			
		theStream->WriteCStringNoEnc("\t<TR>\r\t\t<TD>");
		*theStream << tempString;
		theStream->WriteCStringNoEnc("</TD>\r\t</TR>\r");
		
		theRezType = new CRezType(theType, inRezMap);
		theRezType->GetAllRezIDs(theIdArray);
		
		while (idIterator.Next(theID)) {
			theRezObj = new CRezObj(theRezType, theID);
			
			theStream->WriteCStringNoEnc("\t<TR>\r\t\t<TD></TD><TD>");
			*theStream << theRezObj->GetID();
			theStream->WriteCStringNoEnc("</TD><TD>");
			*theStream << theRezObj->GetSize();
			theStream->WriteCStringNoEnc("</TD><TD>");
			*theStream << theRezObj->GetAttributes();
			theStream->WriteCStringNoEnc("</TD><TD>");
			*theStream << *(theRezObj->GetName());
			theStream->WriteCStringNoEnc("</TD>\r\t</TR>\r");
			delete theRezObj;
		}
		idIterator.ResetTo(0);
		delete theIdArray;
		delete theRezType;
	}
	theStream->WriteCStringNoEnc("</TABLE>\r</BODY>\r</HTML>\r");
}


// ---------------------------------------------------------------------------------
//   WriteOutDerez
// ---------------------------------------------------------------------------------
// Written according to the DeRez output format.

void
StRezMapExporter::WriteOutDerez(CRezMap* inRezMap)
{
	CTypeComparator* theComparator = new CTypeComparator;
	TArray<ResType>* theTypesArray = new TArray<ResType>( theComparator, true);
	TArrayIterator<ResType>	typeIterator(*theTypesArray);
	Str255		tempString, typeString;
	CRezType *	theRezType;
	CRezObj *	theRezObj;
	ResType		theType;
	short		theID;	
	Handle		theData;
	
	inRezMap->GetAllTypes(theTypesArray);
	while (typeIterator.Next(theType)) {
		LLongComparator* theIDComparator = new LLongComparator;
		TArray<short>* theIdArray = new TArray<short>(theIDComparator, true);
		TArrayIterator<short>	idIterator(*theIdArray);
		
		UMiscUtils::OSTypeToPString(theType, typeString);			
		
		theRezType = new CRezType(theType, inRezMap);
		theRezType->GetAllRezIDs(theIdArray);
		
		while (idIterator.Next(theID)) {
			theRezObj = new CRezObj(theRezType, theID);
			
			*mFileStream << "data '";
			*mFileStream << typeString;
			*mFileStream << "' (";
			::NumToString(theRezObj->GetID(), tempString);
			*mFileStream << tempString;
			*mFileStream << ", \"";
			*mFileStream << *(theRezObj->GetName());
			*mFileStream << "\"";

			// Are there flags set ?
			if (theRezObj->HasAttribute(resPurgeable)) {
				*mFileStream << ", purgeable";
			} 
			if (theRezObj->HasAttribute(resLocked)) {
				*mFileStream << ", locked";
			} 
			if (theRezObj->HasAttribute(resProtected)) {
				*mFileStream << ", protected";
			} 
			if (theRezObj->HasAttribute(resPreload)) {
				*mFileStream << ", preload";
			} 
			*mFileStream << ") {";
			
			theData = theRezObj->GetData();
			if (theData != nil) {
				StByteToHexTranslator translator(theData);
				translator.Convert();
				(*mFileStream).WriteByChunks( *(translator.GetOutHandle()), 
											 "\p\r\t$\"", "\p\"", 
											 translator.GetOutSize(), 48);
			 }
			 *mFileStream << "\r};\r\r" ;
			 
			 delete theRezObj;
		 }
		 idIterator.ResetTo(0);
		 delete theIdArray;
		 delete theRezType;
	 }
 }


#pragma mark -

// ======================
// Class StRezMapImporter
// ======================

// ---------------------------------------------------------------------------
//   StRezMapImporter							Constructor		 	 [public]
// ---------------------------------------------------------------------------

StRezMapImporter::StRezMapImporter(CRezMapDoc *	inRezMapDoc,
								FSSpec 	inFSSpec )
{	
	mRezMapDoc = inRezMapDoc;
	mFileSpec = inFSSpec;
}


// ---------------------------------------------------------------------------
//     ~StRezMapImporter						Destructor			  [public]
// ---------------------------------------------------------------------------

StRezMapImporter::~StRezMapImporter()
{}


// ---------------------------------------------------------------------------
//  ReadXml															 [public]
// ---------------------------------------------------------------------------

OSErr
StRezMapImporter::ReadXml()
{
	OSErr			error;
	CFURLRef		theUrl;
	FSRef   	 	theFSRef;
	CFXMLTreeRef    cfXMLTree;
	
	error = FSpMakeFSRef( &mFileSpec, &theFSRef );
	theUrl = ::CFURLCreateFromFSRef(kCFAllocatorDefault, &theFSRef);
	
	// Load the XML data
	if (theUrl) {
		// kCFXMLParserSkipWhitespace is very important here otherwise
		// Rezilla will complain about unknown tags (in the aete objects)
		cfXMLTree = ::CFXMLTreeCreateWithDataFromURL(kCFAllocatorDefault, theUrl, 
												   kCFXMLParserSkipWhitespace, kCFXMLNodeCurrentVersion);
		
		if (cfXMLTree != NULL) {
			error = ParseTree(cfXMLTree);
		} else {
			error = err_ImportCantBuildTree;
		}
	} 
	
	return error;
}


// ---------------------------------------------------------------------------
//  ParseTree														 [private]
// ---------------------------------------------------------------------------

OSErr
StRezMapImporter::ParseTree(CFXMLTreeRef inXMLTree)
{
	OSErr			error = err_ImportMissingRootElement;
	CFXMLTreeRef    xmlTreeNode;
	CFXMLNodeRef    xmlNode;
	int             childCount;
	int             index;
	
	// Get a count of the top level node's children.
	childCount = CFTreeGetChildCount(inXMLTree);
	
	// Print the data string for each top-level node.
	for (index = 0; index < childCount; index++) {
		xmlTreeNode = CFTreeGetChildAtIndex(inXMLTree, index);
		if (xmlTreeNode) {
			xmlNode = CFXMLTreeGetNode(xmlTreeNode);
			if (xmlNode) {
				if (CFXMLNodeGetTypeCode(xmlNode) == kCFXMLNodeTypeElement) {
					if (! CFStringCompare( CFXMLNodeGetString(xmlNode), CFSTR("RezMap"), 0)) {
						error = mRezMapDoc->GetRezMapFromXml(xmlTreeNode);
					} else {
						error = err_ImportWrongRootElement;
					}
				}
			} 
		} 
	}	
	return error;
}
 


PP_End_Namespace_PowerPlant




