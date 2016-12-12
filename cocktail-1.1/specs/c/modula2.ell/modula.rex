GLOBAL	{
# include <stdio.h>
# include <math.h>

# ifdef __cplusplus
extern "C" {
# include "Memory.h"
# include "Positions.h"
# include "Errors.h"
# include "StringMem.h"
# include "Idents.h"
}
# else
# include "Memory.h"
# include "Positions.h"
# include "Errors.h"
# include "StringMem.h"
# include "Idents.h"
# endif

extern char * strcat ();

static int NestingLevel = 0;

void ErrorAttribute
# if defined __STDC__ | defined __cplusplus
   (int Token, tScanAttribute * Attribute)
# else
   (Token, Attribute) int Token; tScanAttribute * Attribute;
# endif
   {}

# define TokIdent		 1
# define TokIntConst		 2
# define TokRealConst		 6
# define TokStringConst		 7
# define TokNotEqual		 8	/* '#', '<>'		*/
# define TokLParent		 9	/* '('			*/
# define TokRParent		10	/* ')'			*/
# define TokTimes		11	/* '*'			*/
# define TokPlus		12	/* '+'			*/
# define TokComma		13	/* ','			*/
# define TokMinus		14	/* '-'			*/
# define TokDot			15	/* '.'			*/
# define TokRange		16	/* '..'			*/
# define TokDivide		17	/* '/'			*/
# define TokColon		18	/* ':'			*/
# define TokAssign		19	/* ':='			*/
# define TokSemiColon		20	/* ';'			*/
# define TokLess		21	/* '<'			*/
# define TokLessEqual		22	/* '<='			*/
# define TokEqual		24	/* '='			*/
# define TokGreater		25	/* '>'			*/
# define TokGreaterEqual	26	/* '>='			*/
# define TokLBracket		27	/* '['			*/
# define TokRBracket		28	/* ']'			*/
# define TokArrow		29	/* '^'			*/
# define TokLBrace		30	/* '{'			*/
# define TokBar			31	/* '|'			*/
# define TokRBrace		32	/* '}'			*/

# define TokAnd			34	/* AND, '&'		*/
# define TokArray		35	/* ARRAY		*/
# define TokBegin		36	/* BEGIN		*/
# define TokBy			37	/* BY			*/
# define TokCase		38	/* CASE			*/
# define TokConst		39	/* CONST		*/
# define TokDefinition		40	/* DEFINITION		*/
# define TokDiv			41	/* DIV			*/
# define TokDo			42	/* DO			*/
# define TokElse		43	/* ELSE			*/
# define TokElsif		44	/* ELSIF		*/
# define TokEnd			45	/* END			*/
# define TokExit		46	/* EXIT			*/
# define TokExport		47	/* EXPORT		*/
# define TokFor			48	/* FOR			*/
# define TokFrom		49	/* FROM			*/
# define TokIf			50	/* IF			*/
# define TokImplementation	51	/* IMPLEMENTATION	*/
# define TokImport		52	/* IMPORT		*/
# define TokIn			53	/* IN			*/
# define TokLoop		54	/* LOOP			*/
# define TokMod			55	/* MOD			*/
# define TokModule		56	/* MODULE		*/
# define TokNot			57	/* NOT, '~'		*/
# define TokOf			58	/* OF			*/
# define TokOr			59	/* OR			*/
# define TokPointer		60	/* POINTER		*/
# define TokProcedure		61	/* PROCEDURE		*/
# define TokQualified		62	/* QUALIFIED		*/
# define TokRecord		63	/* RECORD		*/
# define TokRepeat		64	/* REPEAT		*/
# define TokReturn		65	/* RETURN		*/
# define TokSet			66	/* SET			*/
# define TokThen		67	/* THEN			*/
# define TokTo			68	/* TO			*/
# define TokType		69	/* TYPE			*/
# define TokUntil		70	/* UNTIL		*/
# define TokVar			71	/* VAR			*/
# define TokWhile		72	/* WHILE		*/
# define TokWith		73	/* WITH			*/
}

LOCAL	{
   char		String [256], S [256], Word [256];
   tIdent	ident	;
   tStringRef	string	;
   int		integer	;
   float	real	;
   int		ch	;
}

DEFAULT	{ MessageI ("illegal character", xxError, Attribute.Position, xxCharacter, TokenPtr); }

EOF	{ if (yyStartState == Comment) Message ("unclosed comment", xxError, Attribute.Position); }
   
DEFINE

   digit	= {0-9}		.
   letter	= {a-z A-Z}	.
   CmtCh	= - {*(\t\n}	.
   StrCh1	= - {'\t\n}	.
   StrCh2	= - {"\t\n}	.

START	Comment, Str1, Str2

RULES

#STD, Comment# "(*"	:- {++ NestingLevel; yyStart (Comment);}
#Comment#  "*)"		:- {if (-- NestingLevel == 0) yyStart (STD);}
#Comment#  "(" | "*" | CmtCh + :- {}

#STD# digit +		,
#STD# digit + / ".."	,
#STD# digit + / BY	: {(void) GetWord (Word);
			   integer = atoi (Word);
			   return TokIntConst;}
#STD# {0-7} + B		: {(void) GetWord (Word);
			   (void) sscanf (Word, "%o", & integer);
			   return TokIntConst;}
#STD# {0-7} + C		: {(void) GetWord (Word);
			   (void) sscanf (Word, "%o", & ch);
			   return TokStringConst;}
