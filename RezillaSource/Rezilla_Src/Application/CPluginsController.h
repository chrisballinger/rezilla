// ===========================================================================
// CPluginsController.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-15 16:38:57
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CPluginsController
#define _H_CPluginsController
#pragma once

class CRezillaPlugin;


class CPluginsController {

public:
						CPluginsController();
				virtual	~CPluginsController();
		
		Boolean		HasPluginForType(ResType inType);
		OSErr		RegisterPlugin();
		void		UnregisterPlugin();
		void		LoadPlugin();

		static CFMutableDictionaryRef	sPluginsDict;
		
protected:
		static TArray<CRezillaPlugin*>	sPluginsList;


private:
		OSErr		BuildInternalPluginsDictionary();
		OSErr		BuildExternalPluginsDictionary();
		
		OSErr		ScanPluginsFolder(FSRef * inPluginsRef);
		OSErr		ScanPluginsFolder(CFURLRef inPlugInsURL);
		
		OSErr		AddPluginToDictionary(CFBundleRef inBundleRef);
		OSErr		AddDictEntriesForPlugin(CRezillaPlugin * inRezPlugin);
		
};


#endif
