// ===========================================================================
// CRezMapDoc.h				
// 
//                       Created : 2003-04-29 07:11:00
//             Last modification : 2003-06-02 21:09:44
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003
// All rights reserved.
// ===========================================================================

#ifndef _H_CRezMapDoc
#define _H_CRezMapDoc
#pragma once

#include <LDocument.h>
#include <LListener.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class	LWindow;
class	CRezFile;
class	CRezMap;
class	CRezMapWindow;
class	CRezObj;
class	CRezObjItem;

// ---------------------------------------------------------------------------

class CRezMapDoc : public LDocument, public LListener {
public:
						CRezMapDoc(LCommander* inSuper, 
								   FSSpec* inFileSpec);
						CRezMapDoc(LCommander *inSuper,
								   FSSpec * inFileSpec,
								   SInt16 inFork, 
								   short inRefnum);
						CRezMapDoc(LCommander* inSuper);

						virtual ~CRezMapDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual Boolean		ObeyCommand(
							CommandT			inCommand,
							void*				ioParam = nil);	

	virtual void		ListenToMessage(
							MessageT		inMessage,
							void*			ioParam);

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;

// 	virtual Boolean		UsesFileSpec( const FSSpec& inFileSpec ) const;

	virtual Boolean		IsModified();
	virtual Boolean		HasSelection();
	
	Boolean				DesignateOutFile( FSSpec& outFileSpec, bool & outReplacing);

	virtual void		AttemptClose( Boolean inRecordIt );

	virtual Boolean		AskSaveAs(
								FSSpec			&outFSSpec,
								Boolean			inRecordIt);

	virtual SInt16		AskSaveChanges( bool inQuitting );

	virtual void		DoAESave( FSSpec &inFileSpec);
	virtual void		DoSave();
	
	virtual Boolean		AllowSubRemoval( LCommander* inSub );

	TableIndexT			GetFirstSelected();
	
	CRezMapWindow*		GetRezMapWindow() const { return mRezMapWindow; }

	virtual CRezMap*	GetRezMap() { return mRezMap;}
	void				SetRezMap(CRezMap* theRezMap) {mRezMap = theRezMap ;}

	virtual short		GetRefnum();
	void				SetRefnum(short inRefnum);

	virtual SInt16		GetFork() { return mFork;}
	
	virtual CRezFile*	GetRezFile() { return mRezFile;}
	void				SetRezFile(CRezFile* theRezFile) {mRezFile = theRezFile ;}

	void				CreateNewRes(ResType inType, short inID, Str255* inName, short inAttrs);
	void				DuplicateResource(CRezObj* inRezObj);
	void				RemoveResource(CRezObjItem* inRezObjItem);
	void				PasteResource(ResType inType,
									  short inID,
									  Handle inHandle, 
									  Str255* inName = nil, 
									  short inAttrs = 0);
	
protected:
	SInt16					mFork;
	CRezMap *				mRezMap;
	CRezMapWindow *			mRezMapWindow;
	CRezFile *				mRezFile;
	TArray<ResType>*		mTypesArray;	// Maintain a sorted array of ResTypes
	Boolean					mUpdateOnClose;
		
	void				NameNewDoc();
	void				NewResDialog();
	void				UpdateRefNum(short newRefNum);
	
private:
	void				Initialize(FSSpec * inFileSpec, short inRefnum);
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
