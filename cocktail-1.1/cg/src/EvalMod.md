DEFINITION MODULE EvalMod;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)
 VAR Class: Tree.tTree; 

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE EvalDefMod (t: Tree.tTree);
PROCEDURE EvalImplMod (t: Tree.tTree);
PROCEDURE EvalImplHead (t: Tree.tTree);
PROCEDURE GenEvaluator (t: Tree.tTree);

PROCEDURE BeginEvalMod;
PROCEDURE CloseEvalMod;

END EvalMod.
