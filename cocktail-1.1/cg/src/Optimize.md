DEFINITION MODULE Optimize;

IMPORT SYSTEM, IO, Tree;
(* line 7 "" *)

VAR
   ChildrenDyn	,
   ChildrenIn	,
   AttributeIn	,
   AttributeOut	,
   AttributeTree,
   AttributeParam,
   AttributeVar	,
   AttributeDemand,
   AttributeStack: SHORTCARD;


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE LifeTime1 (t: Tree.tTree);
PROCEDURE LifeTime3 (t: Tree.tTree);

PROCEDURE BeginOptimize;
PROCEDURE CloseOptimize;

END Optimize.
