// ===========================================================================
// CAete_EditorDoc.h
// 
//                       Created: 2004-07-01 08:42:37
//             Last modification: 2005-01-30 13:02:04
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CAete_EditorDoc
#define _H_CAete_EditorDoc
#pragma once


#include "CEditorDoc.h"


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

	virtual Boolean			ObeyCommand(
									CommandT	inCommand,
									void*		ioParam);

	virtual Boolean			AllowSubRemoval( LCommander* inSub );
	
	static Boolean			DesignateExportFile(FSSpec& outFileSpec, 
												Boolean & outReplacing, 
												SInt16 & outExportFormat);

	virtual StringPtr		GetDescriptor( Str255 outDescriptor ) const;

	CAete_EditorWindow*		GetAeteEditWindow() { return mAeteEditWindow;}
	
protected:
	CAete_EditorWindow *		mAeteEditWindow;
	CAeteStream *				mOutStream;
	
	virtual Handle		GetModifiedResource(Boolean &releaseIt);

private:
	void				Initialize();
	void				DoExport(FSSpec	&inFileSpec, SInt16 inFormat);

};



PP_End_Namespace_PowerPlant




#endif

