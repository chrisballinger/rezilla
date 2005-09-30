// ===========================================================================
// CRezillaPlugin.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2005-09-27 10:22:26
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes, 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CRezillaPlugin
#define _H_CRezillaPlugin
#pragma once


class CRezillaPlugin {

public:
				CRezillaPlugin(CFBundleRef inBundleRef);
				virtual ~CRezillaPlugin();


// 		void		GetTypesList();
		void		GetPluginInfo();

		SInt32		CountEditTypes() { return mEditTypes.GetCount(); }
	
		TArray<OSType> *	GetEditTypes() { return &mEditTypes;}

		Boolean				IsSupported(ResType inType);
		
protected:
		TArray<OSType>	mEditTypes;
		Boolean			mIsLoaded;		// differed loading
		UInt32  		mPluginVersion;
		CFStringRef		mIdentifier;
		

private:
		void		Initialize(CFBundleRef inBundleRef);
		void		Load();


};
/* Property list keys:
 * CFBundleIdentifier
 * CFBundleSignature
 * CFBundleVersion
 * CFPlugInDynamicRegistration
 * CFPlugInFactories
 * CFPlugInTypes
 * CFPlugInUnloadFunction
 * CFPluginNameString
 * RezillaPluginEditTypes
 * RezillaPluginRole
 */


// ===========================================================================
//	Inline function definitions
// ===========================================================================

// ---------------------------------------------------------------------------
//	 IsSupported											 [inline] [public]
// ---------------------------------------------------------------------------

inline Boolean
CRezillaPlugin::IsSupported(ResType inType) { return mEditTypes.ContainsItem(inType); }


#endif
