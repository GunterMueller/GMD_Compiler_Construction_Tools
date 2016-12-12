DEFINITION MODULE TreeC1;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

CONST BSS	= 8;	(* BITSET size *)


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE TreeDefC (t: Tree.tTree);
PROCEDURE TreeImplC (t: Tree.tTree);

PROCEDURE BeginTreeC1;
PROCEDURE CloseTreeC1;

END TreeC1.
