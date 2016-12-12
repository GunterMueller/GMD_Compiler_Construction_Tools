(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 3 "puma.rex" *)

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


CONST EofToken	= 0;

VAR TokenLength	: INTEGER;
VAR Attribute	: tScanAttribute;
VAR ScanTabName	: ARRAY [0 .. 127] OF CHAR;
VAR Exit	: PROC;

PROCEDURE BeginScanner	;
PROCEDURE BeginFile	(FileName: ARRAY OF CHAR);
PROCEDURE GetToken	(): INTEGER;
PROCEDURE GetWord	(VAR Word: Strings.tString);
PROCEDURE GetLower	(VAR Word: Strings.tString);
PROCEDURE GetUpper	(VAR Word: Strings.tString);
PROCEDURE CloseFile	;
PROCEDURE CloseScanner	;

END Scanner.
