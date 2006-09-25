// ===========================================================================
// CRezillaPlugin.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-03-08 13:05:17
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@sourceforge.users.fr>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CRezillaPlugin
#define _H_CRezillaPlugin
#pragma once

#include "RezillaPluginInterface.h"

class CRezMap;


class CRezillaPlugin {

public:
				CRezillaPlugin(CFBundleRef inBundleRef);
				virtual ~CRezillaPlugin();

		OSErr		Load();

		Boolean		IsSupported(ResType inType);
		
		CRezMap *	OpenResources();
		
		UInt8		CreateMenus(UInt8 inMenuCount, MenuID * inMenuIDs);

		virtual SPluginEditorInterface**	GetInterface() {return mInterface;}
		
		virtual CFPlugInRef	GetPluginRef() { return mPluginRef;}

		virtual short		GetRefnum() { return mRefNum;}
		
		UInt32				CountEditTypes() { return mEditTypes.GetCount(); }
	
		TArray<OSType> *	GetEditTypes() { return &mEditTypes;}
		TArray<LMenu*> *	GetMenusList() { return &mMenusList;}

		CFStringRef			GetName() { return mName;}
		UInt32				GetPluginType() { return mPluginType;}
		UInt32				GetPluginCreator() { return mPluginCreator;}
		UInt32				GetPluginVersion() { return mPluginVersion;}
		Boolean				IsLoaded() { return mIsLoaded;}

protected:
		CFPlugInRef					mPluginRef;
		short						mRefNum;
		SPluginEditorInterface **	mInterface;
		TArray<OSType>				mEditTypes;
		TArray<LMenu*>				mMenusList;
		Boolean						mMenusBuilt;
		Boolean						mIsLoaded;		// differed loading
		UInt32  					mPluginType,
									mPluginCreator,
									mPluginVersion;
		CFStringRef					mName;		

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
