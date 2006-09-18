// ===========================================================================
// CAete_EditorDoc.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2006-09-17 12:16:31
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2004-2005, 2006
// All rights reserved.
// ===========================================================================

#ifndef _H_CAete_EditorDoc
#define _H_CAete_EditorDoc
#pragma once


#include "CEditorDoc.h"

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

class CAete_EditorWindow;
class CAeteStream;
class CTextFileStream;

class CAete_EditorDoc : public CEditorDoc {
public:
						CAete_EditorDoc(LCommander* inSuper,
										CRezMapTable* inSuperMap,
										CRezObj* inRezObj,
										ResType inSubstType,
										Boolean inReadOnly);
						
						virtual ~CAete_EditorDoc();

	virtual void			FindCommandStatus( CommandT inCommand,
									Boolean &outEnabled, Boolean &outUsesMark,
									UInt16 &outMark, Str255 outName );

	virtual Boolean			AllowSubRemoval( LCommander* inSub );
	
	virtual bool			DesignateExportFile(FSSpec& outFileSpec, 
												bool & outReplacing, 
												SInt16 & outExportFormat);

	virtual StringPtr		GetDescriptor( Str255 outDescriptor ) const;

	CAete_EditorWindow*		GetAeteEditWindow() { return mAeteEditWindow;}
	
protected:
	CAete_EditorWindow *		mAeteEditWindow;
	CAeteStream *				mOutStream;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);
	virtual void		DoImportData(FSSpec inFileSpec);
	virtual void		DoExportData(FSSpec inFileSpec, SInt16 inFormat);

private:
	void				Initialize();

};



PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif

