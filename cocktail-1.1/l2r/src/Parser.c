/* $Id: Parser.c,v 2.9 1992/08/07 15:28:42 grosch rel grosch $ */

# define bool		char
# define true		1
# define false		0

# include "Parser.h"

# ifdef __cplusplus
extern "C" {
#    include "Memory.h"
#    include "DynArray.h"
#    include "Sets.h"
#    include "Errors.h"
#    include <string.h>
#    ifndef BCOPY
#       include <memory.h>
#    endif
}
# else
#    include "Memory.h"
#    include "DynArray.h"
#    include "Sets.h"
#    include "Errors.h"
#    ifndef BCOPY
#       include <memory.h>
#    endif
# endif

# if defined __STDC__ | defined __cplusplus
# define ARGS(parameters)	parameters
# else
# define ARGS(parameters)	()
# endif

# ifdef lex_interface
#    define GetToken	yylex
     extern int yylex ();
#    ifndef AttributeDef
#	include "Positions.h"
        typedef struct { tPosition Position; } tScanAttribute;
        static	tScanAttribute	Attribute = {{ 0, 0 }};
#    endif
#    ifndef ErrorAttributeDef
#	define ErrorAttribute(Token, RepairAttribute)
#    endif
#    ifndef yyGetAttribute
#	define yyGetAttribute(yyAttrStackPtr, Attribute) * yyAttrStackPtr = yylval
#    endif
# else
#    include "Scanner.h"
#    ifndef yyGetAttribute
#	define yyGetAttribute(yyAttrStackPtr, Attribute) (yyAttrStackPtr)->Scan = Attribute
#    endif
# endif

/* line 58 "/tmp/lalr24773" */
/* line 62 "lex.lalr" */


#include <stdio.h>

typedef struct { tScanAttribute Scan; } tParsAttribute;

static int in_defs = 1;	/* parsing definition part 			*/
static char macro [256];/* regular expression for macro definition	*/
static int  m;		/* index for macro				*/
static int level = 0;	/* level count to decide on meaning of $	*/

/* output representation for character, see print_char			*/
static char how_to_print [] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 'b', 't', 'n', 0, 'f', 'r', 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 2, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 2, 2, 2,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 1, 0 };

/* in definition part, append v to macro, otherwise copy to buffer	*/
static void str_put (v)
   char * v;
{
  if (in_defs) {
    while (macro [m++] = *v++);
    m--;
  }
  else BufString (v);
}

/* print one character, escape if necessary				*/
static void print_char (c)
   char c;
{
  char i;
  char v [8];

  i = how_to_print [c];
  switch (i) {
    case 0	: (void) sprintf (v, "\\%d", c); break;
    case 1	: (void) sprintf (v,   "%c", c); break;
    case 2	: (void) sprintf (v, "\\%c", c); break;
    default	: (void) sprintf (v, "\\%c", i); break;
  }
  str_put (v);
}

/* print the default rules for lex compatibility			*/
default_rules ()
{
  str_put ("\" \"	:- { yyEcho; }\n");
  str_put ("\\t	:- { yyTab; yyEcho; }\n");
  str_put ("\\n	:- { yyEol (0); yyEcho; }\n");
}


# if defined lex_interface & ! defined yylvalDef
     tParsAttribute yylval;
# endif

# ifndef yyInitStackSize
#    define yyInitStackSize	100
# endif
# define yyNoState		0

# define yyFirstTerminal	0
# define yyLastTerminal		26
# define yyTableMax		194
# define yyNTableMax		103
# define yyFirstReadState	1
# define yyLastReadState	34
# define yyFirstReadTermState	35
# define yyLastReadTermState	56
# define yyLastReadNontermState	72
# define yyFirstReduceState	73
# define yyLastReduceState	135
# define yyStartState		1
# define yyStopState		73

# define yyFirstFinalState	yyFirstReadTermState

