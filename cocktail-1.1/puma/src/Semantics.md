DEFINITION MODULE Semantics;

IMPORT SYSTEM, IO, Tree;
(* line 5 "sem.puma" *)

FROM Idents	IMPORT tIdent;
FROM Sets	IMPORT tSet;
FROM Tree	IMPORT tTree;

VAR TypeCount	: SHORTCARD;
VAR TypeNames, UserTypes	: tSet;

PROCEDURE IdentifyVar	(node: tTree; i: tIdent): tTree;
PROCEDURE LookupClass	(Classes: tTree; i: CARDINAL): tTree;


VAR yyf	: IO.tFile;
VAR Exit	: PROC;

PROCEDURE Semantics (t: Tree.tTree);
PROCEDURE RemoveTreeTypes (t: Tree.tTree);

PROCEDURE BeginSemantics;
PROCEDURE CloseSemantics;

END Semantics.
