# ifndef yyScanner
# define yyScanner

/* $Id: Scanner.h,v 2.6 1992/08/07 15:29:41 grosch rel $ */

# if defined __STDC__ | defined __cplusplus
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

/* line 7 "lex.rex" */

# include <string.h>
# include "Memory.h"
# include "Positions.h"
# include "StringMem.h"
# include "StringBuf.h"

extern void print_startconds	();
extern void print_macrodefs	();
extern void print_local		();
extern void put_macro		();

typedef struct	{ tPosition Position;
		  char char_value;
		  char string_value [256];
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
