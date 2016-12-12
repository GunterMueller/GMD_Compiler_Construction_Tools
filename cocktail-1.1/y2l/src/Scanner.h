# ifndef yyScanner
# define yyScanner

/* $Id: Scanner.h,v 2.6 1992/08/07 15:29:41 grosch rel $ */

# if defined __STDC__ | defined __cplusplus
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

/* line 7 "yacc.rex" */

# include "StringMem.h"
# include "Positions.h"
# include "Tables.h"

typedef struct	{ tPosition Position;
		     tStringRef		string;
		     int		number;
		     struct tCell *	action;
		} tScanAttribute;

extern void ErrorAttribute ();

 
# define EofToken	0
 
# ifdef lex_interface
#    define GetToken	yylex
#    define TokenLength	yyleng
# endif

extern	char *		TokenPtr	;
extern	short		TokenLength	;
extern	tScanAttribute	Attribute	;
extern	void		(* Scanner_Exit) ()	;
 
extern	void		BeginScanner	();
extern	void		BeginFile	ARGS ((char * yyFileName));
extern	int		GetToken	();
extern	int		GetWord		ARGS ((char * yyWord));
extern	int		GetLower	ARGS ((char * yyWord));
extern	int		GetUpper	ARGS ((char * yyWord));
extern	void		CloseFile	();
extern	void		CloseScanner	();

# endif
