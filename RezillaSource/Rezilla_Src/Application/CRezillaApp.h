// ===========================================================================
// CRezillaApp.h					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2004-02-29 22:58:46
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright: Bernard Desgraupes 2002-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


#pragma once
#include "RezillaConstants.h"

#include <LApplication.h>


//Used Internally to implement Standard File System Open Dialog
//the hook data is used to set the default location
typedef struct Rzil_OpenFileUD{
    UInt16		whichFork;
    Boolean		isReadOnly;
} Rzil_OpenFileUD;

class CInspectorWindow;
class CRezMapDoc;


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
	Boolean				DesignateNewMap( FSSpec& outFileSpec, bool & outReplacing);
	static OSErr		PreOpen(FSSpec & inFileSpec, 
								SInt16 & outFork, 
								short & outRefnum, 
								SInt16 inWantedFork = fork_anyfork);
	OSErr				OpenFork(FSSpec & inFileSpec);
	static void			ReportOpenForkError(OSErr inError, FSSpec * inFileSpecPtr);

	virtual void		ShowAboutBox();
	
	
	virtual void		HandleAppleEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult,
								SInt32				inAENumber);
									
	virtual void		HandleOpenDocsEvent(
								const AppleEvent	&inAppleEvent,
								AppleEvent			&outAEReply,
								AEDesc				&outResult);
									
	static LStr255		VersionFromResource();

	static SInt16		GetOwnRefNum() { return sOwnRefNum;}
// 	static void			SetOwnRefNum(SInt16 theCurrentRefNum) {sOwnRefNum = theCurrentRefNum ;}

	static CRezMapDoc*	FetchRezMapDoc(FSSpec *	inFileSpecPtr);

	static const LStr255		sVersionNumber;
	static short				sOwnRefNum;
	static CInspectorWindow *	sInspectorWindow;
	static TArray<CRezMapDoc *>	sRezMapDocList;
	static SInt16				sDefaultCreatingFork;

protected:
	LDialogBox *		mAboutWindow;
	SInt16				mCreatingFork;
	SInt16				mOpeningFork;
	Boolean				mIsReadOnly;


	virtual void		StartUp();
	virtual void		Initialize();
	void				RegisterClasses();
	OSStatus			RegisterHelpBook();
	void				MakeAboutWindow();
// 	virtual void			DoPreferences();


private:
	void				InstallWindowMenu()	;
	
};



