(* $Id: Scanner.md,v 2.3 1992/08/18 09:05:32 grosch rel $ *)

DEFINITION MODULE Scanner;

IMPORT Strings;

(* line 12 "ell.rex" *)
 
FROM Idents	IMPORT tIdent;
FROM StringMem	IMPORT tStringRef;
FROM Positions	IMPORT tPosition;

TYPE tScanAttribute = RECORD
		     Position : tPosition;
		     CASE :INTEGER OF
		     | 0 : value : INTEGER;
		     | 1 : ident : tIdent;
		     | 2 : ref   : tStringRef;
		     END;
		   END;

CONST NoValue = -1;

VAR
  Epsilon	: tIdent;
  EndOfToken	: tIdent;
  NoIdent	: tIdent;
  NoString	: tStringRef;

PROCEDURE ErrorAttribute (Token : INTEGER; VAR Attribute : tScanAttribute);


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
