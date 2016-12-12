DEFINITION MODULE TreeC2;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

FROM Positions	IMPORT tPosition;

VAR Iterator	: Tree.tTree;

PROCEDURE WriteLine (Line: tPosition);


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE TreeIO (t: Tree.tTree);
PROCEDURE GetIterator (t: Tree.tTree);

PROCEDURE BeginTreeC2;
PROCEDURE CloseTreeC2;

END TreeC2.