typedef unsigned short	yyStateRange	;
typedef unsigned short	yySymbolRange	;
typedef struct	{ yyStateRange Check, Next; } yyTCombType ;

	char *		Parser_TokenName	[yyLastTerminal + 2] = {
"_EndOfFile",
"%%",
0,
0,
"STARTDEF",
"%t",
"/",
".",
"?",
"+",
"*",
"(",
")",
"|",
"ACTION",
"STARTCOND",
"REPEAT",
"EXPANSION",
"^",
"PSEUDOACTION",
"STRING",
"CHARCLASS",
"CHAR",
"MACRODEF",
"TRANSLATION",
"\\n",
"$",
""
};
static	yyTCombType	yyTComb		[yyTableMax + 1] = {
{27, 73},
{1, 80},
{2, 3},
{0, 0},
{1, 80},
{1, 80},
{5, 77},
{5, 77},
{6, 75},
{6, 35},
{0, 0},
{0, 0},
{0, 0},
{3, 78},
{3, 78},
{10, 39},
{16, 47},
{16, 17},
{28, 79},
{0, 0},
{3, 78},
{28, 52},
{28, 29},
{1, 80},
{3, 78},
{1, 80},
{8, 37},
{3, 78},
{3, 78},
{11, 129},
{3, 78},
{3, 78},
{3, 78},
{3, 78},
{3, 78},
{3, 78},
{4, 92},
{4, 92},
{3, 78},
{3, 78},
{28, 55},
{9, 132},
{28, 86},
{4, 92},
{29, 87},
{31, 54},
{9, 38},
{4, 92},
{30, 53},
{32, 56},
{4, 92},
{4, 92},
{9, 131},
{4, 92},
{4, 92},
{4, 92},
{4, 92},
{4, 92},
{4, 92},
{7, 91},
{7, 91},
{4, 92},
{4, 92},
{29, 87},
{24, 104},
{0, 0},
{7, 101},
{30, 31},
{0, 0},
{24, 104},
{7, 101},
{34, 17},
{0, 0},
{7, 96},
{7, 36},
{24, 104},
{7, 101},
{7, 101},
{7, 96},
{7, 101},
{7, 101},
{7, 101},
{12, 103},
{34, 83},
{7, 96},
{7, 101},
{12, 103},
{0, 0},
{0, 0},
{0, 0},
{14, 128},
{0, 0},
{12, 103},
{12, 40},
{14, 128},
{12, 103},
{12, 103},
{12, 103},
{17, 110},
{0, 0},
{14, 128},
{12, 103},
{17, 110},
{14, 128},
{14, 128},
{14, 128},
{0, 0},
{0, 0},
{17, 110},
{14, 128},
{0, 0},
{17, 110},
{17, 110},
{17, 110},
{19, 114},
{0, 0},
{0, 0},
{17, 110},
{0, 0},
{0, 0},
{19, 114},
{19, 114},
{19, 114},
{0, 0},
{19, 48},
{0, 0},
{0, 0},
{19, 114},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{19, 114},
{20, 120},
{20, 120},
{20, 49},
{20, 50},
{20, 51},
{20, 120},
{20, 120},
{20, 120},
{20, 120},
{0, 0},
{20, 120},
{20, 120},
{0, 0},
{20, 120},
{20, 120},
{20, 120},
{20, 120},
{21, 22},
{22, 105},
{20, 120},
{20, 120},
{0, 0},
{22, 105},
{0, 0},
{21, 25},
{21, 98},
{0, 0},
{0, 0},
{22, 105},
{0, 0},
{21, 98},
{22, 105},
{22, 105},
{22, 105},
{25, 107},
{0, 0},
{21, 98},
{22, 105},
{25, 107},
{0, 0},
{0, 0},
{33, 41},
{0, 0},
{0, 0},
{25, 107},
{33, 14},
{0, 0},
{25, 107},
{25, 107},
{25, 107},
{0, 0},
{33, 42},
{0, 0},
{25, 107},
{33, 43},
{33, 44},
{33, 45},
{0, 0},
{0, 0},
{0, 0},
{33, 46},
};
static	unsigned short	yyNComb		[yyNTableMax - yyLastTerminal] = {
2,
4,
5,
6,
57,
27,
28,
72,
32,
33,
0,
30,
71,
7,
58,
8,
9,
59,
12,
13,
21,
16,
68,
69,
23,
70,
18,
19,
26,
65,
20,
15,
10,
11,
61,
60,
66,
24,
19,
0,
65,
20,
62,
0,
19,
0,
65,
20,
63,
64,
20,
34,
66,
0,
19,
0,
65,
20,
67,
0,
19,
0,
65,
20,
0,
0,
66,
0,
19,
0,
65,
20,
0,
0,
0,
0,
0,
};
static	yyTCombType *	yyTBasePtr	[yyLastReadState + 1] = {
& yyTComb [0],
& yyTComb [0],
& yyTComb [1],
& yyTComb [13],
& yyTComb [36],
& yyTComb [6],
& yyTComb [8],
& yyTComb [59],
& yyTComb [1],
& yyTComb [27],
& yyTComb [1],
& yyTComb [4],
& yyTComb [75],
& yyTComb [0],
& yyTComb [83],
& yyTComb [0],
& yyTComb [4],
& yyTComb [91],
& yyTComb [0],
& yyTComb [108],
& yyTComb [128],
& yyTComb [145],
& yyTComb [145],
& yyTComb [0],
& yyTComb [50],
& yyTComb [161],
& yyTComb [0],
& yyTComb [0],
& yyTComb [17],
& yyTComb [39],
& yyTComb [43],
& yyTComb [20],
& yyTComb [24],
& yyTComb [168],
& yyTComb [58],
};
static	unsigned short*	yyNBasePtr	[yyLastReadState + 1] = {
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-26],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-16],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-10],
& yyNComb [-7],
& yyNComb [-27],
& yyNComb [-26],
& yyNComb [-26],
& yyNComb [0],
& yyNComb [-27],
& yyNComb [-23],
& yyNComb [6],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [-27],
& yyNComb [14],
& yyNComb [-27],
};
static	unsigned short	yyDefault	[yyLastReadState + 1] = {
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
10,
0,
33,
0,
33,
0,
0,
33,
33,
0,
0,
0,
33,
34,
0,
33,
0,
0,
0,
0,
0,
0,
0,
0,
};
static	unsigned char	yyLength	[yyLastReduceState - yyFirstReduceState + 1] = {
2,
6,
0,
1,
0,
0,
1,
0,
2,
2,
2,
1,
3,
0,
0,
2,
2,
1,
1,
0,
2,
2,
2,
0,
4,
0,
1,
1,
0,
1,
0,
3,
0,
4,
0,
1,
4,
0,
1,
2,
1,
0,
2,
1,
2,
2,
2,
1,
4,
1,
1,
1,
1,
1,
1,
0,
2,
1,
0,
0,
2,
1,
1,
};
static	yySymbolRange	yyLeftHandSide	[yyLastReduceState - yyFirstReduceState + 1] = {
62,
32,
31,
31,
30,
28,
27,
33,
33,
34,
35,
35,
35,
35,
38,
38,
39,
36,
29,
40,
40,
41,
42,
43,
43,
48,
48,
45,
45,
46,
46,
49,
50,
47,
51,
47,
37,
53,
37,
52,
55,
55,
54,
54,
56,
56,
56,
56,
57,
57,
57,
57,
57,
57,
57,
58,
44,
44,
44,
59,
60,
60,
61,
};
static	yySymbolRange	yyContinuation	[yyLastReadState + 1] = {
0,
1,
1,
0,
0,
0,
0,
0,
25,
25,
14,
25,
7,
17,
7,
17,
12,
7,
17,
6,
6,
14,
7,
17,
14,
7,
17,
0,
1,
5,
5,
25,
25,
17,
25,
};
static	unsigned short	yyFinalToProd	[yyLastReadNontermState - yyFirstReadTermState + 1] = {
76,
100,
94,
130,
135,
102,
124,
122,
125,
123,
126,
127,
121,
113,
117,
119,
118,
84,
85,
89,
90,
82,
74,
93,
95,
133,
134,
109,
112,
115,
116,
111,
106,
97,
99,
108,
88,
81,
};

