/* Ich, Doktor Josef Grosch, Informatiker, 20.3.1989 */

EXPORT  {
FROM StringMem	IMPORT tStringRef;
FROM Idents	IMPORT tIdent	;
FROM Texts	IMPORT tText	;
FROM Positions	IMPORT tPosition;

TYPE
yyIdent = RECORD Ident: tIdent; END;
yyOperator = RECORD Ident: tIdent; END;
yyIncOperator = RECORD Ident: tIdent; END;
yyTargetBlock = RECORD Text: tText; END;
yyString = RECORD StringRef: tStringRef; END;
yyNumber = RECORD StringRef: tStringRef; END;
yyTargetCode = RECORD StringRef: tStringRef; END;
yyWhiteSpace = RECORD StringRef: tStringRef; END;
(* '::' *) yy9 = RECORD StringRef: tStringRef; END;

tScanAttribute = RECORD
Position: tPosition;
CASE : SHORTCARD OF
| 1: Ident: yyIdent;
| 2: Operator: yyOperator;
| 3: IncOperator: yyIncOperator;
| 4: TargetBlock: yyTargetBlock;
| 5: String: yyString;
| 6: Number: yyNumber;
| 7: TargetCode: yyTargetCode;
| 8: WhiteSpace: yyWhiteSpace;
| 9: (* '::' *) yy9: yy9;
END; END;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);


