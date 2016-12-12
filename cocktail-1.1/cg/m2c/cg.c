#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Memory
#include "Memory.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Tree2
#include "Tree2.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Order
#include "Order.h"
#endif

#ifndef DEFINITION_Dialog
#include "Dialog.h"
#endif

#ifndef DEFINITION_GramMod
#include "GramMod.h"
#endif

#ifndef DEFINITION_TreeMod1
#include "TreeMod1.h"
#endif

#ifndef DEFINITION_EvalMod
#include "EvalMod.h"
#endif

#ifndef DEFINITION_EvalMod2
#include "EvalMod2.h"
#endif

#ifndef DEFINITION_EvalMod3
#include "EvalMod3.h"
#endif

#ifndef DEFINITION_GramC
#include "GramC.h"
#endif

#ifndef DEFINITION_GramYacc
#include "GramYacc.h"
#endif

#ifndef DEFINITION_TreeC1
#include "TreeC1.h"
#endif

#ifndef DEFINITION_EvalC
#include "EvalC.h"
#endif

#ifndef DEFINITION_EvalC2
#include "EvalC2.h"
#endif

#ifndef DEFINITION_EvalC3
#include "EvalC3.h"
#endif

static CHAR DefExtMc [] = ".md";
static CHAR ImpExtMc [] = ".mi";
static CHAR LisExtMc [] = ".imp";
static CHAR DefExtC [] = ".h";
static CHAR ImpExtC [] = ".c";
static Strings_tString CgLib, DefFile, TreeFile, EvalFile, String, PathS;
static struct S_1 {
    CHAR A[255 + 1];
} Argument, PathA;
static SHORTCARD j;
static CHAR ch;
static Sets_tSet AllOptions;
static BOOLEAN HasArgs;
static void GenerateMacros ARGS(());
static void ReadTraceTab ARGS(());
static void SetTrace ARGS((Tree_tTree t));
static IO_tFile SmartOpen ARGS((Strings_tString FileName));
static void SmartClose ARGS((Strings_tString FileName, IO_tFile f));