static	void	yyErrorRecovery		ARGS((yySymbolRange * yyTerminal, yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr));
static	void	yyComputeContinuation	ARGS((yyStateRange * yyStack, unsigned long yyStackSize, short yyStackPtr, tSet * yyContinueSet));
static	bool	yyIsContinuation	ARGS((yySymbolRange yyTerminal, yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr));
static	void	yyComputeRestartPoints	ARGS((yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr, tSet * yyRestartSet));
static	yyStateRange yyNext		ARGS((yyStateRange yyState, yySymbolRange yySymbol));
static	void	BeginParser		();

int Parser ()
   {
      register	yyStateRange	yyState		;
      register	long		yyTerminal	;
      register	yyStateRange *	yyStateStackPtr ;
      register	tParsAttribute *yyAttrStackPtr	;
      register	bool		yyIsRepairing	;
		unsigned long	yyStateStackSize= yyInitStackSize;
		unsigned long	yyAttrStackSize = yyInitStackSize;
		yyStateRange *	yyStateStack	;
		tParsAttribute* yyAttributeStack;
		tParsAttribute	yySynAttribute	;	/* synthesized attribute */
      register	yyStateRange *	yyEndOfStack	;
		int		yyErrorCount	= 0;
   


      BeginParser ();
      yyState		= yyStartState;
      yyTerminal	= GetToken ();
      MakeArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));
      MakeArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));
      yyEndOfStack	= & yyStateStack [yyStateStackSize];
      yyStateStackPtr	= yyStateStack;
      yyAttrStackPtr	= yyAttributeStack;
      yyIsRepairing	= false;

   ParseLoop:
      for (;;) {
	 if (yyStateStackPtr >= yyEndOfStack) {
	    int yyyStateStackPtr= yyStateStackPtr - yyStateStack;
	    int yyyAttrStackPtr	= yyAttrStackPtr - yyAttributeStack;
	    ExtendArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));
	    ExtendArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));
	    yyStateStackPtr	= yyStateStack + yyyStateStackPtr;
	    yyAttrStackPtr	= yyAttributeStack + yyyAttrStackPtr;
	    yyEndOfStack	= & yyStateStack [yyStateStackSize];
	 }
	 * yyStateStackPtr = yyState;

   TermTrans:
	 for (;;) {	/* SPEC State = Next (State, Terminal); terminal transition */
	    register short * yyTCombPtr;

	    yyTCombPtr = (short *) (yyTBasePtr [yyState] + yyTerminal);
	    if (* yyTCombPtr ++ == yyState) { yyState = * yyTCombPtr; break; }
	    if ((yyState = yyDefault [yyState]) != yyNoState) goto TermTrans;

							/* syntax error */
	    if (! yyIsRepairing) {			/* report and recover */
	       yySymbolRange yyyTerminal = yyTerminal;

	       yyErrorCount ++;
	       yyErrorRecovery (& yyyTerminal, yyStateStack, yyStateStackSize, yyStateStackPtr - yyStateStack);
	       yyTerminal = yyyTerminal;
	       yyIsRepairing = true;
	    }
	    yyState = * yyStateStackPtr;
	    for (;;) {
	       if (yyNext (yyState, (yySymbolRange) yyTerminal) == yyNoState) { /* repair */
		  yySymbolRange		yyRepairToken;
		  tScanAttribute	yyRepairAttribute;
	    
		  yyRepairToken = yyContinuation [yyState];
		  yyState = yyNext (yyState, yyRepairToken);
		  if (yyState <= yyLastReadTermState) { /* read or read terminal reduce ? */
		     ErrorAttribute ((int) yyRepairToken, & yyRepairAttribute);
		     ErrorMessageI (xxTokenInserted, xxRepair, Attribute.Position,
			xxString, Parser_TokenName [yyRepairToken]);
		     if (yyState >= yyFirstFinalState) {	/* avoid second push */
			yyState = yyFinalToProd [yyState - yyFirstReadTermState];
		     }
		     yyGetAttribute (yyAttrStackPtr ++, yyRepairAttribute);
		     * ++ yyStateStackPtr = yyState;
		  }
		  if (yyState >= yyFirstFinalState) goto Final; /* final state ? */
	       } else {
		  yyState = yyNext (yyState, (yySymbolRange) yyTerminal);
		  goto Final;
	       }
	    }
	 }

   Final:
	 if (yyState >= yyFirstFinalState) {		/* final state ? */
	    if (yyState <= yyLastReadTermState) {	/* read terminal reduce ? */
	       yyStateStackPtr ++;
	       yyGetAttribute (yyAttrStackPtr ++, Attribute);
	       yyTerminal = GetToken ();
	       yyIsRepairing = false;
	    }

	    for (;;) {
	       /* register long yyNonterminal;		/* left-hand side */
# define yyNonterminal yyState

switch (yyState) {
case 73: /* _0000_ : source _EndOfFile .*/
  ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));
  ReleaseArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));
  return yyErrorCount;

