// ===========================================================================
// CTemplatesController.h
// 
//                       Created: 2004-08-06 12:57:55
//             Last modification: 2004-08-09 10:06:58
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
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
	tmpl_internal,
	tmpl_external
};


class	CRezMap;
class	CRezFile;


class CTemplatesController {

public:
							CTemplatesController();
			virtual			~CTemplatesController();
	
		static Boolean		HasTemplateForType(ResType inType, ResType * substType);
		
		static Boolean		HasExternalTemplateForType(ResType inType,
													   FSRef * outFileRef);

		static Handle		GetTemplateHandle(ResType inType);

		static SInt16		GetTemplateKind() { return sTemplateKind;}

		static FSRef		GetTemplateFileRef() { return sTemplateFile;}

		static TArray<OSType>	sInternalTemplates;
		static CRezMap *		sTemplatesMap;
		static CFDictionaryRef	sExternalTemplates;
		static CFDictionaryRef	sPreferedTemplates;
		static SInt16			sTemplateKind;
		static FSRef			sTemplateFile;


protected:

	
private:
	OSErr				RegisterInternalTemplates();
	OSErr				AddTemplatesToDictionary(FSRef * inFileRef, CFMutableDictionaryRef inDict);
	CFDictionaryRef		BuildExternalTemplatesDictionary();

};

#endif // _H_CTemplatesController