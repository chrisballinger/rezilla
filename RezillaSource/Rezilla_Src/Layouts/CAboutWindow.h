// ===========================================================================
// CAboutWindow.h
// 
//                       Created: 2005-03-08 14:22:24
//             Last modification: 2005-03-08 15:23:56
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// (c) Copyright : Bernard Desgraupes, 2003-2005
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================

#pragma once

#include <LDialogBox.h>


class CAboutWindow : public LDialogBox {
public:
	enum { class_ID = FOUR_CHAR_CODE('AboW') };

							CAboutWindow();
							CAboutWindow( const SWindowInfo &inWindowInfo );
							CAboutWindow( ResIDT inWINDid,
								UInt32 inAttributes, LCommander *inSuperCommander );
							CAboutWindow( LStream *inStream );
							~CAboutWindow();
	
	virtual void		FindCommandStatus( CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName );

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);


protected:
	
	virtual void		FinishCreateSelf();

private:
	
};


