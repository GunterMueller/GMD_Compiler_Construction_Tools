(* $Id: Parser.md,v 2.2 1992/08/07 15:13:51 grosch rel $ *)

DEFINITION MODULE Parser;



VAR ParsTabName	: ARRAY [0..128] OF CHAR;

PROCEDURE TokenName (Token: CARDINAL; VAR Name: ARRAY OF CHAR);

PROCEDURE Parser (): CARDINAL;
PROCEDURE CloseParser;

END Parser.
