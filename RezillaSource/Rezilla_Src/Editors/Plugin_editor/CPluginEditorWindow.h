// ===========================================================================
// CPluginEditorWindow.h				
// 
//                       Created: 2005-10-02 08:41:52
//             Last modification: 2006-10-03 15:05:35
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright : Bernard Desgraupes, 2005-2006
// All rights reserved.
// ===========================================================================

#pragma once

#include "CEditorWindow.h"
#include "RezillaPluginInterface.h"

#include <LPeriodical.h>

class CPluginEditorDoc;
class CPluginEditorView;


class CPluginEditorWindow : public CEditorWindow,
							public LPeriodical {
public:
	enum { class_ID = FOUR_CHAR_CODE('PluW') };

							CPluginEditorWindow();
							CPluginEditorWindow(
									WindowPtr		inMacWindow,
									LCommander*		inSuperCommander);
							CPluginEditorWindow( LStream *inStream );
							~CPluginEditorWindow();

	static pascal OSStatus WindowEventHandler(EventHandlerCallRef myHandler, 
											  EventRef event, 
											  void *userData);
							
	virtual Boolean	ObeyCommand(
							CommandT			inCommand,
							void*				ioParam);

	virtual void	ListenToMessage( MessageT inMessage,void *ioParam);

	virtual Boolean	HandleKeyPress( const EventRecord& 	inKeyEvent );

	virtual void	Click( SMouseDownEvent& inMouseDown );
						
	virtual void	Refresh();

	virtual void	FinalizeEditor(CEditorDoc* inEditorDoc, void * ioParam = NULL);

	void			CreateControls(SInt32 inPlugAttrs);
	
	virtual void	RevertContents();
	
	virtual	void	SpendTime( const EventRecord& inMacEvent );

	void			GetContentsRect(Rect &outRect) const;
	
	void			ResizeWindowBy(
							SInt16	inWidthDelta,
							SInt16	inHeightDelta);
	
	RezPlugRef		GetPlugRef() { return mPlugRef;}
	void			SetPlugRef(RezPlugRef inPlugRef) {mPlugRef = inPlugRef;}
	
protected:
		SPluginEditorInterface**	mInterface;
		RezPlugRef					mPlugRef;
		ControlRef					mHeaderRef,
									mNameRef,
									mFooterRef,
									mSaveRef,
									mCancelRef,
									mRevertRef;

	virtual void		PutOnDuty(LCommander *inNewTarget);
	virtual void		TakeOffDuty();
	void				RemovePluginMenus();
	Boolean				IsPluginMenu(ResIDT inMenuID);
	void				AdaptControlsToWindowBounds();
	void				HandleMenuItem(MenuRef inMenuRef, MenuItemIndex inMenuItemIndex);
	
};


