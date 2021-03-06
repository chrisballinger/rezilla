// ===========================================================================
// CRezillaPlugin.h
// 
//                       Created: 2005-09-26 09:48:26
//             Last modification: 2006-11-25 07:31:00
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

#include <LModelObject.h>


class CRezMap;


class CRezillaPlugin : public LModelObject {

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

		// AppleEvents
		virtual void	MakeSelfSpecifier(
									AEDesc&			inSuperSpecifier,
									AEDesc&			outSelfSpecifier) const;

		virtual void	GetAEProperty(
									DescType		inProperty,
									const AEDesc&	inRequestedType,
									AEDesc&			outPropertyDesc) const;

		virtual bool	AEPropertyExists(
									DescType	inProperty) const;

		static SInt32	GetAEPosition(const CRezillaPlugin * inPlugin);
		
		// Accessors
		TArray<OSType> *	GetEditTypes() { return &mEditTypes;}
		TArray<LMenu*> *	GetMenusList() { return &mMenusList;}

		CFStringRef			GetName() { return mName;}
		UInt32				GetPluginType() { return mPluginType;}
		UInt32				GetPluginCreator() { return mPluginCreator;}
		UInt32				GetPluginVersion() { return mPluginVersion;}
		UInt32				GetPluginRole() { return mPluginRole;}
		Boolean				IsLoaded() { return mIsLoaded;}
		IconRef				GetIconRef() { return mIconRef;}

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
									mPluginVersion,
									mPluginRole;
		CFStringRef					mName;		
		IconRef						mIconRef;
		
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
