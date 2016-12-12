/* $Id: input.rex,v 2.4 1992/10/13 16:05:28 grosch rel $ */

/* $Log: input.rex,v $
 * Revision 2.4  1992/10/13  16:05:28  grosch
 * generate # line properly in case of strings in actions
 *
 * Revision 2.3  1992/08/07  15:15:11  grosch
 * allow several scanner and parsers; extend module Errors
 *
 * Revision 2.2  1991/12/04  16:21:41  grosch
 * unified escape conventions for all tools
 *
 * Revision 2.1  1991/11/21  14:47:50  grosch
 * new version of RCS on SPARC
 *
 * Revision 2.0  91/03/08  18:26:49  grosch
 * turned tables into initialized arrays (in C)
 * moved mapping tokens -> strings from Errors to Parser
 * changed interface for source position
 * 
 * Revision 1.3  90/06/11  18:47:51  grosch
 * allow keywords as token names, layout improvements
 * 
 * Revision 1.2  88/12/16  15:03:42  vielsack
 * identifier may now start with backslash ('\') which isn't significant
 * this can be used to define identifiers which are keywords
 * 
 * Revision 1.1  88/10/20  08:51:24  vielsack
 * use tScanAttribute instead of tAttribute
 * 
 * Revision 1.0  88/10/04  14:27:33  vielsack
 * Initial revision
 * 
 */

EXPORT	{

FROM StringMem	IMPORT tStringRef;
FROM Idents	IMPORT tIdent;
FROM Rules      IMPORT Expression;
FROM Lists      IMPORT tList;
FROM Positions	IMPORT tPosition;

TYPE
   AttributeMode = (Keys, Comment, Number, Action, Symbol, Coding, PrioPart, RightSide, Empty);

   tScanAttribute=
      RECORD
	 Position: tPosition;
	 CASE Mode: AttributeMode OF
	 | Comment: Comm	: tList;
	 | Number: Value	: CARDINAL;
	 | Action: Act	: tList;
	 | Symbol: Sym	: tIdent;
	 | Coding:
	     HasCoding	: BOOLEAN ;
	     CodNumbPos	: tPosition;
	     CodValue	: CARDINAL;
	 | PrioPart,
	   RightSide:
	     Expr:  Expression;
	     CASE HasPrio: BOOLEAN OF
	       TRUE:
		 PriSym	: tIdent;
		 PriSymPos	: tPosition;
	     END;
	 END;
      END;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute);
}

GLOBAL	{

FROM SYSTEM	IMPORT ADR, ADDRESS;
FROM Strings	IMPORT tString, ArrayToString, Concatenate, SubString, AssignEmpty, Assign, Char, Length;
FROM StringMem	IMPORT tStringRef, PutString;
FROM Idents	IMPORT MakeIdent;
FROM Lists	IMPORT tList, Append, MakeList;
FROM Limits	IMPORT MaxShortCard;
FROM WriteTok	IMPORT tLanguage, Language;
FROM Errors	IMPORT eWarning, eError, eCharacter, eString, ErrorMessage, ErrorMessageI;
FROM Positions	IMPORT tPosition;

CONST
  eCharIgnored	= 10;
  eEolString	= 11;
  eUnClAction	= 12;
  eUnClComment	= 13;
  eUnClString	= 14;

  SymEqual	=  1;
  SymColon	=  2;
  SymPoint	=  3;
  SymOr		=  4;
  SymStar	=  5;
  SymPlus	=  6;
  SymList	=  7;
  SymLBrace	=  8;
  SymRBrace	=  9;
  SymLBracket	= 10;
  SymRBracket	= 11;
  SymEXPORT	= 12;
  SymGLOBAL	= 13;
  SymLOCAL	= 14;
  SymBEGIN	= 15;
  SymCLOSE	= 16;
  SymTOKEN	= 17;
  SymOPER	= 18;
  SymNONE	= 19;
  SymLEFT	= 20;
  SymRIGHT	= 21;
  SymRULE	= 22;
  SymPREC	= 23;
  SymComment	= 24; (* Schreibweise wie in MODULA-2		*)
  SymNumber	= 25; (* vorzeichenlose ganze Zahl		*)
  SymAction	= 26; (* in '{' und '}' eingeschlossene Aktion	*)
  SymIdentifier	= 27; (* letter (digit | letter) *		*)
  SymString	= 28; (* durch "'" oder '"' begrenzte Zeichenkette *)
  SymScanner	= 29;
  SymParser	= 30;

VAR level: INTEGER; Position: tPosition;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR Attr: tScanAttribute);
  VAR s : tString;
  BEGIN
    ArrayToString ('-error-', s);
    CASE Token OF
      0: ;
    | 1..23:  Attr.Mode	:= Keys;
    | 	 24:  Attr.Mode	:= Comment;
	      MakeList (Attr.Comm);
    |    25:  Attr.Mode	:= Number;
	      Attr.Value:= MaxShortCard;
    |    26:  Attr.Mode	:= Action;
	      MakeList (Attr.Act);
    | 27,28:  Attr.Mode	:= Symbol;
	      Attr.Sym	:= MakeIdent (s);
    END;
  END ErrorAttribute;

