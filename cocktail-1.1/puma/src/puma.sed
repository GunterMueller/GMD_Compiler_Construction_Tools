(* Ich, Doktor Josef Grosch, Informatiker, April 1991 *)

MODULE puma;

FROM System	IMPORT GetArgCount, GetArgument, System, Exit;
FROM Memory	IMPORT MemoryUsed;
FROM IO		IMPORT StdOutput, StdError, WriteOpen, WriteClose, CloseIO,
			WriteI, WriteS, WriteNl,
			tFile, ReadOpen, ReadClose, EndOfFile, ReadNl;
FROM Strings	IMPORT tString, AssignEmpty, Assign, Append, Concatenate,
			ReadL, WriteL, ArrayToString, StringToArray;
FROM Idents	IMPORT tIdent, MakeIdent, GetString, WriteIdent;
FROM Sets	IMPORT tSet, MakeSet, ReleaseSet, Include, Exclude, IsEmpty,
			Extract, Complement, Union, IsElement;
FROM Errors	IMPORT StoreMessages, WriteMessages;
FROM Scanner	IMPORT ScanTabName, BeginFile, ErrorI;
FROM Parser	IMPORT Parser, ParsTabName;
FROM Tree	IMPORT NoTree, tTree, TreeRoot, HeapUsed, Options, SourceFile, f,
			WI, mNoClass, TreeName, ErrorCount, Class, Child, Attribute, 
			ActionPart, NoClass, Test, Dummy, ForallClasses, ForallAttributes,
			QueryTree;
FROM Tree2	IMPORT GetTree2;
FROM Semantics	IMPORT Semantics, TypeCount, TypeNames, UserTypes, RemoveTreeTypes;
FROM Optimize	IMPORT Optimize, RuleProperties;
FROM Mod	IMPORT DefMod, ImplMod, MacroMod;
FROM C		IMPORT DefC, ImplC, MacroC;

CONST
   DefExtMc	= ".md"	;	(* file extensions for Modula (mc)	*)
   ImpExtMc	= ".mi"	;
   LisExtMc	= ".imp";

   DefExtC	= ".h"	;	(* file extensions for C		*)
   ImpExtC	= ".c"	;

VAR
   PumaLib	,
   TrafoFile	,
   String	,
   PathS	: tString;
   Argument	,
   PathA	: ARRAY [0..255] OF CHAR;
   i, j, n	: SHORTCARD;
   ch		: CHAR;
   Node		: tTree;

PROCEDURE SmartOpen (FileName: tString): tFile;
   VAR PathS: tString;
   BEGIN
      IF IsElement (ORD ('7'), Options) THEN
	 ArrayToString	("yy", PathS);
	 Concatenate	(PathS, FileName);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
      ELSE
	 Append		(FileName, 0C);
	 StringToArray	(FileName, PathA);
      END;
      RETURN WriteOpen	(PathA);
   END SmartOpen;

PROCEDURE SmartClose (FileName: tString; f: tFile);
   VAR PathS: tString;
   BEGIN
      WriteClose	(f);
      IF IsElement (ORD ('7'), Options) THEN
	 ArrayToString	("gmdupd ", PathS);
	 Concatenate	(PathS, FileName);
	 ArrayToString	(" yy", String);
	 Concatenate	(PathS, String);
	 Concatenate	(PathS, FileName);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
	 n := System	(PathA);
      END;
   END SmartClose;

