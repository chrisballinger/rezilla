// ===========================================================================
// NavServicesCallbacks.h					
//                       Created: 2003-05-07 15:58:27
//             Last modification: 2004-02-29 07:04:37
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@easyconnect.fr>
// www: <http://webperso.easyconnect.fr/bdesgraupes/>
// � Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// $Date$
// $Revision$
// ===========================================================================


pascal void		Rzil_NewMapNavEventFilterUPP(
							NavEventCallbackMessage inCBSelector,
							NavCBRecPtr inCBParams,
							void *ioCallBackUD);

pascal void		Rzil_OpenNavEventFilterUPP(
							NavEventCallbackMessage inCBSelector,
							NavCBRecPtr inCBParams,
							void *ioCallBackUD);

pascal void		Rzil_SaveAsNavEventFilterUPP(
							NavEventCallbackMessage inCBSelector,
							NavCBRecPtr inCBParams,
							void *ioCallBackUD);

pascal void		Rzil_ExportNavEventFilterUPP(
							NavEventCallbackMessage inCBSelector,
							NavCBRecPtr inCBParams,
							void *ioCallBackUD);

pascal Boolean	Rzil_NavObjectFilterUPP(
							AEDesc *theItem,
							void *theInfo,
							void *ioCallBackUD,
							NavFilterModes theFilterMode);

void			Rzil_NewMapHandleEvent(
							   NavCBRecPtr inCBParams, 
							   void * ioCallBackUD);

void			Rzil_OpenMapHandleEvent(
							   NavCBRecPtr inCBParams, 
							   void * ioCallBackUD);

void			Rzil_SaveMapHandleEvent(
							   NavCBRecPtr inCBParams, 
							   void * ioCallBackUD);

