DEFINITION MODULE GramYacc;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE ParsSpec (t: Tree.tTree);

PROCEDURE BeginGramYacc;
PROCEDURE CloseGramYacc;

END GramYacc.