PROCEDURE GenerateMacros;
   VAR TypeTabFile	: tFile;
   VAR s		: tString;
   VAR i		: tIdent;
   VAR j		: INTEGER;
   BEGIN
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	("TypeTab.c", String);	(* name of type table for C *)
   ELSE
      ArrayToString	("TypeTab.m", String);	(* name of type table for Modula *)
   END;
      Assign		(PathS, PumaLib);
      Concatenate 	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      TypeTabFile := ReadOpen (PathA);

      ArrayToString	("yy" , PathS);		(* name of macro file *)
      GetString		(TreeRoot^.Spec.TrafoName, String);
      Concatenate	(PathS, String);
      ArrayToString	(".w", String);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      f := WriteOpen (PathA);

      WHILE NOT EndOfFile (TypeTabFile) DO
	 ReadL (TypeTabFile, s);
	 i := MakeIdent (s);
	 IF (i <= TypeCount) AND IsElement (i, TypeNames) THEN
	    Exclude (TypeNames, i);
	    !# ifndef begin! WI (i); !!
	    ReadL (TypeTabFile, s); WriteL (f, s);
	    !# endif!
	    FOR j := 2 TO 7 DO ReadNl (TypeTabFile); END;
	    !# ifndef equal! WI (i); !!
	    ReadL (TypeTabFile, s); WriteL (f, s);
	    !# endif!
	 ELSE
	    FOR j := 1 TO 8 DO ReadNl (TypeTabFile); END;
	 END;
      END;
      ReadClose (TypeTabFile);
      RemoveTreeTypes (TreeRoot);

      WHILE NOT IsEmpty (TypeNames) DO
	 i := Extract (TypeNames);
	 Include (UserTypes, i);
   IF IsElement (ORD ('c'), Options) THEN
	 !# ifndef begin! WI (i); !!
	 !# define begin! WI (i); !(a)!
	 !# endif!
	 !# ifndef equal! WI (i); !!
	 !# define equal! WI (i); !(a, b)	memcmp ((char *) & a, (char *) & b, sizeof (a)) == 0!
	 !# endif!
   ELSE
	 !# ifndef begin! WI (i); !!
	 !# define begin! WI (i); !(a)!
	 !# endif!
	 !# ifndef equal! WI (i); !!
	 !# define equal! WI (i); !(a, b)	yyIsEqual (a, b)!
	 !# endif!
   END;
      END;

   IF IsElement (ORD ('c'), Options) THEN
      MacroC (TreeRoot);
   ELSE
      MacroMod (TreeRoot);
   END;

      WriteClose (f);
   END GenerateMacros;

VAR IndentLevel: INTEGER;

PROCEDURE WriteClass (t: tTree);
   VAR i: INTEGER;
   BEGIN
      CASE t^.Kind OF
      | Class	: WITH t^.Class DO
	    FOR i := 1 TO IndentLevel DO
	       WriteS	(StdOutput, "   ");
	    END;
	    WriteIdent	(StdOutput, Name);
	    WriteS	(StdOutput, "	=");
	    WriteClass	(Attributes);
	    IF Extensions^.Kind # NoClass THEN
	       WriteS	(StdOutput, " <");
	       WriteNl	(StdOutput);
	       INC (IndentLevel);
	       WriteClass (Extensions);
	       DEC (IndentLevel);
	       FOR i := 1 TO IndentLevel DO
		  WriteS (StdOutput, "   ");
	       END;
	       WriteS	(StdOutput, ">");
	    END;
	    WriteS	(StdOutput, " .");
	    WriteNl	(StdOutput);
	    WriteClass	(Next);
	 END;
      | Child	: WITH t^.Child DO
	    WriteS	(StdOutput, " ");
	    WriteIdent	(StdOutput, Name);
	    WriteS	(StdOutput, ": ");
	    WriteIdent	(StdOutput, Type);
	    WriteClass	(Next);
	 END;
      | Attribute	: WITH t^.Attribute DO
	 IF ({Test, Dummy} * Properties) = {} THEN
	    WriteS	(StdOutput, " [");
	    WriteIdent	(StdOutput, Name);
	    WriteS	(StdOutput, ": ");
	    WriteIdent	(StdOutput, Type);
	    WriteS	(StdOutput, "]");
	 END;
	    WriteClass	(Next);
	 END;
      | ActionPart	: WITH t^.ActionPart DO
	    WriteClass	(Next);
	 END;
      ELSE
      END;
   END WriteClass;

VAR IsFirst: BOOLEAN;

