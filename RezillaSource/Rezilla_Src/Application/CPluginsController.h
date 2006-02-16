// ===========================================================================
// CPluginsController.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-16 19:48:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPluginsController
#define _H_CPluginsController
#pragma once

class CRezillaPlugin;
class CRezMapDoc;
class CRezObjItem;

class CPluginsController {

public:
						CPluginsController();
				virtual	~CPluginsController();
		
		static Boolean	HasPluginForType(ResType inType, ResType * substType);

		static void		InvokePluginEditor(CRezMapDoc* inRezMapDoc, 
										   CRezObjItem * inRezObjItem,
										   ResType inUseType);

		static CFMutableDictionaryRef	sPluginsDict;
		
protected:
		static TArray<CRezillaPlugin*>	sPluginsList;


private:
		OSErr			BuildInternalPluginsDictionary();
		OSErr			BuildExternalPluginsDictionary();
		
		OSErr			ScanPluginsFolder(FSRef * inPluginsRef);
		OSErr			ScanPluginsFolder(CFURLRef inPlugInsURL);
		
		OSErr			AddPluginToDictionary(CFBundleRef inBundleRef);
		OSErr			AddEntriesForPlugin(CRezillaPlugin * inRezPlugin);
		
		static CRezillaPlugin *	GetPreferredPlugin(ResType inType);
		
};


#endif