PROCEDURE Error		(Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE ErrorI	(Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
PROCEDURE Warning	(Text: ARRAY OF CHAR; Position: tPosition);
PROCEDURE WarningI	(Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
}

GLOBAL  {
FROM SYSTEM	IMPORT ADR;
FROM StringMem	IMPORT PutString;
FROM Strings	IMPORT tString, Concatenate, Char, SubString,
			AssignEmpty, Length, WriteL;
FROM Idents	IMPORT tIdent, MakeIdent, NoIdent, GetStringRef;
FROM Texts	IMPORT MakeText, Append;
FROM Sets	IMPORT IsElement;
FROM Tree	IMPORT Options, ErrorCount;
FROM Positions	IMPORT tPosition;

IMPORT Errors;

VAR NestingLevel: INTEGER; Position, StringPos: tPosition;

PROCEDURE ErrorAttribute (Token: INTEGER; VAR pAttribute: tScanAttribute);
BEGIN
 pAttribute.Position := Attribute.Position;
 CASE Token OF
 | (* Ident *) 1: 
 pAttribute.Ident.Ident	:= NoIdent	;
 ;
 | (* Operator *) 2: 
 pAttribute.Operator.Ident	:= NoIdent	;
 ;
 | (* IncOperator *) 3: 
 pAttribute.IncOperator.Ident	:= NoIdent	;
 ;
 | (* TargetBlock *) 4: 
 MakeText (pAttribute.TargetBlock.Text); ;
 ;
 | (* String *) 5: 
 pAttribute.String.StringRef	:= GetStringRef (NoIdent);
 ;
 | (* Number *) 6: 
 pAttribute.Number.StringRef	:= GetStringRef (NoIdent);
 ;
 | (* TargetCode *) 7: 
 pAttribute.TargetCode.StringRef	:= GetStringRef (NoIdent);
 ;
 | (* WhiteSpace *) 8: 
 pAttribute.WhiteSpace.StringRef	:= GetStringRef (NoIdent);
 ;
 | (* '::' *) 9: 
 pAttribute.yy9.StringRef	:= GetStringRef (NoIdent);
 ;
 ELSE
 END;
END ErrorAttribute;


PROCEDURE Error (Text: ARRAY OF CHAR; Position: tPosition);
   BEGIN
      Errors.Message (Text, Errors.Error, Position);
      INC (ErrorCount);
   END Error;

PROCEDURE ErrorI (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
   BEGIN
      Errors.MessageI (Text, Errors.Error, Position, Errors.Ident, ADR (Ident));
      INC (ErrorCount);
   END ErrorI;

PROCEDURE Warning (Text: ARRAY OF CHAR; Position: tPosition);
   BEGIN
      IF NOT IsElement (ORD ('s'), Options) THEN
	 Errors.Message (Text, Errors.Warning, Position);
      END;
   END Warning;

PROCEDURE WarningI (Text: ARRAY OF CHAR; Position: tPosition; Ident: tIdent);
   BEGIN
      IF NOT IsElement (ORD ('s'), Options) THEN
	 Errors.MessageI (Text, Errors.Warning, Position, Errors.Ident, ADR (Ident));
      END;
   END WarningI;
}

LOCAL	{ VAR Word, String, TargetCode: tString; }

BEGIN	{ NestingLevel := 0; }

DEFAULT	{
   GetWord (Word);
   Errors.MessageI ("illegal character", Errors.Error, Attribute.Position, Errors.String, ADR (Word));
}

EOF     {
   CASE yyStartState OF
   | comment	: Error ("unclosed comment", Position);
   | expr	,
     targetcode	: Error ("unclosed target code", Position);
   | CStr1, CStr2,
     Str1, Str2	: Error ("unclosed string", StringPos);
   ELSE
   END;
}

DEFINE  letter  =   {A-Z a-z _}	.
        digit   =   {0-9}	.
	CmtCh   = - {*\t\n}	.
	StrCh1	= - {'\t\n}	.
	StrCh2	= - {"\t\n}	.
	CStrCh1	= - {'\t\n\\}	.
	CStrCh2	= - {"\t\n\\}	.
	code	= - {\\\t\n{\}'"} .
	anyExpr	= - {\\\t\n{\}'":\ a-zA-Z} .

START	comment, Str1, Str2, CStr1, CStr2, targetcode, expr

RULE

#targetcode#	"{"	: {
			   IF NestingLevel = 0 THEN
			      MakeText (Attribute.TargetBlock.Text);
			      AssignEmpty (TargetCode);
			      Position := Attribute.Position;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			   INC (NestingLevel);
			}

#targetcode#	"}"	:- {
			   DEC (NestingLevel);
			   IF NestingLevel = 0 THEN
			      yyStart (STD);
			      Append (Attribute.TargetBlock.Text, TargetCode);
			      Attribute.Position := Position;
			      RETURN 4;
			   ELSE
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	code +	:- {
			   IF NestingLevel > 0 THEN
			      GetWord (Word);
			      Concatenate (TargetCode, Word);
			   END;
			}

#targetcode#	\t	:- {
			   IF NestingLevel > 0 THEN
			      Strings.Append (TargetCode, 11C);
			   END;
			   yyTab;
			}

#targetcode#	\n	:- {
			   IF NestingLevel > 0 THEN
			      Append (Attribute.TargetBlock.Text, TargetCode);
			      AssignEmpty (TargetCode);
			   END;
			   yyEol (0);
			}

#targetcode#	\\ ANY	:- {
			   IF NestingLevel > 0 THEN
			      GetWord (Word);
			      Strings.Append (TargetCode, Char (Word, 2));
			   END;
			}

#targetcode#	\\	:- {
			   IF NestingLevel > 0 THEN
			      Strings.Append (TargetCode, '\');
			   END;
			}

#STD, expr# "/*"	:  {yyStart (comment); Position := Attribute.Position;}
#comment# "*/"		:- {yyPrevious;}
#comment# "*" | CmtCh +	:- {}

#STD# \f | \r		:- {}

#STD# (digit + "." digit * | digit * "." digit +) ({Ee} {+\-} ? digit +) ? | digit +
			:  {GetWord (Word);
	                    Attribute.Number.StringRef := PutString (Word);
			    RETURN 6;}

#STD, expr, targetcode# ' :{GetWord (String);
			    StringPos := Attribute.Position;
			    IF IsElement (ORD ('c'), Options)
			    THEN yyStart (CStr1);
			    ELSE yyStart (Str1);
			    END;}

#STD, expr, targetcode# \":{GetWord (String);
			    StringPos := Attribute.Position;
			    IF IsElement (ORD ('c'), Options)
			    THEN yyStart (CStr2);
			    ELSE yyStart (Str2);
			    END;}

#Str1#	StrCh1 +	,
#Str2#	StrCh2 +	,
#CStr1#	CStrCh1 + | \\ ANY ? ,
#CStr2#	CStrCh2 + | \\ ANY ? :- {GetWord (Word); Concatenate (String, Word);}

#CStr1#	\\ \n		,
#CStr2#	\\ \n		:- {GetWord (Word); Concatenate (String, Word); yyEol (0);}

#Str1, CStr1# '		,
#Str2, CStr2# \"	:- {Strings.Append (String, Char (String, 1));
			    yyPrevious;
			    IF yyStartState = targetcode THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.String.StringRef := PutString (String);
			       RETURN 5;
			    END;}

#Str1, Str2, CStr1, CStr2# \t :- {Strings.Append (String, 11C); yyTab;}

#Str1, Str2, CStr1, CStr2# \n :- {Error ("unclosed string", Attribute.Position);
			    Strings.Append (String, Char (String, 1));
			    yyEol (0); yyPrevious;
			    IF yyStartState = targetcode THEN
			       Concatenate (TargetCode, String);
			    ELSE
			       Attribute.String.StringRef := PutString (String);
			       RETURN 5;
			    END;}

#STD# "::"		: {RETURN 9			;}

#STD# "{"		: {IF NestingLevel = 0 THEN Position := Attribute.Position; END;
			   yyStart (expr); INC (NestingLevel); RETURN 34;}

#expr# anyExpr *	: {GetWord (Word);
			   Attribute.TargetCode.StringRef := PutString (Word);
			   RETURN 7		;}

#expr# "{"		: {INC (NestingLevel);
			   GetWord (Word);
			   Attribute.TargetCode.StringRef := PutString (Word);
			   RETURN 7		;}

