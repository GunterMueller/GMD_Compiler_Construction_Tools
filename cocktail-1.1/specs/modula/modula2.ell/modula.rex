GLOBAL	{
FROM SYSTEM	IMPORT ADR;
FROM Errors	IMPORT Message, MessageI, Error;
IMPORT Errors;
FROM Strings	IMPORT tString, AssignEmpty, Concatenate, Append, SubString,
			Length, StringToInt, StringToNumber, StringToReal;
FROM StringMem	IMPORT tStringRef, PutString;
FROM Idents	IMPORT tIdent, MakeIdent;

VAR NestingLevel	: CARDINAL;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attribute: tScanAttribute);
   BEGIN
   END ErrorAttribute;

CONST
   TokIdent		=  1	;
   TokIntConst		=  2	;
   TokRealConst		=  6	;
   TokStringConst	=  7	;
   TokNotEqual		=  8	;	(* '#', '<>'		*)
   TokLParent		=  9	;	(* '('			*)
   TokRParent		= 10	;	(* ')'			*)
   TokTimes		= 11	;	(* '*'			*)
   TokPlus		= 12	;	(* '+'			*)
   TokComma		= 13	;	(* ','			*)
   TokMinus		= 14	;	(* '-'			*)
   TokDot		= 15	;	(* '.'			*)
   TokRange		= 16	;	(* '..'			*)
   TokDivide		= 17	;	(* '/'			*)
   TokColon		= 18	;	(* ':'			*)
   TokAssign		= 19	;	(* ':='			*)
   TokSemiColon		= 20	;	(* ';'			*)
   TokLess		= 21	;	(* '<'			*)
   TokLessEqual		= 22	;	(* '<='			*)
   TokEqual		= 24	;	(* '='			*)
   TokGreater		= 25	;	(* '>'			*)
   TokGreaterEqual	= 26	;	(* '>='			*)
   TokLBracket		= 27	;	(* '['			*)
   TokRBracket		= 28	;	(* ']'			*)
   TokArrow		= 29	;	(* '^'			*)
   TokLBrace		= 30	;	(* '{'			*)
   TokBar		= 31	;	(* '|'			*)
   TokRBrace		= 32	;	(* '}'			*)

   TokAnd		= 34	;	(* AND, '&'		*)
   TokArray		= 35	;	(* ARRAY		*)
   TokBegin		= 36	;	(* BEGIN		*)
   TokBy		= 37	;	(* BY			*)
   TokCase		= 38	;	(* CASE			*)
   TokConst		= 39	;	(* CONST		*)
   TokDefinition	= 40	;	(* DEFINITION		*)
   TokDiv		= 41	;	(* DIV			*)
   TokDo		= 42	;	(* DO			*)
   TokElse		= 43	;	(* ELSE			*)
   TokElsif		= 44	;	(* ELSIF		*)
   TokEnd		= 45	;	(* END			*)
   TokExit		= 46	;	(* EXIT			*)
   TokExport		= 47	;	(* EXPORT		*)
   TokFor		= 48	;	(* FOR			*)
   TokFrom		= 49	;	(* FROM			*)
   TokIf		= 50	;	(* IF			*)
   TokImplementation	= 51	;	(* IMPLEMENTATION	*)
   TokImport		= 52	;	(* IMPORT		*)
   TokIn		= 53	;	(* IN			*)
   TokLoop		= 54	;	(* LOOP			*)
   TokMod		= 55	;	(* MOD			*)
   TokModule		= 56	;	(* MODULE		*)
   TokNot		= 57	;	(* NOT, '~'		*)
   TokOf		= 58	;	(* OF			*)
   TokOr		= 59	;	(* OR			*)
   TokPointer		= 60	;	(* POINTER		*)
   TokProcedure		= 61	;	(* PROCEDURE		*)
   TokQualified		= 62	;	(* QUALIFIED		*)
   TokRecord		= 63	;	(* RECORD		*)
   TokRepeat		= 64	;	(* REPEAT		*)
   TokReturn		= 65	;	(* RETURN		*)
   TokSet		= 66	;	(* SET			*)
   TokThen		= 67	;	(* THEN			*)
   TokTo		= 68	;	(* TO			*)
   TokType		= 69	;	(* TYPE			*)
   TokUntil		= 70	;	(* UNTIL		*)
   TokVar		= 71	;	(* VAR			*)
   TokWhile		= 72	;	(* WHILE		*)
   TokWith		= 73	;	(* WITH			*)
}

LOCAL	{
   VAR
      String, S : tString	;
      Word	: tString	;
      indent	: tIdent	;
      string	: tStringRef	;
      integer	: INTEGER	;
      real	: REAL		;
      ch	: CHAR		;
}

BEGIN	{ NestingLevel := 0; }

DEFAULT	{ GetWord (Word);
	  MessageI ("illegal character", Error, Attribute.Position, Errors.String, ADR (Word)); }

EOF	{ IF yyStartState = Comment THEN
	     Message ("unclosed comment", Error, Attribute.Position); END; }
   
DEFINE

   digit	= {0-9}		.
   letter	= {a-z A-Z}	.
   CmtCh	= - {*(\t\n}	.
   StrCh1	= - {'\t\n}	.
   StrCh2	= - {"\t\n}	.

START	Comment, Str1, Str2

RULES

#STD, Comment# "(*"	:- {INC (NestingLevel); yyStart (Comment);}
#Comment#  "*)"		:- {DEC (NestingLevel); IF NestingLevel = 0 THEN yyStart (STD); END;}
#Comment#  "(" | "*" | CmtCh + :- {}

#STD# digit +		,
#STD# digit + / ".."	,
#STD# digit + / BY	: {GetWord (Word);
			   integer := StringToInt (Word);
			   RETURN TokIntConst;}
#STD# {0-7} + B		: {GetWord (Word);
			   SubString (Word, 1, Length (Word) - 1, String);
			   integer := StringToNumber (String, 8);
			   RETURN TokIntConst;}
#STD# {0-7} + C		: {GetWord (Word);
			   SubString (Word, 1, Length (Word) - 1, String);
			   ch := CHR (StringToNumber (String, 8));
			   RETURN TokStringConst;}
