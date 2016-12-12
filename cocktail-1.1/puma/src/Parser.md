(* $Id: Parser.md,v 2.1 1992/08/07 15:28:42 grosch rel $ *)

DEFINITION MODULE Parser;

(* line 118 "Parser.lalr" *)



VAR ParsTabName	: ARRAY [0..128] OF CHAR;

PROCEDURE TokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);

PROCEDURE Parser (): CARDINAL;
PROCEDURE CloseParser;

END Parser.
