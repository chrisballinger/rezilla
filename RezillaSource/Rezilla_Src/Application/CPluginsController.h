// ===========================================================================
// CPluginsController.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-09-28 10:23:17
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

		static CRezillaPlugin *	GetPluginByName(CFStringRef inName);

		static CRezillaPlugin *	GetPreferredPlugin(ResType inType);
		static OSErr			SetPreferredPlugin(ResType inType, CRezillaPlugin * inPlugin);

		static CFMutableDictionaryRef	sPluginsDict;
		static CFDictionaryRef			sPrefsDict;
		static TArray<CRezillaPlugin*>	sPluginsList;

private:
		OSErr			BuildPluginsDictionary();
		
		OSErr			ScanPluginsFolder(FSRef * inPluginsRef);
		OSErr			ScanPluginsFolder(CFURLRef inPlugInsURL);
		
		OSErr			AddPluginToDictionary(CFBundleRef inBundleRef);
		OSErr			AddEntriesForPlugin(CRezillaPlugin * inRezPlugin);
		
		void 			StoreInPreferences();
		void 			RetrieveFromPreferences();
		void			AdjustDictionaryWithPrefs();
		CFMutableArrayRef	ReorderPluginsArray(CFArrayRef inPrefArray, CFMutableArrayRef inOldArray);

};


#endif