#STD# digit {0-9 A-F} * H : {
			   (void) GetWord (Word);
			   (void) sscanf (Word, "%x", & integer);
			   return TokIntConst;}
#STD# digit + "." digit * (E {+\-} ? digit +) ? : {
			   (void) GetWord (Word);
			   real = atof (Word);
			   return TokRealConst;}

#STD#	'		:  {String [0] ='\0'; yyStart (Str1);}
#Str1#	StrCh1 +	:- {(void) GetWord (S); (void) strcat (String, S);}
#Str1#	'		:- {yyStart (STD); string = PutString (String, strlen (String));
			   return TokStringConst;}

#STD#	\"		:  {String [0] ='\0'; yyStart (Str2);}
#Str2#	StrCh2 +	:- {(void) GetWord (S); (void) strcat (String, S);}
#Str2#	\"		:- {yyStart (STD); string = PutString (String, strlen (String));
			   return TokStringConst;}

#Str1, Str2# \t		:- {(void) strcat (String, "\t"); yyTab;}
#Str1, Str2# \n		:- {Message ("unclosed string", xxError, Attribute.Position);
			   string = PutString (String, strlen (String));
			   yyEol (0); yyStart (STD); return TokStringConst;}

#STD# "#"		: {return TokNotEqual		;}
#STD# "&"		: {return TokAnd		;}
#STD# "("		: {return TokLParent		;}
#STD# ")"		: {return TokRParent		;}
#STD# "*"		: {return TokTimes		;}
#STD# "+"		: {return TokPlus		;}
#STD# ","		: {return TokComma		;}
#STD# "-"		: {return TokMinus		;}
#STD# "."		: {return TokDot		;}
#STD# ".."		: {return TokRange		;}
#STD# "/"		: {return TokDivide		;}
#STD# ":"		: {return TokColon		;}
#STD# ":="		: {return TokAssign		;}
#STD# ";"		: {return TokSemiColon		;}
#STD# "<"		: {return TokLess		;}
#STD# "<="		: {return TokLessEqual		;}
#STD# "<>"		: {return TokNotEqual		;}
#STD# "="		: {return TokEqual		;}
#STD# ">"		: {return TokGreater		;}
#STD# ">="		: {return TokGreaterEqual	;}
#STD# "["		: {return TokLBracket		;}
#STD# "]"		: {return TokRBracket		;}
#STD# "^"		: {return TokArrow		;}
#STD# "{"		: {return TokLBrace		;}
#STD# "|"		: {return TokBar		;}
#STD# "}"		: {return TokRBrace		;}
#STD# "~"		: {return TokNot		;}

#STD# AND		: {return TokAnd		;}
#STD# ARRAY		: {return TokArray		;}
#STD# BEGIN		: {return TokBegin		;}
#STD# BY		: {return TokBy			;}
#STD# CASE		: {return TokCase		;}
#STD# CONST		: {return TokConst		;}
#STD# DEFINITION	: {return TokDefinition		;}
#STD# DIV		: {return TokDiv		;}
#STD# DO		: {return TokDo			;}
#STD# ELSE		: {return TokElse		;}
#STD# ELSIF		: {return TokElsif		;}
#STD# END		: {return TokEnd		;}
#STD# EXIT		: {return TokExit		;}
#STD# EXPORT		: {return TokExport		;}
#STD# FOR		: {return TokFor		;}
#STD# FROM		: {return TokFrom		;}
#STD# IF		: {return TokIf			;}
#STD# IMPLEMENTATION	: {return TokImplementation	;}
#STD# IMPORT		: {return TokImport		;}
#STD# IN		: {return TokIn			;}
#STD# LOOP		: {return TokLoop		;}
#STD# MOD		: {return TokMod		;}
#STD# MODULE		: {return TokModule		;}
#STD# \NOT		: {return TokNot		;}
#STD# OF		: {return TokOf			;}
#STD# OR		: {return TokOr			;}
#STD# POINTER		: {return TokPointer		;}
#STD# PROCEDURE		: {return TokProcedure		;}
#STD# QUALIFIED		: {return TokQualified		;}
#STD# RECORD		: {return TokRecord		;}
#STD# REPEAT		: {return TokRepeat		;}
#STD# RETURN		: {return TokReturn		;}
#STD# SET		: {return TokSet		;}
#STD# THEN		: {return TokThen		;}
#STD# TO		: {return TokTo			;}
#STD# TYPE		: {return TokType		;}
#STD# UNTIL		: {return TokUntil		;}
#STD# VAR		: {return TokVar		;}
#STD# WHILE		: {return TokWhile		;}
#STD# WITH		: {return TokWith		;}

#STD# letter (letter | digit) * : {
			   ident = MakeIdent (TokenPtr, TokenLength);
			   return TokIdent;}
