DEFINITION MODULE EvalMod2;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE EvalImplMod (t: Tree.tTree);

PROCEDURE BeginEvalMod2;
PROCEDURE CloseEvalMod2;

END EvalMod2.
