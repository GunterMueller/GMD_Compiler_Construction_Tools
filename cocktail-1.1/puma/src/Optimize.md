DEFINITION MODULE Optimize;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE Optimize (t: Tree.tTree);
PROCEDURE RuleProperties (yyP1: Tree.tTree);
PROCEDURE NeedsTempo (yyP5: Tree.tTree; VAR yyP6: Tree.tTree): BOOLEAN;
PROCEDURE NeedsMatch (yyP2: Tree.tTree): BOOLEAN;
PROCEDURE NeedsNoFinale (yyP7: Tree.tTree): BOOLEAN;
PROCEDURE GetRule (yyP8: Tree.tTree; VAR yyP9: Tree.tTree);

PROCEDURE BeginOptimize;
PROCEDURE CloseOptimize;

END Optimize.