case 74:
case 57: /* source : defs '%%' source_1 rules source_2 source_3 .*/
  yyStateStackPtr -=6; yyAttrStackPtr -=6; yyNonterminal = 32; {

} break;
case 75: /* source_3 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 31; {

} break;
case 76:
case 35: /* source_3 : '%%' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 31; {

} break;
case 77: /* source_2 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 30; {
/* line 102 "/tmp/lalr24773" */
/* line 106 "lex.lalr" */
 default_rules (); 
} break;
case 78: /* source_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 28; {
/* line 105 "/tmp/lalr24773" */
/* line 105 "lex.lalr" */
 in_defs = 0; str_put ("\nRULES\n\n"); 
} break;
case 79: /* defs : defs_1 .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 27; {

} break;
case 80: /* defs_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 33; {

} break;
case 81:
case 72: /* defs_1 : defs_1 defs_2 .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 33; {

} break;
case 82:
case 56: /* defs_2 : def '\n' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 34; {

} break;
case 83: /* def : macrodef expr .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 35; {
/* line 121 "/tmp/lalr24773" */
/* line 121 "lex.lalr" */
 str_put (" ."); put_macro (macro); level--; 
} break;
case 84:
case 52: /* def : STARTDEF .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 35; {

} break;
case 85:
case 53: /* def : '%t' def_1 '%t' .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 35; {
/* line 124 "/tmp/lalr24773" */
/* line 124 "lex.lalr" */
 (void) fprintf (stderr, "WARNING: translation table ignored !\n"); 
} break;
case 86: /* def : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 35; {

} break;
case 87: /* def_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 38; {

} break;
case 88:
case 71: /* def_1 : def_1 def_2 .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 38; {

} break;
case 89:
case 54: /* def_2 : TRANSLATION '\n' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 39; {

} break;
case 90:
case 55: /* macrodef : MACRODEF .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 36; {
/* line 134 "/tmp/lalr24773" */
/* line 130 "lex.lalr" */
 m = 0;
			     str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value);
			     str_put (" = ");
			     level++; 
} break;
case 91: /* rules : rules_1 .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 29; {

} break;
case 92: /* rules_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 40; {

} break;
case 93:
case 58: /* rules_1 : rules_1 rules_2 .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 40; {

} break;
case 94:
case 37: /* rules_2 : rule '\n' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 41; {
/* line 149 "/tmp/lalr24773" */
/* line 141 "lex.lalr" */
 str_put ("\n"); 
} break;
case 95:
case 59: /* rule : rule_1 action .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 42; {

} break;
case 96: /* rule_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 43; {

} break;
case 97:
case 68: /* rule_1 : startcond caret fullexpr rule_2 .*/
  yyStateStackPtr -=4; yyAttrStackPtr -=4; yyNonterminal = 43; {

} break;
case 98: /* rule_2 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 48; {

} break;
case 99:
case 69: /* rule_2 : endcond .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 48; {

} break;
case 100:
case 36: /* startcond : STARTCOND .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 45; {
/* line 158 "/tmp/lalr24773" */
/* line 145 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); str_put (" "); 
} break;
case 101: /* startcond : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 45; {

} break;
case 102:
case 40: /* caret : '^' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 46; {
/* line 163 "/tmp/lalr24773" */
/* line 148 "lex.lalr" */
 str_put ("< "); 
} break;
case 103: /* caret : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 46; {

} break;
case 104: /* endcond : '/' endcond_1 expr .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 49; {

} break;
case 105: /* endcond_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 50; {
/* line 169 "/tmp/lalr24773" */
/* line 151 "lex.lalr" */
 str_put (" / "); 
} break;
case 106:
case 67: /* fullexpr : fullexpr '|' fullexpr_1 term .*/
  yyStateStackPtr -=4; yyAttrStackPtr -=4; yyNonterminal = 47; {

} break;
case 107: /* fullexpr_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 51; {
/* line 173 "/tmp/lalr24773" */
/* line 153 "lex.lalr" */
 str_put (" , "); 
} break;
case 108:
case 70: /* fullexpr : term .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 47; {

} break;
case 109:
case 62: /* expr : expr '|' expr_1 term .*/
  yyStateStackPtr -=4; yyAttrStackPtr -=4; yyNonterminal = 37; {

} break;
case 110: /* expr_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 53; {
/* line 179 "/tmp/lalr24773" */
/* line 156 "lex.lalr" */
 str_put ("|"); 
} break;
case 111:
case 66: /* expr : term .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 37; {

} break;
case 112:
case 63: /* term : factor repeat .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 52; {

} break;
case 113:
case 48: /* repeat : REPEAT .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 55; {
/* line 185 "/tmp/lalr24773" */
/* line 161 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); 
} break;
case 114: /* repeat : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 55; {

} break;
case 115:
case 64: /* factor : factor secondary .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 54; {

} break;
case 116:
case 65: /* factor : secondary .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 54; {

} break;
case 117:
case 49: /* secondary : primary '?' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 56; {
/* line 195 "/tmp/lalr24773" */
/* line 167 "lex.lalr" */
 str_put ("?"); 
} break;
case 118:
case 51: /* secondary : primary '*' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 56; {
/* line 197 "/tmp/lalr24773" */
/* line 168 "lex.lalr" */
 str_put ("*"); 
} break;
case 119:
case 50: /* secondary : primary '+' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 56; {
/* line 199 "/tmp/lalr24773" */
/* line 169 "lex.lalr" */
 str_put ("+"); 
} break;
case 120: /* secondary : primary .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 56; {

} break;
case 121:
case 47: /* primary : '(' primary_1 expr ')' .*/
  yyStateStackPtr -=4; yyAttrStackPtr -=4; yyNonterminal = 57; {
/* line 203 "/tmp/lalr24773" */
/* line 175 "lex.lalr" */
 str_put (")"); level--; 
} break;
case 122:
case 42: /* primary : EXPANSION .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 204 "/tmp/lalr24773" */
/* line 176 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); 
} break;
case 123:
case 44: /* primary : CHARCLASS .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 206 "/tmp/lalr24773" */
/* line 177 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); 
} break;
case 124:
case 41: /* primary : '.' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 209 "/tmp/lalr24773" */
/* line 178 "lex.lalr" */
 str_put (" ANY "); 
} break;
case 125:
case 43: /* primary : STRING .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 210 "/tmp/lalr24773" */
/* line 179 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); 
} break;
case 126:
case 45: /* primary : CHAR .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 212 "/tmp/lalr24773" */
/* line 180 "lex.lalr" */
 print_char ((char) yyAttrStackPtr [1-1].Scan.char_value); 
} break;
case 127:
case 46: /* primary : '$' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 57; {
/* line 219 "/tmp/lalr24773" */
/* line 184 "lex.lalr" */
 if (level != 0)
			    { str_put ("$"); }
			  else
			    str_put (" >"); 
} break;
case 128: /* primary_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 58; {
/* line 222 "/tmp/lalr24773" */
/* line 174 "lex.lalr" */
 str_put ("("); level++; 
} break;
case 129: /* action : action_3 action_1 .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 44; {
/* line 225 "/tmp/lalr24773" */
/* line 188 "lex.lalr" */
 str_put (" }"); 
} break;
case 130:
case 38: /* action : PSEUDOACTION .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 44; {
/* line 227 "/tmp/lalr24773" */
/* line 189 "lex.lalr" */
 str_put (" ,"); 
} break;
case 131: /* action : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 44; {

} break;
case 132: /* action_3 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 59; {
/* line 230 "/tmp/lalr24773" */
/* line 187 "lex.lalr" */
 str_put ("	: { (void) GetWord (yytext); "); 
} break;
case 133:
case 60: /* action_1 : action_1 action_2 .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 60; {

} break;
case 134:
case 61: /* action_1 : action_2 .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 60; {

} break;
case 135:
case 39: /* action_2 : ACTION .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 61; {
/* line 236 "/tmp/lalr24773" */
/* line 196 "lex.lalr" */
 str_put ((char *) yyAttrStackPtr [1-1].Scan.string_value); 
} break;
}

	       /* SPEC State = Next (Top (), Nonterminal); nonterminal transition */
	       yyState = * (yyNBasePtr [* yyStateStackPtr ++] + yyNonterminal);
	       * yyAttrStackPtr ++ = yySynAttribute;
	       if (yyState < yyFirstFinalState) goto ParseLoop; /* read nonterminal reduce ? */
	    } 

	 } else {					/* read */
	    yyStateStackPtr ++;
	    yyGetAttribute (yyAttrStackPtr ++, Attribute);
	    yyTerminal = GetToken ();
	    yyIsRepairing = false;
	 }
      }
   }

