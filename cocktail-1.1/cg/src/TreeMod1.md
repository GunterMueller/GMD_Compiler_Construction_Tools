DEFINITION MODULE TreeMod1;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

CONST BSS	= 32;	(* BITSET size *)


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE TreeDefMod (t: Tree.tTree);
PROCEDURE TreeImplMod (t: Tree.tTree);
PROCEDURE ImportList (t: Tree.tTree);

PROCEDURE BeginTreeMod1;
PROCEDURE CloseTreeMod1;

END TreeMod1.
