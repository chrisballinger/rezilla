// ===========================================================================
// CRezFile.h					
// 
//                       Created: 2003-04-24 14:17:20
//             Last modification: 2003-04-25 05:28:39
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================
// A wrapper class for a Macintosh resource file ie a file storing its resources 
// either in the data fork or in the resource fork

#ifndef _H_CRezFile
#define _H_CRezFile
#pragma once

#include <PP_Prefix.h>

#include <Aliases.h>
#include <Script.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CRezMap;
class CRezMapTable;
class CRezMapDoc;

// ---------------------------------------------------------------------------

class CRezFile {
public:
		enum {
		  rezfile_undeffork = -1,
		  rezfile_rezfork = 1,
		  rezfile_datafork
		};

						CRezFile();
						CRezFile(const FSSpec& inFileSpec, short inRefnum, SInt16 inFork);
						CRezFile(const FSSpec& inFileSpec);
						CRezFile(AliasHandle inAlias,
								Boolean& outWasChanged,
								FSSpec* inFromFile = nil);
			virtual		~CRezFile();

	void				GetSpecifier( FSSpec& outFileSpec ) const;
	virtual void		SetSpecifier( const FSSpec& inFileSpec );
	bool				UsesSpecifier( const FSSpec& inFileSpec ) const;	
	bool				SpecifierExists() const;
	static bool			EqualFileSpec(
								const FSSpec &inFileSpecA,
								const FSSpec &inFileSpecB);

	
	virtual AliasHandle	MakeAlias( FSSpec* inFromFile = nil );

	virtual OSErr		CreateNewFile();

	virtual OSErr		OpenFile(SInt8 inPermissions);

	virtual OSErr		CloseFile();

	virtual Handle		ReadFile();

	virtual SInt32		WriteFile(const void* inBuffer,
								SInt32 inByteCount);

	OSErr				CopyFromRezMap(CRezMap * srcRezmap);

	virtual short		GetRefNum() { return mRefNum;}
	void				SetRefNum(short theRefNum) {mRefNum = theRefNum;}

	virtual CRezMapDoc*	GetOwnerDoc() { return mOwnerDoc;}
	void				SetOwnerDoc(CRezMapDoc* theOwnerDoc) {mOwnerDoc = theOwnerDoc ;}

	virtual SInt16		GetUsedFork() { return mUsedFork;}
	void				SetUsedFork(SInt16 theUsedFork) {mUsedFork = theUsedFork ;}

protected:
		CRezMapDoc *	mOwnerDoc;
		FSSpec			mFileSpec;
		FSRef			mFileRef;
		short			mRefNum;
		SInt16			mUsedFork;
		Boolean			mInChain;

private:			
					// Copy and Assignment not allowed
					CRezFile( const CRezFile& );
	CRezFile&		operator = ( const CRezFile& );
};

PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

