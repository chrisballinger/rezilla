// ===========================================================================
// CRezillaApp.cp					
//                       Created : 2003-04-18 17:34:40
//             Last modification : 2003-04-18 17:34:42
// Author : Bernard Desgraupes
// e-mail : <bdesgraupes@easyconnect.fr>
// www : <http://webperso.easyconnect.fr/bdesgraupes/>
// © Copyright : Bernard Desgraupes 2003
// All rights reserved.
// ===========================================================================


#include "MacTypes.r"

#define REZILLA_MAJOR 		0
#define REZILLA_MINOR		1
#define REZILLA_SUBMINOR	0
#define REZILLA_STAGE 		alphaStage
// developStage, alphaStage, betaStage, finalStage

#if	(REZILLA_STAGE == developStage)
#		define	REZILLA_STAGE_CODE	'd'
#elif	(REZILLA_STAGE == alphaStage)
#		define	REZILLA_STAGE_CODE	'a'
#elif	(REZILLA_STAGE == betaStage)
#	 	define	REZILLA_STAGE_CODE	'b'
#elif	(REZILLA_STAGE == finalStage)
#	 	define	REZILLA_STAGE_CODE	'f'
#endif

#define	REZILLA_MAJOR_BCD	((REZILLA_MAJOR / 10) * 16) + (REZILLA_MAJOR % 10)
#define	REZILLA_MINOR_BCD	(REZILLA_MINOR * 16) + REZILLA_SUBMINOR

#define	REZILLA_VERSION_STRING	\
			$$Format("%d.%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, REZILLA_SUBMINOR,\
						REZILLA_STAGE_CODE)

// #define	REZILLA_VERSION_STRING	\
// 			$$Format("%d.%d%c", REZILLA_MAJOR, REZILLA_MINOR, \
// 						REZILLA_STAGE_CODE)

resource 'vers' (1) {
	REZILLA_MAJOR_BCD,
	REZILLA_MINOR_BCD,
	REZILLA_STAGE,
	0x0,
	0,
	REZILLA_VERSION_STRING,
	$$Format("%s %s © %d by B. Desgraupes", 
					"Rezilla", REZILLA_VERSION_STRING, $$YEAR)
};

resource 'vers' (2) {
	REZILLA_MAJOR_BCD,
	REZILLA_MINOR_BCD,
	REZILLA_STAGE,
	0x0,
	0,
	REZILLA_VERSION_STRING,
	"Resource editor"
};

