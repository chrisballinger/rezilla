// ===========================================================================
// Rezilla_vers.r					
//                       Created: 2003-04-18 17:34:40
//             Last modification: 2004-05-07 07:07:48
// Author: Bernard Desgraupes
// e-mail: <bdesgraupes@users.sourceforge.net>
// www: <http://rezilla.sourceforge.net/>
// (c) Copyright: Bernard Desgraupes 2003-2004
// All rights reserved.
// ===========================================================================


//#include "MacTypes.r"
#include	<Carbon/Carbon.r>

#include "RezillaID.h"


#if	(REZILLA_STAGE == developStage)
#		define	REZILLA_STAGE_CODE	'd'
#elif	(REZILLA_STAGE == alphaStage)
#		define	REZILLA_STAGE_CODE	'a'
#elif	(REZILLA_STAGE == betaStage)
#	 	define	REZILLA_STAGE_CODE	'b'
#elif	(REZILLA_STAGE == finalStage)
#	 	define	REZILLA_STAGE_CODE	'f'
#endif

#define	REZILLA_MAJOR_BCD ((REZILLA_MAJOR / 10) * 16) + (REZILLA_MAJOR % 10)
#define	REZILLA_MINOR_BCD (REZILLA_MINOR * 16) + REZILLA_SUBMINOR


#if (REZILLA_SUBMINOR == 0)

#	if (REZILLA_STAGE == finalStage)
#		define	REZILLA_VERSION_STRING	\
			$$Format("%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, \
						REZILLA_STAGE_CODE)
#	else
#		if (REZILLA_DEVEL == 0)
#			define	REZILLA_VERSION_STRING	\
				$$Format("%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, \
						REZILLA_STAGE_CODE)
#		else
#			define	REZILLA_VERSION_STRING	\
				$$Format("%d.%d%c%d", REZILLA_MAJOR, REZILLA_MINOR, \
						REZILLA_STAGE_CODE, REZILLA_DEVEL)
#		endif

#	endif

#else

#	if (REZILLA_STAGE == finalStage)
#		define	REZILLA_VERSION_STRING	\
			$$Format("%d.%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, REZILLA_SUBMINOR,\
						REZILLA_STAGE_CODE)
#	else
#		if (REZILLA_DEVEL == 0)
#			define	REZILLA_VERSION_STRING	\
				$$Format("%d.%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, REZILLA_SUBMINOR,\
								REZILLA_STAGE_CODE)
#		else
#			define	REZILLA_VERSION_STRING	\
				$$Format("%d.%d.%d%c%d", REZILLA_MAJOR, REZILLA_MINOR, REZILLA_SUBMINOR,\
							REZILLA_STAGE_CODE, REZILLA_DEVEL)
#	endif

#	endif

#endif
			
			
resource 'vers' (1) {
	REZILLA_MAJOR_BCD,
	REZILLA_MINOR_BCD,
	REZILLA_STAGE,
	REZILLA_DEVEL,
	0,
	REZILLA_VERSION_STRING,
	$$Format("%s %s (c) %d by B. Desgraupes", 
					"Rezilla", REZILLA_VERSION_STRING, $$YEAR)
};

resource 'vers' (2) {
	REZILLA_MAJOR_BCD,
	REZILLA_MINOR_BCD,
	REZILLA_STAGE,
	REZILLA_DEVEL,
	0,
	REZILLA_VERSION_STRING,
	"Resource editor"
};

