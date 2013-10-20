// ===========================================================================
// UNavigationDialogs.h					
//                       Created: 2003-05-15 10:35:40
//             Last modification: 2003-05-15 10:36:54
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003
// All rights reserved.
// ===========================================================================
// Modified PowerPlant's UNavServicesDialogs to allow for customization of 
// the EventUpp and the user data. Class CNavFileChooser replaces LFileChooser.


#ifndef _H_CNavFileChooser
#define _H_CNavFileChooser
#pragma once

#include <PP_Prefix.h>
#include <LFileTypeList.h>
#include <UAppleEventsMgr.h>
#ifndef __MACH__
#include <Navigation.h>
#endif

#if PP_Uses_Pragma_Import
	#pragma import on
#endif

PP_Begin_Namespace_PowerPlant

// ---------------------------------------------------------------------------

namespace UNavigationDialogs {
	// -----------------------------------------------------------------------
	//	Wrapper class for a NavReplyRecord

	class	StNavReplyRecord {
		public:
								StNavReplyRecord();
								~StNavReplyRecord();

			void				SetDefaultValues();

			operator NavReplyRecord*()		{ return &mNavReply; }

			NavReplyRecord&		Get()		{ return mNavReply; }

			bool				IsValid() const
											{ return mNavReply.validRecord; }

			bool				IsReplacing() const
											{ return mNavReply.replacing; }

			bool				IsStationery() const
											{ return mNavReply.isStationery; }

			AEDescList			Selection()	const
											{ return mNavReply.selection; }

			ScriptCode			KeyScript()	const
											{ return mNavReply.keyScript; }

			void				GetFileSpec(
										FSSpec&		outFileSpec) const;

		protected:
			NavReplyRecord		mNavReply;

		private:					// Unimplemented to prevent copying
								StNavReplyRecord(
										const StNavReplyRecord&);
			StNavReplyRecord&	operator = (
										const StNavReplyRecord&);
	};


	// -----------------------------------------------------------------------

	#include <UStandardDialogs.i>

	// -----------------------------------------------------------------------

	class CNavFileChooser{
		public:
						CNavFileChooser();

						~CNavFileChooser();

	NavDialogOptions*	GetDialogOptions();

	void				SetDefaultLocation(
								const FSSpec&			inFileSpec,
								bool					inSelectIt);

	void				SetOptionFlags(
							  NavDialogOptionFlags inFlags);

	void				SetPopupExtension(
							  NavMenuItemSpecArrayHandle inPopupExtension);

	void				SetUserData(
							  void * 					inDataPtr);

	void				SetEventFilterProc(
								NavEventProcPtr			inFilterProc);

	void				SetObjectFilterProc(
								NavObjectFilterProcPtr	inFilterProc);

	void				SetPreviewProc(
								NavPreviewProcPtr		inPreviewProc);

	bool				AskOpenFile(
								const LFileTypeList&	inFileTypes);

	bool				AskChooseOneFile(
								const LFileTypeList&	inFileTypes,
								FSSpec					&outFileSpec);

	bool				AskChooseFolder(
								FSSpec&					outFileSpec,
								SInt32&					outFolderDirID);

	bool				AskChooseVolume(
								FSSpec&					outFileSpec);

	bool				IsValid() const;

	SInt32				GetNumberOfFiles() const;

	void				GetFileSpec(
								SInt32		inIndex,
								FSSpec&		outFileSpec) const;

	void				GetFileDescList(
								AEDescList&	outDescList) const;

	ScriptCode			GetScriptCode() const;

		protected:
			StNavReplyRecord		mNavReply;
			NavDialogOptions		mNavOptions;
			NavEventProcPtr			mNavEventProc;
			NavObjectFilterProcPtr	mNavFilterProc;
			NavPreviewProcPtr		mNavPreviewProc;
			StAEDescriptor			mDefaultLocation;
			bool					mSelectDefault;
			void * 					mUserData;
		
	};

// struct NavDialogOptions {
//    UInt16 version;
//    NavDialogOptionFlags dialogOptionFlags;
//    Point location;
//    Str255 clientName;
//    Str255 windowTitle;
//    Str255 actionButtonLabel;
//    Str255 cancelButtonLabel;
//    Str255 savedFileName;
//    Str255 message;
//    UInt32 preferenceKey;
//    NavMenuItemSpecArrayHandle popupExtension;
//    char reserved[494];
// };
	// -----------------------------------------------------------------------

	class	CNavFileDesignator {
		public:
						CNavFileDesignator();

						~CNavFileDesignator();

	void				SetFileType(
								OSType				inFileType);

	void				SetFileCreator(
								OSType				inFileCreator);

	NavDialogOptions*	GetDialogOptions();

	void				SetDefaultLocation(
								const FSSpec&		inFileSpec,
								bool				inSelectIt);

	void				SetOptionFlags(
							  NavDialogOptionFlags inFlags);

	void				SetClientName(Str255 inName);
	Str255 *			GetClientName();
	
	void				SetSavedFileName(Str255 inName);
	Str255 *			GetSavedFileName();
	
	void				SetMessage(Str255 inNessage);

	void				SetPopupExtension(
							  NavMenuItemSpecArrayHandle inPopupExtension);

	void				SetUserData(
							  void * 					inDataPtr);

	void				SetEventFilterProc(
								NavEventProcPtr			inFilterProc);

	bool				AskDesignateFile();

	bool				IsValid() const;

	void				GetFileSpec(
								FSSpec&				outFileSpec) const;

	bool				IsReplacing() const;

	bool				IsStationery() const;

	ScriptCode			GetScriptCode() const;

	void				CompleteSave(
								NavTranslationOptions	inOption = kNavTranslateInPlace);

		protected:
			StNavReplyRecord	mNavReply;
			NavDialogOptions	mNavOptions;
			NavEventProcPtr		mNavEventProc;
			OSType				mFileType;
			OSType				mFileCreator;
			StAEDescriptor		mDefaultLocation;
			bool				mSelectDefault;
			void * 				mUserData;
	};

	// -----------------------------------------------------------------------
	//	Event filter callback function

	pascal void	NavigationEventProc(
						NavEventCallbackMessage		inSelector,
						NavCBRecPtr					ioParams,
						NavCallBackUserData			ioUserData);

	class	StNavEventUPP {
		public:
			StNavEventUPP( NavEventProcPtr inProcPtr );
			~StNavEventUPP();

			operator NavEventUPP()		{ return mNavEventUPP; }

		protected:
			NavEventUPP		mNavEventUPP;
	};

	// -----------------------------------------------------------------------
	//	Object Filter UPP

	class	StNavObjectFilterUPP {
		public:
			StNavObjectFilterUPP( NavObjectFilterProcPtr inProcPtr );
			~StNavObjectFilterUPP();

			operator NavObjectFilterUPP()	{ return mNavObjectFilterUPP; }

		protected:
			NavObjectFilterUPP	mNavObjectFilterUPP;
	};

	// -----------------------------------------------------------------------
	//	Preview UPP

	class	StNavPreviewUPP {
		public:
			StNavPreviewUPP( NavPreviewProcPtr inProcPtr );
			~StNavPreviewUPP();

			operator NavPreviewUPP()		{ return mNavPreviewUPP; }

		protected:
			NavPreviewUPP		mNavPreviewUPP;
	};
}

PP_End_Namespace_PowerPlant

#if PP_Uses_Pragma_Import
	#pragma import reset
#endif

#endif
