// ===========================================================================
// CRezillaApp.h					
//                       Created : 2003-04-16 22:13:54
//             Last modification : 2003-04-12 14:28:53
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright : Bernard Desgraupes 2002, 2003
// All rights reserved.
// ===========================================================================


#pragma once

#include <LApplication.h>

class CInspectorWindow;


class	CRezillaApp : public LDocApplication, public LListener {
public:
						CRezillaApp();
	virtual 			~CRezillaApp();
	
	virtual Boolean		ObeyCommand(CommandT inCommand, void* ioParam);	
			
	virtual void		ListenToMessage( MessageT inMessage, void *ioParam);

	virtual void		FindCommandStatus(CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName);

	Boolean				ChooseAFile(FSSpec & fileSpec);
	Boolean				ChooseAFile(const LFileTypeList & inFileTypes, FSSpec & fileSpec);
	Boolean				PreOpen(FSSpec & inFileSpec, SInt16 & outFork, short & outRefnum);
	Boolean				DesignateNewMap( FSSpec& outFileSpec, bool & outReplacing);

	virtual void		ShowAboutBox();
	
	static LStr255		VersionFromResource();

	static SInt16		GetOwnRefNum() { return sOwnRefNum;}
// 	static void			SetOwnRefNum(SInt16 theCurrentRefNum) {sOwnRefNum = theCurrentRefNum ;}

	static const LStr255		sVersionNumber;
	static short				sOwnRefNum;
	static CInspectorWindow *	sInspectorWindow;

protected:
	LDialogBox *		mAboutWindow;
	SInt16				mOpeningFork;


	virtual void		StartUp();
	virtual void		Initialize();
	void				RegisterClasses();
	OSStatus			RegisterHelpBook();
	void				MakeAboutWindow();
// 	virtual void			DoPreferences();


private:
	void					InstallWindowMenu()	;
};


