DEFINITION MODULE GramC;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE ParsSpec (t: Tree.tTree);
PROCEDURE ScanSpec (t: Tree.tTree);

PROCEDURE BeginGramC;
PROCEDURE CloseGramC;

END GramC.