PROCEDURE GetNumber (VAR Word: tString): CARDINAL;
  VAR i, n, d : CARDINAL;
   BEGIN
      i := 0;
      n := 0;
      WHILE i < Length (Word) DO
	i := i+1;
	d := (ORD(Char (Word, i))-ORD('0'));
	IF (n > MaxShortCard DIV 10) OR (n*10 > MaxShortCard - d) THEN
	  RETURN MaxShortCard;
	END;
	n := n*10 + d;
      END;
      RETURN n;
   END GetNumber;
}

LOCAL	{ VAR Word, String, LastWord: tString; c: CHAR; PrevState: SHORTCARD; }

EOF	{
CASE yyStartState OF
| code			: ErrorMessage (eUnClAction , eError, Attribute.Position);
| comment, comment2	: ErrorMessage (eUnClComment, eError, Attribute.Position);
| Str1, Str2, CStr1, CStr2:ErrorMessage (eUnClString, eError, Attribute.Position);
ELSE
END;
}

DEFINE
  digit		= {0-9}		.
  letter	= {a-z A-Z _}	.
  cmt		= - {*(\t\n}	.
  cmt2		= - {*\t\n}	.
  codechar	= - {\\{\}\t\n'"} .
  StrCh1	= - {'\t\n}	.
  StrCh2	= - {"\t\n}	.
  CStrCh1	= - {'\t\n\\}	.
  CStrCh2	= - {"\t\n\\}	.

START token, rule, code, Str1, Str2, CStr1, CStr2, comment, comment2

RULES

#token#	"="	: { Attribute.Mode := Keys; RETURN SymEqual	; }
#rule#	":"	: { Attribute.Mode := Keys; RETURN SymColon	; }
#rule#	"."	: { Attribute.Mode := Keys; RETURN SymPoint	; }
#rule#	"|"	: { Attribute.Mode := Keys; RETURN SymOr	; }
#rule#	"*"	: { Attribute.Mode := Keys; RETURN SymStar	; }
#rule#	"+"	: { Attribute.Mode := Keys; RETURN SymPlus	; }
#rule#	"||"	: { Attribute.Mode := Keys; RETURN SymList	; }
#rule#	"("	: { Attribute.Mode := Keys; RETURN SymLBrace	; }
#rule#	")"	: { Attribute.Mode := Keys; RETURN SymRBrace	; }
#rule#	"["	: { Attribute.Mode := Keys; RETURN SymLBracket	; }
#rule#	"]"	: { Attribute.Mode := Keys; RETURN SymRBracket	; }
#STD#	\SCANNER: { Attribute.Mode := Keys; RETURN SymScanner	; }
#STD#	\PARSER	: { Attribute.Mode := Keys; RETURN SymParser	; }
#STD#	\EXPORT	: { Attribute.Mode := Keys; RETURN SymEXPORT	; }
#STD#	\GLOBAL	: { Attribute.Mode := Keys; RETURN SymGLOBAL	; }
#STD#	\LOCAL	: { Attribute.Mode := Keys; RETURN SymLOCAL	; }
#STD#	\BEGIN	: { Attribute.Mode := Keys; RETURN SymBEGIN	; }
#STD#	\CLOSE	: { Attribute.Mode := Keys; RETURN SymCLOSE	; }
#STD#	TOKEN	: { Attribute.Mode := Keys; yyStart (token); RETURN SymTOKEN	; }

#token#	OPER	: { Attribute.Mode := Keys; RETURN SymOPER	; }
#token#	NONE	: { Attribute.Mode := Keys; RETURN SymNONE	; }
#token#	LEFT	: { Attribute.Mode := Keys; RETURN SymLEFT	; }
#token#	RIGHT	: { Attribute.Mode := Keys; RETURN SymRIGHT	; }
#token#	RULE	: { Attribute.Mode := Keys; yyStart (rule); RETURN SymRULE	; }

#rule#	PREC	: { Attribute.Mode := Keys; RETURN SymPREC	; }

#token#	digit +	:
{
  Attribute.Mode := Number;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  Attribute.Value := GetNumber (Word);
  RETURN SymNumber;
}

#STD, token, rule#	\\ letter (letter | digit) *	:
{
  Attribute.Mode := Keys;
  GetWord (Word);
  SubString (Word, 2, Length (Word), String);
  Attribute.Sym := MakeIdent (String);
  RETURN SymIdentifier;
}

#STD, token, rule#	letter (letter | digit) *	:
{
  Attribute.Mode := Keys;
  GetWord (Word);
  Attribute.Sym := MakeIdent (Word);
  RETURN SymIdentifier;
}

#STD, rule#	"{"	:
{
  PrevState := yyStartState;
  Position := Attribute.Position;
  yyStart (code);
  GetWord (LastWord);
  Attribute.Mode := Action;
  MakeList (Attribute.Act);
  level := 1;
}

#STD, token, rule# \f | \r :- {}

#token, rule, code# '	: { GetWord (String);
  			    Attribute.Mode := Symbol;
			    IF Language = C
			    THEN yyStart (CStr1);
			    ELSE yyStart (Str1);
			    END;}

#token, rule, code# \"	: { GetWord (String);
  			    Attribute.Mode := Symbol;
			    IF Language = C
			    THEN yyStart (CStr2);
			    ELSE yyStart (Str2);
			    END;}

#Str1#	StrCh1  + | \'\'	,
#Str2#	StrCh2  + | \"\"	,
#CStr1#	CStrCh1 + | \\ ANY ?	,
#CStr2#	CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1, CStr2#	\\ \n	:- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '		,
#Str2, CStr2# \"	:- {Strings.Append (String, Char (String, 1));
			    yyPrevious;
			    IF yyStartState = code THEN
			       Concatenate (LastWord, String);
			    ELSE
  			       Attribute.Sym := MakeIdent (String);
  			       RETURN SymString;
			    END;}

#Str1, Str2, CStr1, CStr2# \t :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n : {ErrorMessage (eEolString, eError, Attribute.Position);
			    Strings.Append (String, Char (String, 1));
			    yyEol (0); yyPrevious;
			    IF yyStartState = code THEN
			       Concatenate (LastWord, String);
			    ELSE
  			       Attribute.Sym := MakeIdent (String);
			       RETURN SymString;
			    END;}

#STD, token, rule#	"(*"	:
{
  yyStart (comment);
  GetWord (LastWord);
  Attribute.Mode := Comment;
  MakeList (Attribute.Comm);
  level := 1;
}

#STD, token, rule#	"/*"	:- { yyStart (comment2); }

#STD, token, rule#	- {\t\n\ }	:
{
  GetWord (Word);
  c := Char (Word, 1);
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));
}

