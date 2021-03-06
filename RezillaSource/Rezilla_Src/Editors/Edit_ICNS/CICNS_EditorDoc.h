// ===========================================================================
// CICNS_EditorDoc.h				
// 
//                       Created: 2006-02-23 15:12:16
//             Last modification: 2006-11-10 06:50:06
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CICNS_EditorDoc
#define _H_CICNS_EditorDoc
#pragma once

#include "CEditorDoc.h"


#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CRezFile;
class CRezMapTable;
class CRezObj;
class CICNS_Family;
class CICNS_EditorWindow;
class CRezMapDoc;


class CICNS_EditorDoc : public CEditorDoc {
	
public:
						CICNS_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						virtual ~CICNS_EditorDoc();

	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual Boolean		ObeyCommand(
							CommandT	inCommand,
							void*		ioParam);

	virtual StringPtr	GetDescriptor( Str255 outDescriptor ) const;
	
#if PP_Uses_CFDescriptor
	virtual CFStringRef	CopyCFDescriptor () const;
#endif

	virtual Boolean		AllowSubRemoval( LCommander* inSub );
	
	void				Explode();
	void				Implode(CRezMapDoc * inRezMapDoc, short inID);
	
protected:
	CICNS_EditorWindow *		mIcnsEditWindow;
	IconRef						mIconRef;
	Boolean						mIconIsEmpty;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);

	virtual void		DoImportData(FSSpec inFileSpec);
	virtual void		DoExportData(FSSpec inFileSpec, SInt16 inFormat);
	
private:
	OSErr				RegisterIcon();
	OSErr				UnregisterIcon();
	void				Initialize();
};


PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
