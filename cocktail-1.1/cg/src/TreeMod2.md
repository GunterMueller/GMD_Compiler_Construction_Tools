DEFINITION MODULE TreeMod2;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

FROM Positions	IMPORT tPosition;

VAR Iterator	: Tree.tTree;

PROCEDURE WriteLine (Line: tPosition);


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE TreeIO (t: Tree.tTree);
PROCEDURE GetIterator (t: Tree.tTree);

PROCEDURE BeginTreeMod2;
PROCEDURE CloseTreeMod2;

END TreeMod2.
