DEFINITION MODULE Order;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

VAR IndexToClass: POINTER TO ARRAY [0 .. 10000] OF Tree.tTree;


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE Order (t: Tree.tTree);
PROCEDURE WriteOrderDecl (t: Tree.tTree);
PROCEDURE WriteOrderEval (t: Tree.tTree);
PROCEDURE WriteVisitSequence (t: Tree.tTree);

PROCEDURE BeginOrder;
PROCEDURE CloseOrder;

END Order.
