DEFINITION MODULE GramMod;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE ParsSpec (t: Tree.tTree);
PROCEDURE ScanSpec (t: Tree.tTree);

PROCEDURE BeginGramMod;
PROCEDURE CloseGramMod;

END GramMod.