static void GenerateMacros
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile TypeTabFile;
  Strings_tString s;
  Idents_tIdent i;
  INTEGER j;

  if (Sets_IsElement(ORD('c'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"TypeTab.c", 9L, &String);
  } else {
    Strings_ArrayToString((STRING)"TypeTab.m", 9L, &String);
  }
  Strings_Assign(&PathS, &CgLib);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 256L);
  TypeTabFile = IO_ReadOpen(PathA.A, 256L);
  Strings_ArrayToString((STRING)"yy", 2L, &PathS);
  Idents_GetString(Tree_iModule, &Tree_ModuleName);
  Strings_Concatenate(&PathS, &Tree_ModuleName);
  Strings_ArrayToString((STRING)".w", 2L, &String);
  Strings_Concatenate(&PathS, &String);
  Strings_Append(&PathS, '\0');
  Strings_StringToArray(&PathS, PathA.A, 256L);
  Tree_f = IO_WriteOpen(PathA.A, 256L);
  while (!IO_EndOfFile(TypeTabFile)) {
    Strings_ReadL(TypeTabFile, &s);
    i = Idents_MakeIdent(&s);
    if (i <= Semantics_TypeCount && Sets_IsElement((LONGCARD)i, &Tree_TypeNames)) {
      Sets_Exclude(&Tree_TypeNames, (LONGCARD)i);
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef close", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef read", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef write", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef get", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef put", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef copy", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      Strings_ReadL(TypeTabFile, &s);
      Strings_WriteL(Tree_f, &s);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else {
      for (j = 1; j <= 8; j += 1) {
        IO_ReadNl(TypeTabFile);
      }
    }
  }
  IO_ReadClose(TypeTabFile);
  if (Tree_itTree <= Semantics_TypeCount) {
    Sets_Exclude(&Tree_TypeNames, (LONGCARD)Tree_itTree);
  }
  while (!Sets_IsEmpty(Tree_TypeNames)) {
    i = Sets_Extract(&Tree_TypeNames);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef close", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define close", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef read", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define read", 13L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyReadHex ((unsigned char *) & a, sizeof (a));", 50L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef write", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define write", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyWriteHex ((unsigned char *) & a, sizeof (a));", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef get", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define get", 12L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyGet ((char *) & a, sizeof (a));", 37L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef put", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define put", 12L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyPut ((char *) & a, sizeof (a));", 37L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef copy", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define copy", 13L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)	memcmp ((char *) & a, (char *) & b, sizeof (a)) == 0", 59L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    } else {
      IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef close", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define close", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef read", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define read", 13L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyReadHex (a);", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef write", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define write", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyWriteHex (a);", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef get", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define get", 12L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyGet (a);", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef put", 12L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define put", 12L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a)	yyPut (a);", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef copy", 13L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define copy", 13L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
      Tree_WI(i);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
      Tree_WI(i);
      IO_WriteS(Tree_f, (STRING)"(a, b)	yyIsEqual (a, b)", 23L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
    }
  }
  if (Sets_IsElement(ORD('c'), &Tree_Options)) {
    IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	a = ", 8L);
    Tree_WI(Tree_iNoTree);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef close", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define close", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyChild = a; a = ", 21L);
    Tree_WI(Tree_iNoTree);
    IO_WriteS(Tree_f, (STRING)"; yyRelease", 11L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (yyChild);", 11L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef read", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define read", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyRead", 10L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef write", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define write", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyWrite", 11L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef get", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define get", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyGet", 9L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef put", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define put", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyPut", 9L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef copy", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define copy", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a, b)	yyCopy", 13L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (b, & a);", 10L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a, b)	IsEqual", 14L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
  } else {
    IO_WriteS(Tree_f, (STRING)"# ifndef begin", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define begin", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	a := ", 9L);
    Tree_WI(Tree_iNoTree);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef close", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define close", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyChild := a; a := ", 23L);
    Tree_WI(Tree_iNoTree);
    IO_WriteS(Tree_f, (STRING)"; yyRelease", 11L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (yyChild);", 11L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef read", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define read", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyRead", 10L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef write", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define write", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyWrite", 11L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef get", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define get", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyGet", 9L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef put", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define put", 12L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a)	yyPut", 9L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a);", 5L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef copy", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define copy", 13L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a, b)	yyCopy", 13L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (b, SYSTEM.ADR (a));", 21L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# ifndef equal", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# define equal", 14L);
    Tree_WI(Tree_itTree);
    IO_WriteS(Tree_f, (STRING)"(a, b)	IsEqual", 14L);
    Tree_WI(Tree_iModule);
    IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"# endif", 7L);
    IO_WriteNl(Tree_f);
  }
  IO_WriteClose(Tree_f);
}

static void ReadTraceTab
# ifdef __STDC__
()
# else
()
# endif
{
  IO_tFile TraceTabFile;
  Strings_tString s;
  Tree_tTree t;

  TraceTabFile = IO_ReadOpen((STRING)"TraceTab", 8L);
  if (TraceTabFile >= 0) {
    while (!IO_EndOfFile(TraceTabFile)) {
      Strings_ReadL(TraceTabFile, &s);
      t = Tree_IdentifyClass(Tree_TreeRoot->U_1.V_26.Ag.Classes, Idents_MakeIdent(&s));
      if (t != Tree_NoTree) {
        SetTrace(t);
        Tree_ForallClasses(t->U_1.V_5.Class.Extensions, (Tree_ProcOfT)SetTrace);
      }
    }
    IO_ReadClose(TraceTabFile);
  }
}

static void SetTrace
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  INCL(t->U_1.V_5.Class.Properties, Tree_Trace);
}

