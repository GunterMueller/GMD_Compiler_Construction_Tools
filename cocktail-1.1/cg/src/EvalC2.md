DEFINITION MODULE EvalC2;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE EvalImplC (t: Tree.tTree);

PROCEDURE BeginEvalC2;
PROCEDURE CloseEvalC2;

END EvalC2.
