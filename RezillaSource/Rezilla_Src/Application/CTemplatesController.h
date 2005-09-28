// ===========================================================================
// CTemplatesController.h
// 
//                       Created: 2004-08-06 12:57:55
//             Last modification: 2005-09-27 12:04:52
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// Deals with third party templates (locating in Application Support 
// folders) and with substitution types (type defined with a 'type 
// as' instruction in the Rez files).

#ifndef _H_CTemplatesController
#define _H_CTemplatesController
#pragma once

enum {
	tmpl_none = 0,
	tmpl_local,
	tmpl_internal,
	tmpl_external
};


class	CRezMap;
class	CRezFile;


class CTemplatesController {

public:
							CTemplatesController();
			virtual			~CTemplatesController();
	
		static Boolean		HasTemplateForType(ResType inType, 
											   ResType * substType, 
											   CRezMap * inRezMap);
		
		static Boolean		HasLocalTemplateForType(Str255 inName, 
													CRezMap * inRezMap);

		static Boolean		HasInternalTemplateForType(ResType inType);
		
		static Boolean		HasExternalTemplateForType(ResType inType,
													   FSRef * outFileRef);

		static Handle		GetTemplateHandle(ResType inType);

		static SInt16		GetTemplateKind() { return sTemplateKind;}

		static FSRef		GetTemplateFileRef() { return sTemplateFile;}

		static CFComparisonResult	TypeSorter(const void *lhs, const void *rhs, void *context);
		

		static CRezMap *		sTemplatesMap;
		static CFArrayRef		sInternalTemplates;
		static CFDictionaryRef	sExternalTemplates;
		// static CFDictionaryRef	sPreferedTemplates;
		static CFArrayRef		sAllTypesArray;
		static SInt16			sTemplateKind;
		static FSRef			sTemplateFile;


protected:

	
private:
		OSErr				BuildInternalTemplatesArray();
		OSErr				BuildExternalTemplatesDictionary();
		OSErr				ScanTemplatesFolder(FSRef * inTmplFolder);
		OSErr				AddTemplatesToDictionary(FSRef * inFileRef);
		void				AddAsTypesToAllTypes();

};

#endif // _H_CTemplatesController