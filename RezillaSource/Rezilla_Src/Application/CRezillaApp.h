// ===========================================================================
// CRezillaApp.h					
//                       Created: 2003-04-16 22:13:54
//             Last modification: 2004-11-19 07:26:55
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
#include <UTextTraits.h>


//Used Internally to implement Open Dialog
typedef struct Rzil_OpenFileUD{
    UInt16		whichFork;
    Boolean		isReadOnly;
} Rzil_OpenFileUD;


typedef struct Rzil_basics{
	SInt32				charWidth;
	SInt32				charHeight;
} Rzil_basics;

class CInspectorWindow;
class CRezMapDoc;
class CRecentItemsMenu;
class CRezillaPrefs;
class CEditorsController;
class CTemplatesController;


class CRezillaApp : public LDocApplication, public LListener {
public:
						CRezillaApp();
	virtual 			~CRezillaApp();
	
	virtual Boolean		ObeyCommand(CommandT inCommand, void* ioParam);	
			
	virtual void		ListenToMessage( MessageT inMessage, void *ioParam);

	virtual Boolean		AttemptQuitSelf( SInt32	 inSaveOption );
	
	virtual void		FindCommandStatus(CommandT inCommand,
							Boolean &outEnabled, Boolean &outUsesMark,
							UInt16 &outMark, Str255 outName);

	virtual void		OpenDocument( FSSpec* inFSSpec );

	Boolean				ChooseAFile(FSSpec & fileSpec);

	Boolean				ChooseAFile(const LFileTypeList & inFileTypes, FSSpec & fileSpec);

	Boolean				DesignateNewMap( FSSpec& outFileSpec, bool & outReplacing);
	
	static OSErr		PreOpen(FSSpec & inFileSpec, 
								SInt16 & outFork, 
								short & outRefnum, 
								SInt16 inWantedFork = fork_anyfork, 
								Boolean askChangePerm = false);
	
	OSErr				OpenFork(FSSpec & inFileSpec, Boolean askChangePerm = false);
	
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
	static LStr255		VersionFromPlist();

	static SInt16		GetOwnRefNum() { return sOwnRefNum;}

	static CRezMapDoc*	FetchRezMapDoc(FSSpec *	inFileSpecPtr);
	
	static CRecentItemsMenu*	GetRecentItemsAttachment() { return sRecentItemsAttachment;}

	static CRezillaPrefs *			sPrefs;
	static CEditorsController *		sEditController;
	static CTemplatesController *	sTemplatesController;
	static Rzil_basics				sBasics;
	static const LStr255			sVersionNumber;
	static short					sOwnRefNum;
	static CInspectorWindow *		sInspectorWindow;
	static TArray<CRezMapDoc *>		sRezMapDocList;
	static CRecentItemsMenu *		sRecentItemsAttachment;
	static Boolean					sReadOnlyNavFlag;

protected:
	LDialogBox *		mAboutWindow;
	SInt16				mCreatingFork;
	SInt16				mOpeningFork;

	virtual void		StartUp();
	virtual void		Initialize();
	void				RegisterClasses();
	OSStatus			RegisterHelpBook();
	void				MakeAboutWindow();
	virtual void		DoPreferences();

private:
	void				InstallWindowMenu();
};


