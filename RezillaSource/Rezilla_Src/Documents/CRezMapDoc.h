// ===========================================================================
// CRezMapDoc.h				
// 
//                       Created: 2003-04-29 07:11:00
//             Last modification: 2005-05-14 10:23:45
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
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

class LWindow;
class CRezFile;
class CTextFileStream;
class CRezMap;
class CRezMapWindow;
class CRezObj;
class CRezType;
class CRezObjItem;
class CEditorDoc;

// ---------------------------------------------------------------------------

class CRezMapDoc : public LDocument, public LListener {
public:
						CRezMapDoc(LCommander* inSuper);
						CRezMapDoc(LCommander* inSuper, 
								   FSSpec* inFileSpec);
						CRezMapDoc(LCommander *inSuper,
								   FSSpec * inFileSpec,
								   SInt16 inFork, 
								   short inRefnum);
						CRezMapDoc(LCommander *inSuper, 
									CRezFile * inRezFile);

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

	virtual Boolean		UsesFileSpec( const FSSpec& inFileSpec ) const;

	virtual Boolean		IsModified();

	virtual void		SetModified( Boolean inModified );

	Boolean				CheckEditorsUnmodified(Boolean closeAll);
	
	virtual Boolean		HasSelection();
	
	Boolean				DesignateOutFile( FSSpec& outFileSpec, bool & outReplacing);

	Boolean				DesignateExportFile( FSSpec& outFileSpec, bool & outReplacing);

	virtual void		AttemptClose( Boolean inRecordIt );

	virtual Boolean		AskSaveAs(
								FSSpec			&outFSSpec,
								Boolean			inRecordIt);

	virtual Boolean		AskExportAs(
								FSSpec			&outFSSpec,
								Boolean			inRecordIt);

	virtual SInt16		AskSaveChanges( bool inQuitting );

	virtual bool		AskConfirmRevert();

	virtual void		DoAESave(
								FSSpec&			inFileSpec,
								OSType			inFileType);
	virtual void		DoSave();
	virtual void		DoRevert();
	
	virtual void		DoExport( FSSpec &inFileSpec);
	
	virtual Boolean		AllowSubRemoval( LCommander* inSub );

	TableIndexT			GetFirstSelected();
	
	// AppleEvents
	virtual void	GetAEProperty(
								DescType			inProperty,
								const AEDesc&		inRequestedType,
								AEDesc&				outPropertyDesc) const;
	
	void			SetAEProperty(
								DescType		inProperty,
								const AEDesc&	inValue,
								AEDesc&			outAEReply);

	static SInt32	GetAEPosition(const CRezMapDoc * inDoc);
	
	virtual void	HandleAppleEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
								SInt32				inAENumber);
									
	void			HandleExportEvent(
								const AppleEvent&	inAppleEvent,
								AppleEvent&			outAEReply,
								AEDesc&				outResult);

	virtual void		GetSubModelByPosition(
								DescType			inModelID,
								SInt32				inPosition,
								AEDesc&				outToken) const;

	virtual void		GetSubModelByName(
								DescType			inModelID,
								Str255				inName,
								AEDesc&				outToken) const;

	virtual bool	AEPropertyExists(
								DescType		inProperty) const;

	// Accessors
	CRezMapWindow*		GetRezMapWindow() const { return mRezMapWindow; }

	virtual CRezMap*	GetRezMap() { return mRezMap;}
	void				SetRezMap(CRezMap* theRezMap) {mRezMap = theRezMap ;}

	virtual short		GetRefnum();
	void				SetRefnum(short inRefnum);

	virtual SInt16		GetFork() { return mFork;}
	
	virtual CRezFile*	GetRezFile() { return mRezFile;}
	void				SetRezFile(CRezFile* theRezFile) {mRezFile = theRezFile ;}

	CRezType *			GetRezTypeAtIndex(SInt32 inPosition) const;
	CRezType *			GetRezTypeByName(Str255 inName)  const;
	CRezType *			GetRezTypeByType(ResType inType) const;
	
	SInt32				GetIndexForType(ResType inType) const;
	
	CRezObjItem *		CreateNewRes(ResType inType, short inID, Str255* inName, short inAttrs);
	CRezObj *			DuplicateResource(CRezObj* inRezObj);
	void				RemoveResource(CRezObjItem* inRezObjItem);
	void				PasteResource(ResType inType,
									  short inID,
									  Handle inHandle, 
									  Str255* inName, 
									  short inAttrs, 
									  Boolean replaceExisting);
	void				PasteRezMap(CRezMap * srcRezMap);

	CEditorDoc *		GetRezEditor(ResType inType, short inID);

	TArray<CEditorDoc *>*	GetOpenedEditors() { return mOpenedEditors ;}

	int					TryEdit(CRezObjItem * inRezObjItem, 
								CommandT inCommand, 
								ResType asType = 0);
	
	void				DoEdit(CRezObjItem * inRezObjItem, 
							   CommandT inCommand, 
							   ResType inType, 
							   ResType * substTypePtr);
		
	Boolean				IsReadOnly() { return mReadOnly;}
	void				SetReadOnly(Boolean inReadOnlyDoc) {mReadOnly = inReadOnlyDoc;}

	
	static TArray<CRezMapDoc*>& GetRezMapDocList()
							{
								return sRezMapDocList;
							}

protected:
	static TArray<CRezMapDoc*>	sRezMapDocList;

	SInt16					mFork;
	CRezMap *				mRezMap;
	CRezMapWindow *			mRezMapWindow;
	CRezFile *				mRezFile;
	CTextFileStream *		mExportStream;
	TArray<ResType>*		mTypesArray;	// Maintain a sorted array of ResTypes
	TArray<CEditorDoc *> *	mOpenedEditors;	// Maintain an array of editor docs 
	                 		                // depending from this doc (all edit 
	                 		                // windows for resources in this map)
	Boolean					mUpdateOnClose;
	Boolean					mReadOnly;
	SInt16					mExportFormat;
	
	void				NameNewDoc();
	CRezObjItem *		NewResDialog();
	void				UpdateRefNum(short newRefNum);
	void				WriteOutExport(SInt16 inExportFormat);
	
private:
	void				Initialize(FSSpec * inFileSpec, short inRefnum);
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
