// ===========================================================================
// CSnd_EditorDoc.cp
// 
//                       Created: 2004-12-07 07:22:47
//             Last modification: 2004-12-07 07:46:23
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

PP_Begin_Namespace_PowerPlant


#ifdef PowerPlant_PCH
	#include PowerPlant_PCH
#endif

#include "CSnd_EditorDoc.h"

#include "CRezObj.h"

#include "UDialogBoxHandler.h"
#include "UMessageDialogs.h"
#include "UMiscUtils.h"

#include <LDataStream.h>

#include <LString.h>
#include <PP_Messages.h>


// ---------------------------------------------------------------------------
//	¥ CSnd_EditorDoc							Constructor		  [public]
// ---------------------------------------------------------------------------

CSnd_EditorDoc::CSnd_EditorDoc(LCommander* inSuper, 
								 CRezMapTable* inSuperMap,
								 CRezObj* inRezObj,
								 ResType inSubstType,
								 Boolean inReadOnly)
 	: CEditorDoc(inSuper, inSuperMap, inRezObj, inSubstType, inReadOnly)
{
	Initialize();
}


// ---------------------------------------------------------------------------
//	¥ ~CSnd_EditorDoc							Destructor				  [public]
// ---------------------------------------------------------------------------

CSnd_EditorDoc::~CSnd_EditorDoc()
{
}


// ---------------------------------------------------------------------------
//	¥ Initialize													  [public]
// ---------------------------------------------------------------------------

void
CSnd_EditorDoc::Initialize()
{		
	if (mRezObj != nil) {
		Handle rezData = mRezObj->GetData();
		
		if (rezData != nil) {
			// Work with a copy of the handle
			::HandToHand(&rezData);
			Play(rezData);
			::DisposeHandle(rezData);
		} 
	} 
}


// ---------------------------------------------------------------------------
//	¥ Play														  [public]
// ---------------------------------------------------------------------------

void
CSnd_EditorDoc::Play(Handle inSoundH)
{
	StHandleLocker	lock(inSoundH);
	::SndPlay(NULL, (SndListHandle) inSoundH, false);
}



PP_End_Namespace_PowerPlant