#code#	\\ ANY | codechar +	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#code#	\\	:
{
  c := '\';
  ErrorMessageI (eCharIgnored, eWarning, Attribute.Position, eCharacter, ADR (c));
}

#code#	\t	:-
{
  yyTab;
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#code#	\n	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  Append (Attribute.Act, ADDRESS (PutString (LastWord)));
  AssignEmpty (LastWord);
  yyEol (0);
}

#code#	"{"	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (level);
}

#code#	"}"	:-
{
  DEC (level);
  GetWord (Word);
  Concatenate (LastWord, Word);
  IF level = 0 THEN
    yyStart (PrevState);
    Attribute.Position := Position;
    Append (Attribute.Act, ADDRESS (PutString (LastWord)));
    RETURN SymAction;
  END;
}

#comment#	"(*"	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  INC (level);
}

#comment#	"*)"	:-
{
  DEC (level);
  GetWord (Word);
  Concatenate (LastWord, Word);
  IF level = 0 THEN
    yyPrevious;
    Append (Attribute.Comm, ADDRESS (PutString (LastWord)));
    RETURN SymComment;
  END;
}

#comment#	"(" | "*" | cmt +	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#comment#	\t	:-
{
  yyTab;
  GetWord (Word);
  Concatenate (LastWord, Word);
}

#comment#	\n	:-
{
  GetWord (Word);
  Concatenate (LastWord, Word);
  Append (Attribute.Comm, ADDRESS (PutString (LastWord)));
  AssignEmpty (LastWord);
  yyEol (0);
}

#comment2#	"*" | cmt2 +	:- { }
#comment2#	"*/"		:- { yyPrevious; }
