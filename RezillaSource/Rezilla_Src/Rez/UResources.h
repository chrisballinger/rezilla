// ===========================================================================
// UResources.h					
// 
//                       Created: 2003-04-23 12:32:10
//             Last modification: 2003-05-02 08:27:08
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_UResources
#define _H_UResources
#pragma once

// -------------------------------------------------------------

struct SResourceObjInfo {
	ResType		type;
	SInt32		size;
	SInt32		id;
	Str255		name;
	ResType		iconid;
	Boolean		sysheap;
	Boolean		purge;
	Boolean		lock;
	Boolean		protect;
	Boolean		preload;
	Boolean		compress;
};

typedef struct SResourceObjInfo SResourceObjInfo;
typedef SResourceObjInfo* SResourceObjInfoPtr;


// -------------------------------------------------------------

class UResources {

public:
	static OSErr	GetCurrentResFile(short & outRefNum);

    static OSErr    UniqueID(ResType inType, short & outID);
		
	static OSErr	CountForType(ResType inType, short & outCount);
	static OSErr	CountAllTypes(short & outCount);
	static OSErr	CountAllResources(short & outCount);
		
	static OSErr	GetWithID(ResType inType, short inID, Handle & outHandle);
	static OSErr	GetWithName(ResType inType, ConstStr255Param inName, Handle & outHandle);
	static OSErr	GetAllTypes( TArray<ResType>* & outArray );

	static const SInt16	refNum_Undef = -1;

};


// ===========================================================================
//	¥ Stack-based classes
// ===========================================================================

// ---------------------------------------------------------------------------
//  ¥ class StRezReferenceSaver
// ---------------------------------------------------------------------------
class StRezReferenceSaver {
public:
						StRezReferenceSaver();
						StRezReferenceSaver( SInt16 inRefNum );
						~StRezReferenceSaver();

	void		SetRefNum( SInt16 inRefNum ) { mOriginalRefNum = inRefNum; }
	
	void		Restore();
	
private:
	SInt16	mOriginalRefNum;	// original value of RefNum

};


// ---------------------------------------------------------------------------
//  ¥ class StRezLoadSaver
// ---------------------------------------------------------------------------
class StRezLoadSaver {
public:
						StRezLoadSaver( Boolean inResLoad = false );
						~StRezLoadSaver();

	Boolean		mOriginalResLoad;			// original value of ResLoad
};




#endif