static void yyErrorRecovery
# if defined __STDC__ | defined __cplusplus
   (yySymbolRange * yyTerminal, yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr)
# else
   (yyTerminal, yyStateStack, yyStackSize, yyStackPtr)
   yySymbolRange *	yyTerminal	;
   yyStateRange *	yyStateStack	;
   unsigned long	yyStackSize	;
   short		yyStackPtr	;
# endif
   {
      bool	yyTokensSkipped	;
      tSet	yyContinueSet	;
      tSet	yyRestartSet	;
      int	yyLength = 0	;
      char	yyContinueString [256];

   /* 1. report an error */
      ErrorMessage (xxSyntaxError, xxError, Attribute.Position);

   /* 2. report the set of expected terminal symbols */
      MakeSet (& yyContinueSet, (short) yyLastTerminal);
      yyComputeContinuation (yyStateStack, yyStackSize, yyStackPtr, & yyContinueSet);
      yyContinueString [0] = '\0';
      while (! IsEmpty (& yyContinueSet)) {
	 char * yyTokenString = Parser_TokenName [Extract (& yyContinueSet)];
	 if ((yyLength += strlen (yyTokenString) + 1) >= 256) break;
	 (void) strcat (yyContinueString, yyTokenString);
	 (void) strcat (yyContinueString, " ");
      }
      ErrorMessageI (xxExpectedTokens, xxInformation, Attribute.Position,
	 xxString, yyContinueString);
      ReleaseSet (& yyContinueSet);

   /* 3. compute the set of terminal symbols for restart of the parse */
      MakeSet (& yyRestartSet, (short) yyLastTerminal);
      yyComputeRestartPoints (yyStateStack, yyStackSize, yyStackPtr, & yyRestartSet);

   /* 4. skip terminal symbols until a restart point is reached */
      yyTokensSkipped = false;
      while (! IsElement (* yyTerminal, & yyRestartSet)) {
	 * yyTerminal = GetToken ();
	 yyTokensSkipped = true;
      }
      ReleaseSet (& yyRestartSet);

   /* 5. report the restart point */
      if (yyTokensSkipped) {
	 ErrorMessage (xxRestartPoint, xxInformation, Attribute.Position);
      }
   }

