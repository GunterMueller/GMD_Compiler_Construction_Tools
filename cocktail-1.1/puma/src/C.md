DEFINITION MODULE C;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE DefC (t: Tree.tTree);
PROCEDURE ImplC (t: Tree.tTree);
PROCEDURE MacroC (t: Tree.tTree);

PROCEDURE BeginC;
PROCEDURE CloseC;

END C.
