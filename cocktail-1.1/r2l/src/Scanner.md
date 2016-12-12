(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 38 "r2l.rex" *)


FROM Idents	IMPORT tIdent	;
FROM StringMem	IMPORT tStringRef;
FROM Texts	IMPORT tText	;
FROM Positions	IMPORT tPosition;

TYPE
   tScanAttribute	= RECORD
	      Position	: tPosition	;
	 CASE : INTEGER OF
	 | 1: Ident	: tIdent	;
	 | 2: Number	: SHORTCARD	;
	 | 3: String	: tStringRef	;
	 | 4: Ch	: CHAR		;
	 | 5: Text	: tText		;
	 END;
      END;

PROCEDURE ErrorAttribute (Token: CARDINAL; VAR Attribute: tScanAttribute);


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
