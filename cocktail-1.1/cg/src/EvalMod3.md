DEFINITION MODULE EvalMod3;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE EvalImplMod (t: Tree.tTree);
PROCEDURE ToBit0 (yyP2: Tree.tTree; yyP1: INTEGER): INTEGER;

PROCEDURE BeginEvalMod3;
PROCEDURE CloseEvalMod3;

END EvalMod3.
