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

/* line 2 "/tmp/lalr24798" */
/* line 1 "yacc.lalr" */

typedef union { tScanAttribute Scan; } tParsAttribute;

int rword;		/* 0 = %token, 1 = %oper, 2 = %type */
tStringRef lhs, tag, prec;
tStringRef left_str, right_str, none_str, colon_str, bar_str, action_str, prec_str, dot_str;
int has_rhs, has_action;
struct tCell default_action = { 0, 0 };


# if defined lex_interface & ! defined yylvalDef
     tParsAttribute yylval;
# endif

# ifndef yyInitStackSize
#    define yyInitStackSize	100
# endif
# define yyNoState		0

# define yyFirstTerminal	0
# define yyLastTerminal		20
# define yyTableMax		138
# define yyNTableMax		54
# define yyFirstReadState	1
# define yyLastReadState	32
# define yyFirstReadTermState	33
# define yyLastReadTermState	45
# define yyLastReadNontermState	53
# define yyFirstReduceState	54
# define yyLastReduceState	91
# define yyStartState		1
# define yyStopState		54

# define yyFirstFinalState	yyFirstReadTermState

typedef unsigned short	yyStateRange	;
typedef unsigned short	yySymbolRange	;
typedef struct	{ yyStateRange Check, Next; } yyTCombType ;

	char *		Parser_TokenName	[yyLastTerminal + 2] = {
"_EndOfFile",
"identifier",
"C_IDENT",
"number",
"%left",
"%right",
"%nonassoc",
"%token",
"%prec",
"%type",
"%start",
"%union",
"%%",
"<",
">",
",",
"|",
"{",
"}",
";",
":",
""
};
static	yyTCombType	yyTComb		[yyTableMax + 1] = {
{32, 54},
{3, 38},
{4, 59},
{5, 6},
{1, 60},
{1, 60},
{1, 60},
{1, 60},
{10, 11},
{1, 60},
{1, 60},
{1, 60},
{1, 60},
{2, 33},
{2, 34},
{2, 35},
{2, 36},
{24, 56},
{2, 37},
{2, 3},
{2, 39},
{2, 4},
{6, 79},
{7, 8},
{11, 88},
{12, 41},
{11, 88},
{15, 83},
{16, 17},
{24, 43},
{13, 77},
{26, 27},
{13, 77},
{14, 58},
{27, 44},
{14, 15},
{11, 88},
{28, 29},
{0, 0},
{0, 0},
{11, 88},
{11, 12},
{13, 77},
{11, 88},
{25, 71},
{14, 58},
{13, 77},
{0, 0},
{19, 80},
{14, 20},
{19, 80},
{20, 82},
{20, 82},
{20, 82},
{0, 0},
{0, 0},
{25, 26},
{0, 0},
{0, 0},
{20, 82},
{19, 80},
{0, 0},
{0, 0},
{20, 82},
{19, 80},
{0, 0},
{0, 0},
{20, 82},
{20, 82},
{0, 0},
{20, 82},
{21, 86},
{21, 86},
{21, 86},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{21, 86},
{0, 0},
{0, 0},
{0, 0},
{21, 86},
{22, 91},
{22, 40},
{22, 91},
{21, 86},
{21, 86},
{23, 81},
{21, 86},
{23, 81},
{22, 10},
{0, 0},
{0, 0},
{0, 0},
{22, 91},
{0, 0},
{0, 0},
{0, 0},
{22, 91},
{23, 81},
{0, 0},
{22, 91},
{0, 0},
{23, 81},
{0, 0},
{29, 75},
{23, 42},
{29, 45},
{29, 75},
{29, 75},
{29, 75},
{29, 75},
{0, 0},
{29, 75},
{29, 75},
{29, 75},
{29, 75},
{0, 0},
{0, 0},
{29, 75},
{30, 64},
{30, 64},
{30, 64},
{30, 64},
{0, 0},
{30, 64},
{30, 64},
{30, 64},
{30, 64},
{0, 0},
{0, 0},
{30, 31},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
{0, 0},
};
static	unsigned short	yyNComb		[yyNTableMax - yyLastTerminal] = {
2,
5,
14,
24,
48,
32,
50,
25,
28,
30,
53,
7,
9,
13,
49,
16,
18,
47,
46,
19,
21,
22,
23,
47,
52,
51,
47,
0,
0,
0,
0,
0,
0,
0,
};
static	yyTCombType *	yyTBasePtr	[yyLastReadState + 1] = {
& yyTComb [0],
& yyTComb [0],
& yyTComb [9],
& yyTComb [0],
& yyTComb [0],
& yyTComb [1],
& yyTComb [2],
& yyTComb [3],
& yyTComb [0],
& yyTComb [0],
& yyTComb [7],
& yyTComb [24],
& yyTComb [7],
& yyTComb [30],
& yyTComb [33],
& yyTComb [7],
& yyTComb [8],
& yyTComb [0],
& yyTComb [0],
& yyTComb [48],
& yyTComb [51],
& yyTComb [71],
& yyTComb [84],
& yyTComb [89],
& yyTComb [17],
& yyTComb [43],
& yyTComb [30],
& yyTComb [20],
& yyTComb [36],
& yyTComb [106],
& yyTComb [118],
& yyTComb [0],
& yyTComb [0],
};
static	unsigned short*	yyNBasePtr	[yyLastReadState + 1] = {
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-20],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-17],
& yyNComb [-15],
& yyNComb [-21],
& yyNComb [-17],
& yyNComb [-12],
& yyNComb [-12],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-21],
& yyNComb [-7],
& yyNComb [-6],
& yyNComb [-21],
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
21,
22,
0,
0,
0,
23,
0,
0,
0,
21,
22,
23,
0,
0,
11,
0,
0,
0,
0,
0,
0,
0,
28,
28,
0,
};
static	unsigned char	yyLength	[yyLastReduceState - yyFirstReduceState + 1] = {
2,
6,
0,
1,
0,
0,
0,
2,
2,
1,
3,
1,
1,
1,
1,
1,
3,
0,
1,
2,
3,
1,
2,
5,
2,
0,
5,
4,
0,
0,
2,
2,
0,
2,
2,
3,
2,
0,
};
static	yySymbolRange	yyLeftHandSide	[yyLastReduceState - yyFirstReduceState + 1] = {
39,
26,
25,
25,
24,
22,
21,
21,
27,
27,
27,
28,
28,
28,
28,
28,
29,
29,
30,
30,
30,
31,
31,
23,
23,
32,
35,
35,
37,
36,
33,
33,
33,
38,
34,
34,
34,
34,
};
static	yySymbolRange	yyContinuation	[yyLastReadState + 1] = {
0,
4,
12,
1,
2,
2,
20,
20,
0,
0,
1,
0,
18,
0,
0,
20,
20,
0,
0,
0,
0,
0,
0,
0,
0,
1,
1,
14,
1,
1,
4,
1,
0,
};
static	unsigned short	yyFinalToProd	[yyLastReadNontermState - yyFirstReadTermState + 1] = {
66,
67,
68,
65,
69,
62,
63,
84,
87,
90,
57,
70,
76,
89,
85,
55,
78,
61,
74,
73,
72,
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
case 54: /* _0000_ : spec _EndOfFile .*/
  ReleaseArray ((char * *) & yyStateStack, & yyStateStackSize, sizeof (yyStateRange));
  ReleaseArray ((char * *) & yyAttributeStack, & yyAttrStackSize, sizeof (tParsAttribute));
  return yyErrorCount;

case 55:
case 48: /* spec : spec_1 '%%' spec_2 rules spec_3 spec_4 .*/
  yyStateStackPtr -=6; yyAttrStackPtr -=6; yyNonterminal = 26; {

} break;
case 56: /* spec_4 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 25; {

} break;
case 57:
case 43: /* spec_4 : '%%' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 25; {

} break;
case 58: /* spec_3 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 24; {
/* line 54 "/tmp/lalr24798" */
/* line 47 "yacc.lalr" */
 yacc_globals (); 
} break;
case 59: /* spec_2 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 22; {
/* line 56 "/tmp/lalr24798" */
/* line 47 "yacc.lalr" */
 put_text (text_list); 
} break;
case 60: /* spec_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 21; {

} break;
case 61:
case 50: /* spec_1 : spec_1 def .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 21; {

} break;
case 62:
case 38: /* def : '%start' identifier .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 27; {
/* line 61 "/tmp/lalr24798" */
/* line 50 "yacc.lalr" */
 start_symbol = yyAttrStackPtr [2-1].Scan.string; 
} break;
case 63:
case 39: /* def : '%union' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 27; {

} break;
case 64: /* def : rword tag nlist .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 27; {

} break;
case 65:
case 36: /* rword : '%token' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 28; {
/* line 66 "/tmp/lalr24798" */
/* line 55 "yacc.lalr" */
 rword = 0; 
} break;
case 66:
case 33: /* rword : '%left' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 28; {
/* line 68 "/tmp/lalr24798" */
/* line 56 "yacc.lalr" */
 rword = 1; put_oper (left_str); 
} break;
case 67:
case 34: /* rword : '%right' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 28; {
/* line 70 "/tmp/lalr24798" */
/* line 57 "yacc.lalr" */
 rword = 1; put_oper (right_str); 
} break;
case 68:
case 35: /* rword : '%nonassoc' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 28; {
/* line 72 "/tmp/lalr24798" */
/* line 58 "yacc.lalr" */
 rword = 1; put_oper (none_str); 
} break;
case 69:
case 37: /* rword : '%type' .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 28; {
/* line 74 "/tmp/lalr24798" */
/* line 59 "yacc.lalr" */
 rword = 2; type = 1; 
} break;
case 70:
case 44: /* tag : '<' identifier '>' .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 29; {
/* line 77 "/tmp/lalr24798" */
/* line 62 "yacc.lalr" */
 tag = yyAttrStackPtr [2-1].Scan.string; 
} break;
case 71: /* tag : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 29; {
/* line 79 "/tmp/lalr24798" */
/* line 63 "yacc.lalr" */
 tag = 0; 
} break;
case 72:
case 53: /* nlist : nmno .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 30; {

} break;
case 73:
case 52: /* nlist : nlist nmno .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 30; {

} break;
case 74:
case 51: /* nlist : nlist ',' nmno .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 30; {

} break;
case 75: /* nmno : identifier .*/
  yyStateStackPtr -=1; yyAttrStackPtr -=1; yyNonterminal = 31; {
/* line 87 "/tmp/lalr24798" */
/* line 71 "yacc.lalr" */
 switch (rword) {
			 case 1 : put_oper (yyAttrStackPtr [1-1].Scan.string);
			 case 0 : put_token (yyAttrStackPtr [1-1].Scan.string, 0); break;
			 default: break;
		       }
		       if (tag) put_type (yyAttrStackPtr [1-1].Scan.string, tag); 
} break;
case 76:
case 45: /* nmno : identifier number .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 31; {
/* line 96 "/tmp/lalr24798" */
/* line 77 "yacc.lalr" */
 switch (rword) {
			        case 1 : put_oper (yyAttrStackPtr [1-1].Scan.string);
			        case 0 : put_token (yyAttrStackPtr [1-1].Scan.string, yyAttrStackPtr [2-1].Scan.number); break;
			        default: break;
			      }
			      if (tag) put_type (yyAttrStackPtr [1-1].Scan.string, tag); 
} break;
case 77: /* rules : C_IDENT rules_1 ':' rbody prec .*/
  yyStateStackPtr -=5; yyAttrStackPtr -=5; yyNonterminal = 23; {
/* line 106 "/tmp/lalr24798" */
/* line 89 "yacc.lalr" */
 if (has_rhs && ! has_action) put_whole_action (& default_action, true);
	    if (prec) { put_delim (prec_str); put_delim (prec); }
	    if (yyTerminal != 16) put_delim (dot_str);
	    put_rule (rule_elmts_list); put_text (text_list); 
} break;
case 78:
case 49: /* rules : rules rule .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 23; {

} break;
case 79: /* rules_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 32; {
/* line 114 "/tmp/lalr24798" */
/* line 86 "yacc.lalr" */
 rule_elmts_list = prec = has_rhs = has_action = 0; lhs = yyAttrStackPtr [0-1].Scan.string;
	    put_lhs (lhs); put_delim (lhs); put_delim (colon_str); 
} break;
case 80: /* rule : C_IDENT rule_1 ':' rbody prec .*/
  yyStateStackPtr -=5; yyAttrStackPtr -=5; yyNonterminal = 35; {
/* line 120 "/tmp/lalr24798" */
/* line 100 "yacc.lalr" */
 if (has_rhs && ! has_action) put_whole_action (& default_action, true);
	    if (prec) { put_delim (prec_str); put_delim (prec); }
	    if (yyTerminal != 16) put_delim (dot_str);
	    put_rule (rule_elmts_list); put_text (text_list); 
} break;
case 81: /* rule : '|' rule_2 rbody prec .*/
  yyStateStackPtr -=4; yyAttrStackPtr -=4; yyNonterminal = 35; {
/* line 127 "/tmp/lalr24798" */
/* line 108 "yacc.lalr" */
 if (has_rhs && ! has_action) put_whole_action (& default_action, true);
	    if (prec) { put_delim (prec_str); put_delim (prec); }
	    if (yyTerminal != 16) put_delim (dot_str);
	    put_rule (rule_elmts_list); put_text (text_list); 
} break;
case 82: /* rule_2 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 37; {
/* line 134 "/tmp/lalr24798" */
/* line 105 "yacc.lalr" */
 rule_elmts_list = prec = has_rhs = has_action = 0;
	    put_lhs (lhs); put_delim (bar_str); 
} break;
case 83: /* rule_1 : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 36; {
/* line 139 "/tmp/lalr24798" */
/* line 97 "yacc.lalr" */
 rule_elmts_list = prec = has_rhs = has_action = 0; lhs = yyAttrStackPtr [0-1].Scan.string;
	    put_lhs (lhs); put_delim (lhs); put_delim (colon_str); 
} break;
case 84:
case 40: /* rbody : rbody identifier .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 33; {
/* line 144 "/tmp/lalr24798" */
/* line 114 "yacc.lalr" */
 put_symbol (yyAttrStackPtr [2-1].Scan.string); has_rhs = 1; 
} break;
case 85:
case 47: /* rbody : rbody act .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 33; {

} break;
case 86: /* rbody : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 33; {

} break;
case 87:
case 41: /* act : '{' '}' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 38; {
/* line 151 "/tmp/lalr24798" */
/* line 121 "yacc.lalr" */
 has_action = 1; put_whole_action (yyAttrStackPtr [2-1].Scan.action, has_rhs &
		    /* is it last action ? */
		    (yyTerminal == 16 || yyTerminal == 19 || yyTerminal == 0)); 
} break;
case 88: /* prec : '%prec' identifier .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 34; {
/* line 157 "/tmp/lalr24798" */
/* line 126 "yacc.lalr" */
 prec = yyAttrStackPtr [2-1].Scan.string; 
} break;
case 89:
case 46: /* prec : '%prec' identifier act .*/
  yyStateStackPtr -=3; yyAttrStackPtr -=3; yyNonterminal = 34; {
/* line 159 "/tmp/lalr24798" */
/* line 127 "yacc.lalr" */
 prec = yyAttrStackPtr [2-1].Scan.string; 
} break;
case 90:
case 42: /* prec : prec ';' .*/
  yyStateStackPtr -=2; yyAttrStackPtr -=2; yyNonterminal = 34; {

} break;
case 91: /* prec : .*/
  yyStateStackPtr -=0; yyAttrStackPtr -=0; yyNonterminal = 34; {

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
/* line 23 "/tmp/lalr24798" */
/* line 19 "yacc.lalr" */

left_str	= PutString ("\n\tLEFT", 6);
right_str	= PutString ("\n\tRIGHT", 7);
none_str	= PutString ("\n\tNONE", 6);
colon_str	= PutString ("\t:", 2);
bar_str		= PutString ("\t|", 2);
action_str	= PutString (" }}", 3);
prec_str	= PutString ("PREC", 4);
dot_str		= PutString ("\n\t.", 3);
default_action.car = action_str;

   }

void CloseParser ()
   {

   }