/*
   compute the set of terminal symbols that can be accepted (read)
   in a given stack configuration (eventually after reduce actions)
*/

static void yyComputeContinuation
# if defined __STDC__ | defined __cplusplus
   (yyStateRange * yyStack, unsigned long yyStackSize, short yyStackPtr, tSet * yyContinueSet)
# else
   (yyStack, yyStackSize, yyStackPtr, yyContinueSet)
   yyStateRange *	yyStack		;
   unsigned long	yyStackSize	;
   short		yyStackPtr	;
   tSet *		yyContinueSet	;
# endif
   {
      register yySymbolRange	yyTerminal;
      register yyStateRange	yyState = yyStack [yyStackPtr];

      AssignEmpty (yyContinueSet);
      for (yyTerminal = yyFirstTerminal; yyTerminal <= yyLastTerminal; yyTerminal ++) {
	 if (yyNext (yyState, yyTerminal) != yyNoState &&
	    yyIsContinuation (yyTerminal, yyStack, yyStackSize, yyStackPtr)) {
	    Include (yyContinueSet, (short) yyTerminal);
	 }
      }
   }

/*
   check whether a given terminal symbol can be accepted (read)
   in a certain stack configuration (eventually after reduce actions)
*/

static bool yyIsContinuation
# if defined __STDC__ | defined __cplusplus
   (yySymbolRange yyTerminal, yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr)
