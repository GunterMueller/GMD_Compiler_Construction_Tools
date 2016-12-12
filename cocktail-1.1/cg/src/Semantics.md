DEFINITION MODULE Semantics;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)
 VAR TypeCount: SHORTCARD; 

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE Semantics (t: Tree.tTree);

PROCEDURE BeginSemantics;
PROCEDURE CloseSemantics;

END Semantics.
