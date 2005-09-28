// ===========================================================================
// CPluginsController.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-26 10:29:47
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CPluginsController
#define _H_CPluginsController
#pragma once


class CPluginsController {

public:
						CPluginsController();
				virtual	~CPluginsController();
		
		Boolean		HasPluginForType(ResType inType);
		OSErr		RegisterPlugin();
		void		UnregisterPlugin();
		void		LoadPlugin();

protected:
		static CFDictionaryRef	sPluginsDict;


private:
		OSErr		BuildPluginsDictionary();
		OSErr		ScanPluginsFolder(FSRef * inPluginsRef);
		OSErr		AddPluginToDictionary(CFBundleRef inBundleRef);
};


#endif
