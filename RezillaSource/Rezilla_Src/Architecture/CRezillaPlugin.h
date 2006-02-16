// ===========================================================================
// CRezillaPlugin.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-02-16 12:04:01
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CRezillaPlugin
#define _H_CRezillaPlugin
#pragma once

#include "RezillaPluginInterface.h";

class CRezillaPlugin {

public:
				CRezillaPlugin(CFBundleRef inBundleRef);
				virtual ~CRezillaPlugin();

		void		GetPluginInfo();

		OSErr		Load();

		SInt32		CountEditTypes() { return mEditTypes.GetCount(); }
	
		TArray<OSType> *	GetEditTypes() { return &mEditTypes;}

		Boolean		IsSupported(ResType inType);
		
		Boolean		IsLoaded() {return mIsLoaded;}
	
		virtual SRezillaPluginInterface**	GetInterface() {return mInterface;}

protected:
		CFPlugInRef					mPluginRef;
		SRezillaPluginInterface **	mInterface;
		TArray<OSType>				mEditTypes;
		Boolean						mIsLoaded;		// differed loading
		UInt32  					mPluginVersion,
									mPluginType,
									mPluginCreator;
		Str255						mName;		

private:
		void		Initialize(CFBundleRef inBundleRef);

};


// ===========================================================================
//	Inline function definitions
// ===========================================================================

// ---------------------------------------------------------------------------
//	 IsSupported											 [inline] [public]
// ---------------------------------------------------------------------------

inline Boolean
CRezillaPlugin::IsSupported(ResType inType) { return mEditTypes.ContainsItem(inType); }


#endif