static IO_tFile SmartOpen
# ifdef __STDC__
(Strings_tString FileName)
# else
(FileName)
Strings_tString FileName;
# endif
{
  Strings_tString PathS;

  if (Sets_IsElement(ORD('7'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"yy", 2L, &PathS);
    Strings_Concatenate(&PathS, &FileName);
    Strings_Append(&PathS, '\0');
    Strings_StringToArray(&PathS, PathA.A, 256L);
  } else {
    Strings_Append(&FileName, '\0');
    Strings_StringToArray(&FileName, PathA.A, 256L);
  }
  return IO_WriteOpen(PathA.A, 256L);
}

static void SmartClose
# ifdef __STDC__
(Strings_tString FileName, IO_tFile f)
# else
(FileName, f)
Strings_tString FileName;
IO_tFile f;
# endif
{
  Strings_tString PathS;

  IO_WriteClose(f);
  if (Sets_IsElement(ORD('7'), &Tree_Options)) {
    Strings_ArrayToString((STRING)"gmdupd ", 7L, &PathS);
    Strings_Concatenate(&PathS, &FileName);
    Strings_ArrayToString((STRING)" yy", 3L, &String);
    Strings_Concatenate(&PathS, &String);
    Strings_Concatenate(&PathS, &FileName);
    Strings_Append(&PathS, '\0');
    Strings_StringToArray(&PathS, PathA.A, 256L);
    j = System(PathA.A, 256L);
  }
}

void BEGIN_MODULE()
{
  BEGIN_System();
  BEGIN_Memory();
  BEGIN_IO();
  BEGIN_Strings();
  BEGIN_Idents();
  BEGIN_Sets();
  BEGIN_Errors();
  BEGIN_Scanner();
  BEGIN_Parser();
  BEGIN_Tree();
  BEGIN_Tree2();
  BEGIN_Semantics();
  BEGIN_Order();
  BEGIN_Dialog();
  BEGIN_GramMod();
  BEGIN_TreeMod1();
  BEGIN_EvalMod();
  BEGIN_EvalMod2();
  BEGIN_EvalMod3();
  BEGIN_GramC();
  BEGIN_GramYacc();
  BEGIN_TreeC1();
  BEGIN_EvalC();
  BEGIN_EvalC2();
  BEGIN_EvalC3();

  Strings_AssignEmpty(&CgLib);
  Tree_SourceFile.A[0] = '\0';
  Scanner_ArgCount = GetArgCount() - 1;
  HasArgs = FALSE;
  Scanner_CurArg = 0;
  for (;;) {
    INC(Scanner_CurArg);
    if (Scanner_CurArg > Scanner_ArgCount) {
      goto EXIT_1;
    }
    GetArgument(Scanner_CurArg, Argument.A, 256L);
    if (Argument.A[0] == '-') {
      if (Argument.A[1] == 'l') {
        Strings_AssignEmpty(&CgLib);
        j = 2;
        for (;;) {
          ch = Argument.A[j];
          if (ch == '\0') {
            goto EXIT_2;
          }
          Strings_Append(&CgLib, ch);
          INC(j);
        } EXIT_2:;
        Strings_Append(&CgLib, '/');
      } else {
        j = 0;
        for (;;) {
          INC(j);
          ch = Argument.A[j];
          if (ch == '\0') {
            goto EXIT_3;
          } else if (ch == '?') {
            Sets_Include(&Tree_Options, ORD('h'));
            Sets_Include(&Tree_Options, ORD('H'));
          } else {
            Sets_Include(&Tree_Options, ORD(ch));
          }
        } EXIT_3:;
        HasArgs = TRUE;
      }
    } else if (Argument.A[0] == '?') {
      Sets_Include(&Tree_Options, ORD('h'));
      Sets_Include(&Tree_Options, ORD('H'));
      HasArgs = TRUE;
    } else {
      j = 0;
      do {
        ch = Argument.A[j];
        Tree_SourceFile.A[j] = ch;
        INC(j);
      } while (!(ch == '\0'));
      goto EXIT_1;
    }
  } EXIT_1:;
  if (!HasArgs) {
    Sets_Include(&Tree_Options, ORD('a'));
    Sets_Include(&Tree_Options, ORD('A'));
  }
  if (Sets_IsElement(ORD('a'), &Tree_Options)) {
    Sets_MakeSet(&AllOptions, 127L);
    for (ch = 'a'; ch <= 'z'; ch += 1) {
      Sets_Include(&AllOptions, ORD(ch));
    }
    Sets_Include(&AllOptions, ORD('F'));
    Sets_Include(&AllOptions, ORD('R'));
    Sets_Include(&AllOptions, ORD('='));
    Sets_Exclude(&AllOptions, ORD('c'));
    Sets_Exclude(&AllOptions, ORD('h'));
    Sets_Exclude(&AllOptions, ORD('u'));
    Sets_Exclude(&AllOptions, ORD('x'));
    Sets_Exclude(&AllOptions, ORD('z'));
    Sets_Union(&Tree_Options, AllOptions);
    Sets_ReleaseSet(&AllOptions);
  }
  if (Sets_IsElement(ORD('k'), &Tree_Options) || Sets_IsElement(ORD('q'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('o'));
  }
  if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('f'), &Tree_Options) || Sets_IsElement(ORD('k'), &Tree_Options) || Sets_IsElement(ORD('t'), &Tree_Options) || Sets_IsElement(ORD('b'), &Tree_Options) || Sets_IsElement(ORD('y'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD(','));
  }
  if (Sets_IsElement(ORD('w'), &Tree_Options) || Sets_IsElement(ORD('r'), &Tree_Options) || Sets_IsElement(ORD('p'), &Tree_Options) || Sets_IsElement(ORD('g'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD(';'));
  }
  if (Sets_IsElement(ORD('A'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('D'));
    Sets_Include(&Tree_Options, ORD('I'));
  }
  if (Sets_IsElement(ORD('T'), &Tree_Options) || Sets_IsElement(ORD('X'), &Tree_Options) || Sets_IsElement(ORD('Y'), &Tree_Options) || Sets_IsElement(ORD('Z'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('I'));
  }
  if (Sets_IsElement(ORD('I'), &Tree_Options) || Sets_IsElement(ORD('V'), &Tree_Options) || Sets_IsElement(ORD('M'), &Tree_Options) || Sets_IsElement(ORD('P'), &Tree_Options) || Sets_IsElement(ORD('S'), &Tree_Options) || Sets_IsElement(ORD('N'), &Tree_Options) || Sets_IsElement(ORD('O'), &Tree_Options) || Sets_IsElement(ORD('G'), &Tree_Options) || Sets_IsElement(ORD('E'), &Tree_Options) || Sets_IsElement(ORD('C'), &Tree_Options) || Sets_IsElement(ORD('J'), &Tree_Options) || Sets_IsElement(ORD('x'), &Tree_Options) || Sets_IsElement(ORD('z'), &Tree_Options) || Sets_IsElement(ORD('u'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('.'));
  }
  if (Sets_IsElement(ORD('x'), &Tree_Options) || Sets_IsElement(ORD('z'), &Tree_Options) || Sets_IsElement(ORD('u'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('B'));
  }
  if (Sets_IsElement(ORD('T'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('X'));
    Sets_Include(&Tree_Options, ORD('Z'));
  }
  if (Sets_IsElement(ORD('X'), &Tree_Options)) {
    Sets_Include(&Tree_Options, ORD('Y'));
  }
  if (Sets_IsElement(ORD('h'), &Tree_Options)) {
    Sets_Exclude(&Tree_Options, ORD('h'));
    Tree_f = IO_StdOutput;
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"usage: cg [-options] [-ldir] [files]", 36L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"options for tree/graph module", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" a generate all except -ch (default)", 36L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" n generate node constructors    procedures n<node> (node)", 58L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" m generate node constructors    procedures m<node> (make)", 58L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" f generate node/graph destroyer procedure ReleaseTREE (free)", 61L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" F generate general    destroyer procedure ReleaseTREEModule (FREE)", 67L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" o generate ascii  node  writer  procedure WriteTREENode (output)", 65L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" r generate ascii  graph reader  procedure ReadTREE", 51L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" w generate ascii  graph writer  procedure WriteTREE", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" g generate binary graph reader  procedure GetTREE", 50L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" p generate binary graph writer  procedure PutTREE", 50L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" R generate list reverser        procedure ReverseTREE", 54L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" t generate top down  traversal  procedure TraverseTREETD", 57L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" b generate bottom up traversal  procedure TraverseTREEBU", 57L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" y generate graph copy           procedure CopyTREE", 51L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" k generate graph checker        procedure CheckTREE", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" q generate graph browser        procedure QueryTREE", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" = generate tree equality test   procedure IsEqualTREE", 54L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" d generate definition     module", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" i generate implementation module", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" s generate import statements", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 4 generate tree/graph description in file TREE.TS", 50L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 6 generate # line directives", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 7 touch output files only if necessary", 39L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 8 report storage consumption", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" c generate C code (default is Modula-2)", 40L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" h print help information for tree/graph module", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" H print help information for evaluator  module", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" -ldir specify the directory dir where cg finds its tables", 58L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"options for scanner and parser interface", 40L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" x generate scanner specification", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" z generate parser  specification for lalr", 42L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" u generate parser  specification for yacc", 42L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" v omit actions in the generated parser specifications", 54L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" j allow undefined node types; define implicitly as terminals", 61L);
    IO_WriteNl(Tree_f);
  }
  if (Sets_IsElement(ORD('H'), &Tree_Options)) {
    Sets_Exclude(&Tree_Options, ORD('H'));
    Tree_f = IO_StdOutput;
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"usage: cg [-options] [-ldir] [files]", 36L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"options for evaluator module", 28L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" A generate all, same as -DI (default)", 38L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" D generate definition     module", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" I generate implementation module", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" L generate a (lazy) evaluator for WAG (default OAG)", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" W suppress warnings", 20L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" B allow missing attribute computations in extended node types", 62L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" V print visit sequences", 24L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" M print summary of all node types (rules) from source", 54L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" P print dependency relations DP", 32L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" S print dependency relations SNC", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" N print dependency relations DNC", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" O print dependency relations OAG", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" G print attribute instances sorted by declaration order", 56L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" E print attribute instances sorted by evaluation order", 55L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" C print dependencies introduced for total order", 48L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" T generate evaluator with trace output (all actions, T = XZ)", 61L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" U trace only node types specified in file TraceTab", 51L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" X trace attribute evaluation actions with    values", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" Y trace attribute evaluation actions without values", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" Z trace visit actions", 22L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" J start dialog system", 22L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" Q browse internal data structure", 33L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 0 optimize attribute storage", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 1 print inserted copy rules", 28L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 2 print inherited attribute computation rules", 46L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 3 print attribute storage assignment", 37L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 5 generate code to check for cyclic dependencies", 49L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 6 generate # line directives", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 7 touch output files only if necessary", 39L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 8 report storage consumption", 29L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" 9 generate code to measure stack size", 38L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" c generate C code (default is Modula-2)", 40L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" H print help information for evaluator  module", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" h print help information for tree/graph module", 47L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" -ldir specify the directory dir where cg finds its tables", 58L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)"implications", 12L);
    IO_WriteNl(Tree_f);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" {}              -> {a, A}", 26L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" a               -> {a-z, F, R} - {c, e, h, u, x, z}", 52L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" A               -> {D, I}", 26L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" {L, T, X, Y, Z} -> I", 21L);
    IO_WriteNl(Tree_f);
    IO_WriteS(Tree_f, (STRING)" T               -> {X, Z}", 26L);
    IO_WriteNl(Tree_f);
  }
  if (!Sets_IsEmpty(Tree_Options)) {
    Strings_ArrayToString(Scanner_ScanTabName.A, 128L, &String);
    Strings_Assign(&PathS, &CgLib);
    Strings_Concatenate(&PathS, &String);
    Strings_Append(&PathS, '\0');
    Strings_StringToArray(&PathS, Scanner_ScanTabName.A, 128L);
    Strings_ArrayToString(Parser_ParsTabName.A, 129L, &String);
    Strings_Assign(&PathS, &CgLib);
    Strings_Concatenate(&PathS, &String);
    Strings_Append(&PathS, '\0');
    Strings_StringToArray(&PathS, Parser_ParsTabName.A, 129L);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString((STRING)"int", 3L, &String);
    } else {
      Strings_ArrayToString((STRING)"INTEGER", 7L, &String);
    }
    Tree_iInteger = Idents_MakeIdent(&String);
    if (Tree_SourceFile.A[0] != '\0') {
      Scanner_BeginFile(Tree_SourceFile.A, 256L);
      Strings_ArrayToString(Tree_SourceFile.A, 256L, &String);
      Scanner_Attribute.Position.File = Idents_MakeIdent(&String);
    }
    Errors_StoreMessages(TRUE);
    Tree_ErrorCount = Parser_Parser();
    Tree_BeginTree2();
    Semantics_Semantics(Tree_TreeRoot);
    if (Tree_ErrorCount > 0) {
      Errors_WriteMessages((System_tFile)IO_StdError);
      IO_CloseIO();
      Exit(1L);
    }
  }
  if (Sets_IsElement(ORD('x'), &Tree_Options)) {
    if (Tree_TreeRoot->U_1.V_26.Ag.ScannerName == Idents_NoIdent) {
      Strings_ArrayToString((STRING)"Scanner", 7L, &PathS);
    } else {
      Idents_GetString(Tree_TreeRoot->U_1.V_26.Ag.ScannerName, &PathS);
    }
    Strings_ArrayToString((STRING)".rpp", 4L, &String);
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      GramC_ScanSpec(Tree_TreeRoot);
    } else {
      GramMod_ScanSpec(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('z'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Ag.ParserName, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    Strings_ArrayToString((STRING)".lalr", 5L, &String);
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      GramC_ParsSpec(Tree_TreeRoot);
    } else {
      GramMod_ParsSpec(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
  } else if (Sets_IsElement(ORD('u'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Ag.ParserName, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    Strings_ArrayToString((STRING)".y", 2L, &String);
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    GramYacc_ParsSpec(Tree_TreeRoot);
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('.'), &Tree_Options)) {
    Order_Order(Tree_TreeRoot);
  }
  Errors_WriteMessages((System_tFile)IO_StdError);
  Errors_StoreMessages(TRUE);
  if (Sets_IsElement(ORD('Q'), &Tree_Options)) {
    Tree_QueryTree(Tree_TreeRoot);
  }
  if (Sets_IsElement(ORD('J'), &Tree_Options)) {
    Dialog_Dialog(Tree_TreeRoot);
  }
  if (Tree_ErrorCount > 0) {
    IO_CloseIO();
    Exit(1L);
  }
  if (Sets_IsElement(ORD('i'), &Tree_Options) || Sets_IsElement(ORD('X'), &Tree_Options)) {
    GenerateMacros();
  }
  if (Sets_IsElement(ORD('d'), &Tree_Options)) {
    Idents_GetString(Tree_iModule, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(DefExtC, 2L, &String);
    } else {
      Strings_ArrayToString(DefExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Strings_Assign(&DefFile, &PathS);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      TreeC1_TreeDefC(Tree_TreeRoot);
    } else {
      TreeMod1_TreeDefMod(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
    if (!Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString((STRING)"gmdcpp ", 7L, &PathS);
      Strings_Concatenate(&PathS, &DefFile);
      Strings_Append(&PathS, '\0');
      Strings_StringToArray(&PathS, PathA.A, 256L);
      j = System(PathA.A, 256L);
    }
  }
  if (Sets_IsElement(ORD('4'), &Tree_Options)) {
    Idents_GetString(Tree_ViewName, &PathS);
    Strings_ArrayToString((STRING)".TS", 3L, &String);
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    Idents_WriteIdent(Tree_f, Tree_iModule);
    IO_WriteNl(Tree_f);
    Tree2_PutTree2(Tree_f, Tree_TreeRoot->U_1.V_26.Ag.Classes);
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('i'), &Tree_Options)) {
    Idents_GetString(Tree_iModule, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(ImpExtC, 2L, &String);
    } else {
      Strings_ArrayToString(ImpExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Strings_Assign(&TreeFile, &PathS);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      TreeC1_TreeImplC(Tree_TreeRoot);
    } else {
      TreeMod1_TreeImplMod(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
    if (!Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString((STRING)"gmdcpp ", 7L, &PathS);
      Strings_Concatenate(&PathS, &TreeFile);
      Strings_Append(&PathS, '\0');
      Strings_StringToArray(&PathS, PathA.A, 256L);
      j = System(PathA.A, 256L);
    }
  }
  if (Sets_IsElement(ORD('s'), &Tree_Options) && !Sets_IsElement(ORD('c'), &Tree_Options)) {
    Idents_GetString(Tree_iModule, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    Strings_ArrayToString(LisExtMc, 4L, &String);
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    TreeMod1_ImportList(Tree_TreeRoot);
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('U'), &Tree_Options)) {
    ReadTraceTab();
  } else if (!Sets_IsEmpty(Tree_Options)) {
    Tree_ForallClasses(Tree_TreeRoot->U_1.V_26.Ag.Classes, (Tree_ProcOfT)SetTrace);
  }
  if (Sets_IsElement(ORD('D'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Ag.EvalName, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(DefExtC, 2L, &String);
    } else {
      Strings_ArrayToString(DefExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      EvalC_EvalDefC(Tree_TreeRoot);
    } else {
      EvalMod_EvalDefMod(Tree_TreeRoot);
    }
    SmartClose(PathS, Tree_f);
  }
  if (Sets_IsElement(ORD('I'), &Tree_Options)) {
    Idents_GetString(Tree_TreeRoot->U_1.V_26.Ag.EvalName, &Tree_ModuleName);
    Strings_Assign(&PathS, &Tree_ModuleName);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString(ImpExtC, 2L, &String);
    } else {
      Strings_ArrayToString(ImpExtMc, 3L, &String);
    }
    Strings_Concatenate(&PathS, &String);
    Strings_Assign(&EvalFile, &PathS);
    Tree_f = SmartOpen(PathS);
    if (Sets_IsElement(ORD('c'), &Tree_Options)) {
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        EvalC3_EvalImplC(Tree_TreeRoot);
      } else if (Sets_IsElement(ORD('0'), &Tree_Options)) {
        EvalC2_EvalImplC(Tree_TreeRoot);
      } else {
        EvalC_EvalImplC(Tree_TreeRoot);
      }
    } else {
      if (Sets_IsElement(ORD('L'), &Tree_Options)) {
        EvalMod3_EvalImplMod(Tree_TreeRoot);
      } else if (Sets_IsElement(ORD('0'), &Tree_Options)) {
        EvalMod2_EvalImplMod(Tree_TreeRoot);
      } else {
        EvalMod_EvalImplMod(Tree_TreeRoot);
      }
    }
    SmartClose(PathS, Tree_f);
    if (!Sets_IsElement(ORD('c'), &Tree_Options)) {
      Strings_ArrayToString((STRING)"gmdcpp ", 7L, &PathS);
      Strings_Concatenate(&PathS, &EvalFile);
      Strings_Append(&PathS, '\0');
      Strings_StringToArray(&PathS, PathA.A, 256L);
      j = System(PathA.A, 256L);
    }
  }
  if (!Sets_IsElement(ORD('c'), &Tree_Options)) {
    if (Sets_IsElement(ORD('i'), &Tree_Options) || Sets_IsElement(ORD('X'), &Tree_Options)) {
      Strings_ArrayToString((STRING)"gmdrm yy", 8L, &PathS);
      Idents_GetString(Tree_iModule, &Tree_ModuleName);
      Strings_Concatenate(&PathS, &Tree_ModuleName);
      Strings_ArrayToString((STRING)".w", 2L, &String);
      Strings_Concatenate(&PathS, &String);
      Strings_Append(&PathS, '\0');
      Strings_StringToArray(&PathS, PathA.A, 256L);
      j = System(PathA.A, 256L);
    }
  }
  if (Sets_IsElement(ORD('8'), &Tree_Options)) {
    IO_WriteNl((System_tFile)IO_StdError);
    IO_WriteS((System_tFile)IO_StdError, (STRING)"Memory", 6L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Memory_MemoryUsed, 8L);
    IO_WriteS((System_tFile)IO_StdError, (STRING)"  Heap", 6L);
    IO_WriteI((System_tFile)IO_StdError, (LONGINT)Tree_HeapUsed, 8L);
    IO_WriteNl((System_tFile)IO_StdError);
  }
  Errors_WriteMessages((System_tFile)IO_StdError);
  IO_CloseIO();
  Exit(0L);
}