PROCEDURE WritePattern (t: tTree);
   BEGIN
      CASE t^.Kind OF
      | Class	: WITH t^.Class DO
	    WriteIdent	(StdOutput, Name);
	    WriteS	(StdOutput, " (");
	    IsFirst := TRUE;
	    ForallAttributes (t, WritePattern);
	    WriteS	(StdOutput, ")");
	    WriteNl	(StdOutput);
	 END;
      | Child	: WITH t^.Child DO
	    IF IsFirst THEN
	       IsFirst := FALSE;
	    ELSE
	       WriteS	(StdOutput, ", ");
	    END;
	    WriteIdent	(StdOutput, Name);
	    WriteS	(StdOutput, ":");
	    WriteIdent	(StdOutput, Type);
	 END;
      | Attribute	: WITH t^.Attribute DO
	 IF ({Test, Dummy} * Properties) = {} THEN
	    IF IsFirst THEN
	       IsFirst := FALSE;
	    ELSE
	       WriteS	(StdOutput, ", ");
	    END;
	    WriteIdent	(StdOutput, Name);
	 END;
	 END;
      ELSE
      END;
   END WritePattern;

BEGIN
   IndentLevel := 0;
   AssignEmpty (PumaLib);
   SourceFile [0] := 0C;
   n := GetArgCount () - 1;

   FOR i := 1 TO n DO
      GetArgument (i, Argument);
      IF Argument [0] = '-' THEN 
	 IF Argument [1] = 'l' THEN 
	    AssignEmpty (PumaLib);
	    j := 2;
	    LOOP
	       ch := Argument [j];
	       IF ch = 0C THEN EXIT; END;
	       Append (PumaLib, ch);
	       INC (j);
	    END;
	    Append (PumaLib, '/');
	    DEC (n);
	 ELSE
	    j := 0;
	    LOOP
	       INC (j);
	       ch := Argument [j];
	       IF ch = 0C THEN
		  EXIT;
	       ELSIF ch = '?' THEN
		  Include (Options, ORD ('h'));
	       ELSE
		  Include (Options, ORD (ch));
	       END;
	    END;
	 END;
      ELSIF Argument [0] = '?' THEN 
	 Include (Options, ORD ('h'));
      ELSE
	 j := 0;
	 REPEAT
            ch := Argument [j];
	    SourceFile [j] := ch;
	    INC (j);
	 UNTIL ch = 0C;
	 DEC (n);
      END;
   END;

   IF n < 1 THEN				(* {} -> a		*)
      Include (Options, ORD ('a'));
   END;

   IF IsElement (ORD ('a'), Options) THEN	(* a -> {d, i}		*)
      Include (Options, ORD ('d'));
      Include (Options, ORD ('i'));
   END;

   IF IsElement (ORD ('h'), Options) THEN
      Exclude (Options, ORD ('h'));
      f := StdOutput;
      !!
      !usage: puma [-options] [-ldir] [file]!
      !!
      ! a generate all, same as -di (default)!
      ! d generate definition     module!
      ! i generate implementation module!
      ! s suppress warnings!
      ! m use procedure MakeTREE to construct nodes (default is inline code)!
      ! p allow node constructors without parentheses!
      ! f signal a runtime error if none of the rules of a procedure matches!
      ! k allow non-linear patterns!
      ! n check parameters for NoTREE (NIL) and treat as failure (tg compatibility)!
      ! w surround actions by WITH statements (tg compatibility)!
      ! e treat undefined names as error!
      ! v treat undefined names as warning!
      ! o list undefined names on standard output!
      ! t print tree definitions!
      ! r print patterns!
      ! q browse internal data structure!
      ! 6 generate # line directives!
      ! 7 touch output files only if necessary!
      ! 8 report storage consumption!
      ! c generate C code (default is Modula-2)!
      ! h print help information!
      ! -ldir specify the directory dir where puma finds its tables!
      !!
   END;

   IF IsEmpty (Options) THEN CloseIO; HALT; END;

      ArrayToString	(ScanTabName, String);	(* name of scanner table *)
      Assign		(PathS, PumaLib);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, ScanTabName);

      ArrayToString	(ParsTabName, String);	(* name of parser table *)
      Assign		(PathS, PumaLib);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, ParsTabName);

      StoreMessages (TRUE);
      IF SourceFile [0] # 0C THEN BeginFile (SourceFile); END;
      INC (ErrorCount, Parser ());

      Node := TreeRoot^.Spec.TreeNames;
      WHILE Node^.Kind = TreeName DO
	 GetString	(Node^.TreeName.Name, PathS);
	 ArrayToString	(".TS", String);
	 Concatenate	(PathS, String);
	 Append		(PathS, 0C);
	 StringToArray	(PathS, PathA);
	 f := ReadOpen	(PathA);
	 IF f >= 0 THEN
	    ReadL (f, String); Node^.TreeName.Name := MakeIdent (String);
	    Node^.TreeName.Classes := GetTree2 (f);
	    ReadClose	(f);
   IF IsElement (ORD ('t'), Options) THEN
	    WriteS (StdOutput, "Tree Definition: "); WriteIdent (StdOutput, Node^.TreeName.Name);
	    WriteNl (StdOutput);
	    WriteS (StdOutput, "----------------"); WriteNl (StdOutput);
	    WriteNl (StdOutput);
	    WriteClass (Node^.TreeName.Classes);
	    WriteNl (StdOutput);
   END;
   IF IsElement (ORD ('r'), Options) THEN
	    WriteS (StdOutput, "Patterns: "); WriteIdent (StdOutput, Node^.TreeName.Name);
	    WriteNl (StdOutput);
	    WriteS (StdOutput, "---------"); WriteNl (StdOutput);
	    WriteNl (StdOutput);
	    ForallClasses (Node^.TreeName.Classes, WritePattern);
	    WriteNl (StdOutput);
   END;
	 ELSE
	    Node^.TreeName.Classes := mNoClass ();
	    ErrorI ("cannot read view file", Node^.TreeName.Pos, Node^.TreeName.Name);
	 END;
	 Node := Node^.TreeName.Next;
      END;

      Semantics	(TreeRoot);
   IF IsElement (ORD ('b'), Options) THEN
      RuleProperties	(TreeRoot);
   ELSE
      Optimize		(TreeRoot);
   END;

      WriteMessages (StdError);

   IF IsElement (ORD ('q'), Options) THEN
      QueryTree		(TreeRoot);
   END;

      IF ErrorCount > 0 THEN CloseIO; Exit (1); END;
      GenerateMacros;

   IF IsElement (ORD ('d'), Options) THEN
      GetString		(TreeRoot^.Spec.TrafoName, PathS);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(DefExtC , String);
   ELSE
      ArrayToString	(DefExtMc, String);
   END;
      Concatenate	(PathS, String);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      DefC		(TreeRoot);
   ELSE
      DefMod		(TreeRoot);
   END;
      SmartClose	(PathS, f);
   END;

   IF IsElement (ORD ('i'), Options) THEN
      GetString		(TreeRoot^.Spec.TrafoName, PathS);
   IF IsElement (ORD ('c'), Options) THEN
      ArrayToString	(ImpExtC , String);
   ELSE
      ArrayToString	(ImpExtMc, String);
   END;
      Concatenate	(PathS, String);
      Assign		(TrafoFile, PathS);
      f := SmartOpen	(PathS);
   IF IsElement (ORD ('c'), Options) THEN
      ImplC		(TreeRoot);
   ELSE
      ImplMod		(TreeRoot);
   END;
      SmartClose	(PathS, f);

   IF NOT IsElement (ORD ('c'), Options) THEN
      ArrayToString	("gmdcpp ", PathS);		(* call cpp *)
      Concatenate	(PathS, TrafoFile);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      n := System	(PathA);

      ArrayToString	("gmdrm yy" , PathS);		(* name of macro file *)
      GetString		(TreeRoot^.Spec.TrafoName, String);
      Concatenate	(PathS, String);
      ArrayToString	(".w", String);
      Concatenate	(PathS, String);
      Append		(PathS, 0C);
      StringToArray	(PathS, PathA);
      n := System	(PathA);
   END;
   END;

   IF IsElement (ORD ('8'), Options) THEN
      WriteNl (StdError);
      WriteS  (StdError, "Memory"); WriteI (StdError, MemoryUsed, 8);
      WriteS  (StdError, "  Heap"); WriteI (StdError, HeapUsed  , 8);
      WriteNl (StdError);
   END;
   CloseIO; Exit (0);
END puma.