# else
   (yyTerminal, yyStateStack, yyStackSize, yyStackPtr)
   yySymbolRange	yyTerminal	;
   yyStateRange *	yyStateStack	;
   unsigned long	yyStackSize	;
   short		yyStackPtr	;
# endif
   {
      register yyStateRange	yState		;
      register yySymbolRange	yyNonterminal	;
	       yyStateRange *	yyStack		;
   
      MakeArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));	/* pass Stack by value */
# ifdef BCOPY
      bcopy ((char *) yyStateStack, (char *) yyStack, (int) sizeof (yyStateRange) * (yyStackPtr + 1));
# else
      (void) memcpy ((char *) yyStack, (char *) yyStateStack, (int) sizeof (yyStateRange) * (yyStackPtr + 1));
# endif

      yState = yyStack [yyStackPtr];
      for (;;) {
	 yyStack [yyStackPtr] = yState;
	 yState = yyNext (yState, yyTerminal);
	 if (yState == yyNoState) {
	    ReleaseArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
	    return false;
	 }
	 if (yState <= yyLastReadTermState) {		/* read or read terminal reduce ? */
	    ReleaseArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
	    return true;
	 }

	 for (;;) {					/* reduce */
	    if (yState == yyStopState) {
	       ReleaseArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
	       return true;
	    } else { 
	       yyStackPtr -= yyLength [yState - yyFirstReduceState];
	       yyNonterminal = yyLeftHandSide [yState - yyFirstReduceState];
	    }

	    yState = yyNext (yyStack [yyStackPtr], yyNonterminal);
	    if (yyStackPtr >= yyStackSize) {
	       ExtendArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
	    }
	    yyStackPtr ++;
	    if (yState < yyFirstFinalState) break;	/* read nonterminal ? */
	    yState = yyFinalToProd [yState - yyFirstReadTermState];	/* read nonterminal reduce */
	 }
      }
   }

