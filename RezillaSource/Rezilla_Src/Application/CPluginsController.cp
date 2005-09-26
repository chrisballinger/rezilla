// ===========================================================================
// CPluginsController.cp
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-26 10:29:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#include "CPluginsController.h"
#include "UMiscUtils.h"


// ---------------------------------------------------------------------------
//  CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::CPluginsController()
{
	ScanPluginsFolders();
}


// ---------------------------------------------------------------------------
//  ~CPluginsController												[public]
// ---------------------------------------------------------------------------

CPluginsController::~CPluginsController()
{
}


// ---------------------------------------------------------------------------
//  HasPluginForType												[public]
// ---------------------------------------------------------------------------

Boolean
CPluginsController::HasPluginForType(ResType inType)
{
	Boolean hasPlugin = false;
	
	
	return hasPlugin;
}


// ---------------------------------------------------------------------------
//  RegisterPlugin												[public]
// ---------------------------------------------------------------------------

OSErr
CPluginsController::RegisterPlugin()
{
}


// ---------------------------------------------------------------------------
//  UnregisterPlugin												[public]
// ---------------------------------------------------------------------------

void
CPluginsController::UnregisterPlugin()
{
}


// ---------------------------------------------------------------------------
//  LoadPlugin												[public]
// ---------------------------------------------------------------------------

void
CPluginsController::LoadPlugin()
{
}


// ---------------------------------------------------------------------------
//	¥ ScanPluginsFolders										[private]
// ---------------------------------------------------------------------------
// Scan the PlugIns subfolders inside Rezilla's Application Support
// folder. Create them if necessary.
// They can reside in two domains:
// 		kLocalDomain	---> Library/Application Support/Rezilla/PlugIns
// 		kUserDomain		---> ~/Library/Application Support/Rezilla/PlugIns
// 		
// kNetworkDomain ?

OSErr
CPluginsController::ScanPluginsFolders()
{
	OSErr					error = noErr;
	UInt32   				domainIndex;
	FSRef					appSupportRef, rezillaRef, templateRef, fileRef;
	// kUserDomain, kNetworkDomain, kLocalDomain, kSystemDomain
	static const SInt16 kFolderDomains[] = {kUserDomain, kLocalDomain, 0};
		

	domainIndex = 0;
	do {
		error = FSFindFolder(kFolderDomains[domainIndex], kApplicationSupportFolderType, kCreateFolder, &appSupportRef);
		// If we can't find or create the folder in this domain, just ignore the domain.
		if (error == noErr) {
			HFSUniStr255 	unicodeName;
			ConstStr31Param rzilName = "\pRezilla";
			ConstStr31Param plugName = "\pPlugIns";
			
			// If we found the Support folder, look for a Templates subfolder
			UMiscUtils::HFSNameToUnicodeName(rzilName, &unicodeName);
			error = FSMakeFSRefUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
									   kTextEncodingUnknown, &rezillaRef);
			if (error != noErr) {
				error = FSCreateDirectoryUnicode(&appSupportRef, unicodeName.length, unicodeName.unicode, 
												 kFSCatInfoNone, NULL, &rezillaRef, NULL, NULL);
			}
			
			if (error == noErr) {
				UMiscUtils::HFSNameToUnicodeName(plugName, &unicodeName);
				error = FSMakeFSRefUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
										   kTextEncodingUnknown, &templateRef);
				if (error != noErr) {
					error = FSCreateDirectoryUnicode(&rezillaRef, unicodeName.length, unicodeName.unicode, 
													 kFSCatInfoNone, NULL, &templateRef, NULL, NULL);
				}
			} 			
		}
		domainIndex += 1;
	} while ( kFolderDomains[domainIndex] != 0 );
	
	return error;
}


