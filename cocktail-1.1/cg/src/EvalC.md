DEFINITION MODULE EvalC;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)
 VAR Class: Tree.tTree; 

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE EvalDefC (t: Tree.tTree);
PROCEDURE EvalImplC (t: Tree.tTree);
PROCEDURE EvalImplHead (t: Tree.tTree);
PROCEDURE GenEvaluator (t: Tree.tTree);

PROCEDURE BeginEvalC;
PROCEDURE CloseEvalC;

END EvalC.