#expr# "}"		: {DEC (NestingLevel);
			   IF NestingLevel = 0 THEN
			      yyStart (STD);
			      RETURN 35;
			   ELSE
			      GetWord (Word);
			      Attribute.TargetCode.StringRef := PutString (Word);
			      RETURN 7;
			   END				;}

#expr# ":"		: {GetWord (Word);
			   Attribute.TargetCode.StringRef := PutString (Word);
			   RETURN 7		;}

#expr# "::"		: {GetWord (Word);
			   Attribute.yy9.StringRef := PutString (Word);
			   RETURN 9			;}

#expr# " " +		: {GetWord (Word);
			   Attribute.WhiteSpace.StringRef := PutString (Word);
			   RETURN 8		;}

#expr# \n		: {GetWord (Word);
			   Attribute.WhiteSpace.StringRef := PutString (Word);
			   yyEol (0);
			   RETURN 8		;}

#expr# \t		: {GetWord (Word);
			   Attribute.WhiteSpace.StringRef := PutString (Word);
			   yyTab;
			   RETURN 8		;}

#expr# \\ ANY		: {GetWord (Word);
			   SubString (Word, 2, 2, String);
			   Attribute.TargetCode.StringRef := PutString (String);
			   RETURN 7		;}

#expr# \\		: {GetWord (Word);
			   Attribute.TargetCode.StringRef := PutString (Word);
			   RETURN 7		;}

#STD# BEGIN		: {yyStart (targetcode); RETURN 19	;}
#STD# CLOSE		: {yyStart (targetcode); RETURN 20	;}
#STD# EXPORT		: {yyStart (targetcode); RETURN 16;}
#STD# GLOBAL		: {yyStart (targetcode); RETURN 18;}
#STD# IMPORT		: {yyStart (targetcode); RETURN 17;}
#STD# LOCAL		: {yyStart (targetcode); RETURN 30	;}

#STD# 
  "!"
| "!="
| "#"
| "%"
| "&"
| "&&"
| "*"
| "+"
| "-"
| "/"
| "<"
| "<<"
| "<="
| "<>"
| "="
| "=="
| ">"
| ">="
| ">>"
| "|"
| "||"
| "~"
| AND
| DIV
| IN
| MOD
| \NOT
| OR
			: {GetWord (Word);
	                   Attribute.Operator.Ident := MakeIdent (Word);
			   RETURN 2		;}

#STD# "++" | "--"	: {GetWord (Word);
	                   Attribute.IncOperator.Ident := MakeIdent (Word);
			   RETURN 3		;}

#STD# \\ - {\ \t\n} +	: {GetWord (Word);
			   SubString (Word, 2, Length (Word), String);
	                   Attribute.Operator.Ident := MakeIdent (String);
			   RETURN 2		;}

 #STD#TRAFO	: { RETURN 10; }
 #STD#TREE	: { RETURN 11; }
 #STD#\,	: { RETURN 12; }
 #STD#PUBLIC	: { RETURN 13; }
 #STD#EXTERN	: { RETURN 14; }
 #STD#\;	: { RETURN 15; }
 #STD#EXPORT	: { RETURN 16; }
 #STD#IMPORT	: { RETURN 17; }
 #STD#GLOBAL	: { RETURN 18; }
 #STD#BEGIN	: { RETURN 19; }
 #STD#CLOSE	: { RETURN 20; }
 #STD#PROCEDURE	: { RETURN 21; }
 #STD#\(	: { RETURN 22; }
 #STD#REF	: { RETURN 23; }
 #STD#\:	: { RETURN 24; }
 #STD#\.	: { RETURN 25; }
 #STD#\[	: { RETURN 26; }
 #STD#\]	: { RETURN 27; }
 #STD#\=\>	: { RETURN 28; }
 #STD#\)	: { RETURN 29; }
 #STD#LOCAL	: { RETURN 30; }
 #STD#\.\.	: { RETURN 31; }
 #STD#NIL	: { RETURN 32; }
 #STD#_	: { RETURN 33; }
 #STD#\{	: { RETURN 34; }
 #STD#\}	: { RETURN 35; }
 #STD#\-\>	: { RETURN 36; }
 #STD#\^	: { RETURN 37; }
 #STD#\:\>	: { RETURN 38; }
 #STD#\:\=	: { RETURN 39; }
 #STD#\?	: { RETURN 40; }
 #STD#REJECT	: { RETURN 41; }
 #STD#FAIL	: { RETURN 42; }
 #STD#NL	: { RETURN 43; }
 #STD#RETURN	: { RETURN 44; }
 #STD#FUNCTION	: { RETURN 45; }
 #STD#PREDICATE	: { RETURN 46; }


#STD# "..."		: {RETURN 31			;}
#STD# ":-"		: {RETURN 40			;}

#STD, expr# letter (letter | digit) *
			: {GetWord (Word);
	                   Attribute.Ident.Ident := MakeIdent (Word);
			   RETURN 1			;}