/*
   compute a set of terminal symbols that can be used to restart
   parsing in a given stack configuration. we simulate parsing until
   end of file using a suffix program synthesized by the function
   Continuation. All symbols acceptable in the states reached during
   the simulation can be used to restart parsing.
*/

static void yyComputeRestartPoints
# if defined __STDC__ | defined __cplusplus
   (yyStateRange * yyStateStack, unsigned long yyStackSize, short yyStackPtr, tSet * yyRestartSet)
# else
   (yyStateStack, yyStackSize, yyStackPtr, yyRestartSet)
   yyStateRange *	yyStateStack	;
   unsigned long	yyStackSize	;
   short		yyStackPtr	;
   tSet *		yyRestartSet	;
# endif
   {
      register yyStateRange	yState		;
      register yySymbolRange	yyNonterminal	;
	       yyStateRange *	yyStack		;
	       tSet		yyContinueSet	;
   
      MakeArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange)); /* pass Stack by value */
# ifdef BCOPY
      bcopy ((char *) yyStateStack, (char *) yyStack, (int) sizeof (yyStateRange) * (yyStackPtr + 1));
# else
      (void) memcpy ((char *) yyStack, (char *) yyStateStack, (int) sizeof (yyStateRange) * (yyStackPtr + 1));
# endif

      MakeSet (& yyContinueSet, (short) yyLastTerminal);
      AssignEmpty (yyRestartSet);
      yState = yyStack [yyStackPtr];

      for (;;) {
	 if (yyStackPtr >= yyStackSize) {
	    ExtendArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
	 }
	 yyStack [yyStackPtr] = yState;
	 yyComputeContinuation (yyStack, yyStackSize, yyStackPtr, & yyContinueSet);
	 Union (yyRestartSet, & yyContinueSet);
	 yState = yyNext (yState, yyContinuation [yState]);

	 if (yState >= yyFirstFinalState) {		/* final state ? */
	    if (yState <= yyLastReadTermState) {	/* read terminal reduce ? */
	       yyStackPtr ++;
	       yState = yyFinalToProd [yState - yyFirstReadTermState];
	    }

	    for (;;) {					/* reduce */
	       if (yState == yyStopState) {
		  ReleaseSet (& yyContinueSet);
		  ReleaseArray ((char * *) & yyStack, & yyStackSize, sizeof (yyStateRange));
		  return;
	       } else { 
		  yyStackPtr -= yyLength [yState - yyFirstReduceState];
		  yyNonterminal = yyLeftHandSide [yState - yyFirstReduceState];
	       }

	       yState = yyNext (yyStack [yyStackPtr], yyNonterminal);
	       yyStackPtr ++;
	       if (yState < yyFirstFinalState) break;	/* read nonterminal ? */
	       yState = yyFinalToProd [yState - yyFirstReadTermState]; /* read nonterminal reduce */
	    }
	 } else {					/* read */
	    yyStackPtr ++;
	 }
      }
   }

/* access the parse table:   Next : State x Symbol -> Action */

static yyStateRange yyNext
# if defined __STDC__ | defined __cplusplus
   (yyStateRange yyState, yySymbolRange yySymbol)
# else
   (yyState, yySymbol) yyStateRange yyState; yySymbolRange yySymbol;
# endif
   {
      register yyTCombType * yyTCombPtr;

      if (yySymbol <= yyLastTerminal) {
	 for (;;) {
	    yyTCombPtr = yyTBasePtr [yyState] + yySymbol;
	    if (yyTCombPtr->Check != yyState) {
	       if ((yyState = yyDefault [yyState]) == yyNoState) return yyNoState;
	    } else {
	       return yyTCombPtr->Next;
	    }
	 }
      } else {
	return * (yyNBasePtr [yyState] + yySymbol);
      }
   }

static void BeginParser ()
   {

   }

void CloseParser ()
   {

   }
