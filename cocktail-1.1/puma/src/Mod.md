DEFINITION MODULE Mod;

IMPORT SYSTEM, IO, Tree;

VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE DefMod (t: Tree.tTree);
PROCEDURE ImplMod (t: Tree.tTree);
PROCEDURE MacroMod (t: Tree.tTree);

PROCEDURE BeginMod;
PROCEDURE CloseMod;

END Mod.