#STD# digit {0-9 A-F} * H : {
			   GetWord (Word);
			   SubString (Word, 1, Length (Word) - 1, String);
			   integer := StringToNumber (String, 16);
			   RETURN TokIntConst;}
#STD# digit + "." digit * (E {+\-} ? digit +) ? : {
			   GetWord (Word);
			   real := StringToReal (Word);
			   RETURN TokRealConst;}

#STD#	'		:  {AssignEmpty (String); yyStart (Str1);}
#Str1#	StrCh1 +	:- {GetWord (S); Concatenate (String, S);}
#Str1#	'		:- {yyStart (STD); string := PutString (String); RETURN TokStringConst;}

#STD#	\"		:  {AssignEmpty (String); yyStart (Str2);}
#Str2#	StrCh2 +	:- {GetWord (S); Concatenate (String, S);}
#Str2#	\"		:- {yyStart (STD); string := PutString (String); RETURN TokStringConst;}

#Str1, Str2# \t		:- {Append (String, 11C); yyTab;}
#Str1, Str2# \n		:- {Message ("unclosed string", Error, Attribute.Position); yyEol (0);
			    yyStart (STD); string := PutString (String); RETURN TokStringConst;}

#STD# "#"		: {RETURN TokNotEqual		;}
#STD# "&"		: {RETURN TokAnd		;}
#STD# "("		: {RETURN TokLParent		;}
#STD# ")"		: {RETURN TokRParent		;}
#STD# "*"		: {RETURN TokTimes		;}
#STD# "+"		: {RETURN TokPlus		;}
#STD# ","		: {RETURN TokComma		;}
#STD# "-"		: {RETURN TokMinus		;}
#STD# "."		: {RETURN TokDot		;}
#STD# ".."		: {RETURN TokRange		;}
#STD# "/"		: {RETURN TokDivide		;}
#STD# ":"		: {RETURN TokColon		;}
#STD# ":="		: {RETURN TokAssign		;}
#STD# ";"		: {RETURN TokSemiColon		;}
#STD# "<"		: {RETURN TokLess		;}
#STD# "<="		: {RETURN TokLessEqual		;}
#STD# "<>"		: {RETURN TokNotEqual		;}
#STD# "="		: {RETURN TokEqual		;}
#STD# ">"		: {RETURN TokGreater		;}
#STD# ">="		: {RETURN TokGreaterEqual	;}
#STD# "["		: {RETURN TokLBracket		;}
#STD# "]"		: {RETURN TokRBracket		;}
#STD# "^"		: {RETURN TokArrow		;}
#STD# "{"		: {RETURN TokLBrace		;}
#STD# "|"		: {RETURN TokBar		;}
#STD# "}"		: {RETURN TokRBrace		;}
#STD# "~"		: {RETURN TokNot		;}

#STD# AND		: {RETURN TokAnd		;}
#STD# ARRAY		: {RETURN TokArray		;}
#STD# BEGIN		: {RETURN TokBegin		;}
#STD# BY		: {RETURN TokBy			;}
#STD# CASE		: {RETURN TokCase		;}
#STD# CONST		: {RETURN TokConst		;}
#STD# DEFINITION	: {RETURN TokDefinition		;}
#STD# DIV		: {RETURN TokDiv		;}
#STD# DO		: {RETURN TokDo			;}
#STD# ELSE		: {RETURN TokElse		;}
#STD# ELSIF		: {RETURN TokElsif		;}
#STD# END		: {RETURN TokEnd		;}
#STD# EXIT		: {RETURN TokExit		;}
#STD# EXPORT		: {RETURN TokExport		;}
#STD# FOR		: {RETURN TokFor		;}
#STD# FROM		: {RETURN TokFrom		;}
#STD# IF		: {RETURN TokIf			;}
#STD# IMPLEMENTATION	: {RETURN TokImplementation	;}
#STD# IMPORT		: {RETURN TokImport		;}
#STD# IN		: {RETURN TokIn			;}
#STD# LOOP		: {RETURN TokLoop		;}
#STD# MOD		: {RETURN TokMod		;}
#STD# MODULE		: {RETURN TokModule		;}
#STD# \NOT		: {RETURN TokNot		;}
#STD# OF		: {RETURN TokOf			;}
#STD# OR		: {RETURN TokOr			;}
#STD# POINTER		: {RETURN TokPointer		;}
#STD# PROCEDURE		: {RETURN TokProcedure		;}
#STD# QUALIFIED		: {RETURN TokQualified		;}
#STD# RECORD		: {RETURN TokRecord		;}
#STD# REPEAT		: {RETURN TokRepeat		;}
#STD# RETURN		: {RETURN TokReturn		;}
#STD# SET		: {RETURN TokSet		;}
#STD# THEN		: {RETURN TokThen		;}
#STD# TO		: {RETURN TokTo			;}
#STD# TYPE		: {RETURN TokType		;}
#STD# UNTIL		: {RETURN TokUntil		;}
#STD# VAR		: {RETURN TokVar		;}
#STD# WHILE		: {RETURN TokWhile		;}
#STD# WITH		: {RETURN TokWith		;}

#STD# letter (letter | digit) * : {
			   GetWord (Word);
			   indent := MakeIdent (Word);
			   RETURN TokIdent;}
