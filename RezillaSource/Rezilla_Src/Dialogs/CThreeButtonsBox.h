// ===========================================================================
// File: "CThreeButtonsBox.h"
//                        Created: 2005-03-09 05:43:35
//              Last modification: 2005-03-09 05:43:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright: Bernard Desgraupes 2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#ifndef _H_CThreeButtonsBox
#define _H_CThreeButtonsBox
#pragma once

#include <LWindow.h>
#include <LListener.h>

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

class	CThreeButtonsBox : public LWindow,
					 public LListener {
public:
	enum { class_ID = FOUR_CHAR_CODE('TBBx') };

						CThreeButtonsBox();

						CThreeButtonsBox( const SWindowInfo& inWindowInfo );

						CThreeButtonsBox(
								ResIDT			inWINDid,
								UInt32			inAttributes,
								LCommander*		inSuperCommander);

						CThreeButtonsBox(
								LCommander*		inSuperCommander,
								const Rect&		inGlobalBounds,
								ConstStringPtr	inTitle,
								SInt16			inProcID,
								UInt32			inAttributes,
								WindowPtr		inBehind,
								PaneIDT			inDefaultButtonID = PaneIDT_Undefined,
								PaneIDT			inCancelButtonID = PaneIDT_Undefined,
								PaneIDT			inDontButtonID = PaneIDT_Undefined);

						CThreeButtonsBox( LStream* inStream );

	virtual				~CThreeButtonsBox();

	virtual void		SetDefaultButton( PaneIDT inButtonID );

	virtual void		SetCancelButton( PaneIDT inButtonID );

	virtual void		SetDontButton( PaneIDT inButtonID );

	virtual Boolean		HandleKeyPress( const EventRecord& inKeyEvent );

	virtual void		ListenToMessage(
								MessageT		inMessage,
								void*			ioParam);

protected:
	virtual void		FinishCreateSelf();
	
	virtual void		SetDefaultTag(
								PaneIDT			inButtonID,
								Boolean			inBeDefault);
	
	virtual void		SetCancelTag(
								PaneIDT			inButtonID,
								Boolean			inBeDefault);
								
protected:
	PaneIDT				mDefaultButtonID;
	PaneIDT				mCancelButtonID;
	PaneIDT				mDontButtonID;
};

// ---------------------------------------------------------------------------
//	Structure passed as the parameter to ProcessCommand when relaying
//	Messages as Commands

struct SThreeButtonsResponse {
	CThreeButtonsBox*		dialogBox;
	void*					messageParam;
};
// ---------------------------------------------------------------------------




PP_End_Namespace_PowerPlant


#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
