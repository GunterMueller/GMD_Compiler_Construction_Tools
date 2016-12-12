#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Mod
#include "Mod.h"
#endif

IO_tFile Mod_yyf;
PROC Mod_Exit;

#define kProcedure	0
#define kFunction	1
#define kPredicate	2
static unsigned char RoutineKind;
static CARDINAL i, j;
static INTEGER ListCount;
static Tree_tTree rule, TheClass, InFormals, OutFormals, ReturnFormals, Decls;
static Idents_tIdent TheName;
static BOOLEAN TemposDone;
static void WriteLine ARGS((Positions_tPosition Line));
static void Match ARGS((Tree_tTree t, Tree_tTree Formals));
static void MatchExprs ARGS((Tree_tTree t));
static void MatchExpr ARGS((Tree_tTree t));
static void AssignTempos ARGS((Tree_tTree t));
static void AssignTempo ARGS((Tree_tTree t));
static void AssignFormals ARGS((Tree_tTree t, Tree_tTree Formals));
static void AssignFormal ARGS((Tree_tTree t, Tree_tTree Formals));
static void BeginFormals ARGS((Tree_tTree Formals));
static INTEGER ConsPatterns ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER ConsTempos ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER Expressions ARGS((Tree_tTree t, INTEGER ListCount));
static void Expression ARGS((Tree_tTree t));
static void Tg2 ARGS((Tree_tTree t, Tree_tTree Formals));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        char dummy;
    } U_1;
};
struct S_4 {
    union {
        char dummy;
    } U_1;
};
struct S_5 {
    union {
        struct {
            struct S_6 {
                Tree_tTree Var;
            } yyR14;
        } V_1;
    } U_1;
};
static void Declare ARGS((Tree_tTree t));
struct S_7 {
    union {
        struct {
            struct S_8 {
                Tree_tTree Var;
            } yyR2;
        } V_1;
    } U_1;
};
static void Tg1 ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void Tg3 ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim2 ARGS((Tree_tTree OneTest, Tree_tTree yyP1));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim ARGS((Tree_tTree t));
struct S_12 {
    union {
        char dummy;
    } U_1;
};
static void Case ARGS((Tree_tTree t));
struct S_13 {
    union {
        struct {
            struct S_14 {
                CARDINAL n;
            } yyR1;
        } V_1;
    } U_1;
};
static void yyExit ARGS(());


static void WriteLine
# ifdef __STDC__
(Positions_tPosition Line)
# else
(Line)
Positions_tPosition Line;
# endif
{
  if (Line.Line != 0) {
    IO_WriteS(Tree_f, (STRING)"(* line ", 8L);
    Tree_WN((LONGINT)Line.Line);
    IO_WriteS(Tree_f, (STRING)" \"", 2L);
    IO_WriteS(Tree_f, Tree_SourceFile.A, 256L);
    IO_WriteS(Tree_f, (STRING)"\" *)", 4L);
    IO_WriteNl(Tree_f);
  }
}

static void Match
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Idents_tIdent TreeName;
  Tree_tTree Pattern;

  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  Pattern = t->U_1.V_45.OnePattern.Pattern;
  switch (Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_1 = &Pattern->U_1.V_50.Decompose;

      TreeName = W_1->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      if (Formals->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind == Tree_UserType || Sets_IsNotEqual(W_1->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.Types, Formals->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.Types)) {
        if (W_1->Object->U_1.V_5.Class.Extensions->U_1.V_1.Kind == Tree_NoClass) {
          IO_WriteS(Tree_f, (STRING)"      IF (", 10L);
          Mod_ImplMod(W_1->Path);
          IO_WriteS(Tree_f, (STRING)"^.Kind # ", 9L);
        } else {
          IO_WriteS(Tree_f, (STRING)"      IF NOT ", 13L);
          Tree_WI(TreeName);
          IO_WriteS(Tree_f, (STRING)".IsType (", 9L);
          Mod_ImplMod(W_1->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
        }
        Tree_WI(TreeName);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)") THEN EXIT; END;", 17L);
        IO_WriteNl(Tree_f);
      }
      Match(W_1->Patterns, W_1->Object->U_1.V_5.Class.Formals);
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_2 = &Pattern->U_1.V_51.VarDef;

      if (W_2->Object != Tree_NoTree) {
        {
          register Tree_yFormal *W_3 = &W_2->Object->U_1.V_86.Formal;

          IO_WriteS(Tree_f, (STRING)"      IF NOT (equal", 19L);
          Mod_ImplMod(W_3->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          Mod_ImplMod(W_3->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
          Mod_ImplMod(Pattern->U_1.V_51.VarDef.Path);
          IO_WriteS(Tree_f, (STRING)")) THEN EXIT; END;", 18L);
          IO_WriteNl(Tree_f);
        }
      }
    }
    break;
  case Tree_NilTest:;
    IO_WriteS(Tree_f, (STRING)"      IF ", 9L);
    Mod_ImplMod(Pattern->U_1.V_52.NilTest.Path);
    IO_WriteS(Tree_f, (STRING)" # NIL THEN EXIT; END;", 22L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1:;
    break;
  case Tree_DontCare:;
    return;
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_4 = &Pattern->U_1.V_55.Value;

      AssignTempo(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)"      IF NOT (equal", 19L);
      Mod_ImplMod(Formals->U_1.V_86.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_ImplMod(W_4->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_4->Expr);
      IO_WriteS(Tree_f, (STRING)")) THEN EXIT; END;", 18L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_4->Expr);
    }
    break;
  }
  Match(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_86.Formal.Next);
}

static void MatchExprs
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return;
  }
  if (t->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind == Tree_DontCare) {
    return;
  }
  MatchExpr(t->U_1.V_58.OneExpr.Expr);
  MatchExprs(t->U_1.V_58.OneExpr.Next);
}

static void MatchExpr
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    MatchExprs(t->U_1.V_61.Compose.Exprs);
    break;
  case Tree_VarUse:;
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1:;
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_5 = &t->U_1.V_65.Call;

      MatchExpr(W_5->Expr);
      MatchExprs(W_5->Exprs);
      if (W_5->Object != Tree_NoTree) {
        Match(W_5->Patterns, W_5->Object->U_1.V_32.Routine.OutForm);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_6 = &t->U_1.V_66.Binary;

      MatchExpr(W_6->Lop);
      MatchExpr(W_6->Rop);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    MatchExpr(t->U_1.V_67.PreOperator.Expr);
    break;
  case Tree_Index:;
    MatchExpr(t->U_1.V_69.Index.Expr);
    MatchExprs(t->U_1.V_69.Index.Exprs);
    break;
  case Tree_Parents:;
    MatchExpr(t->U_1.V_70.Parents.Expr);
    break;
  }
}

static void AssignTempos
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return;
  }
  if (t->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind == Tree_DontCare) {
    return;
  }
  AssignTempo(t->U_1.V_58.OneExpr.Expr);
  AssignTempos(t->U_1.V_58.OneExpr.Next);
}

static void AssignTempo
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Idents_tIdent TreeName;

  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    {
      register Tree_yCompose *W_7 = &t->U_1.V_61.Compose;

      TreeName = W_7->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      IO_WriteS(Tree_f, (STRING)"      yyALLOC (", 15L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",Make", 5L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_7->Tempo);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_7->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      if (W_7->Exprs->U_1.V_1.Kind == Tree_OneExpr && W_7->Exprs->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind != Tree_DontCare) {
        IO_WriteS(Tree_f, (STRING)"      WITH ", 11L);
        Tree_WI(W_7->Tempo);
        IO_WriteS(Tree_f, (STRING)"^.", 2L);
        Tree_WI(W_7->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        AssignFormals(W_7->Exprs, W_7->Object->U_1.V_5.Class.Formals);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
      }
    }
    break;
  case Tree_VarUse:;
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1:;
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_8 = &t->U_1.V_65.Call;

      AssignTempo(W_8->Expr);
      AssignTempos(W_8->Exprs);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_9 = &t->U_1.V_66.Binary;

      AssignTempo(W_9->Lop);
      AssignTempo(W_9->Rop);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    AssignTempo(t->U_1.V_67.PreOperator.Expr);
    break;
  case Tree_Index:;
    AssignTempo(t->U_1.V_69.Index.Expr);
    AssignTempos(t->U_1.V_69.Index.Exprs);
    break;
  case Tree_Parents:;
    AssignTempo(t->U_1.V_70.Parents.Expr);
    break;
  }
}

static void AssignFormals
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr || Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind == Tree_DontCare) {
    BeginFormals(Formals);
    return;
  }
  AssignFormal(t->U_1.V_58.OneExpr.Expr, Formals);
  AssignFormals(t->U_1.V_58.OneExpr.Next, Formals->U_1.V_86.Formal.Next);
}

static void AssignFormal
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Idents_tIdent TreeName;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_10 = &t->U_1.V_61.Compose;

      TreeName = W_10->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      IO_WriteS(Tree_f, (STRING)"      yyALLOC (", 15L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",Make", 5L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(Formals->U_1.V_86.Formal.Name);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      if (W_10->Exprs->U_1.V_1.Kind == Tree_OneExpr && W_10->Exprs->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind != Tree_DontCare) {
        IO_WriteS(Tree_f, (STRING)"      WITH ", 11L);
        Tree_WI(Formals->U_1.V_86.Formal.Name);
        IO_WriteS(Tree_f, (STRING)"^.", 2L);
        Tree_WI(W_10->Object->U_1.V_5.Class.Name);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
        AssignFormals(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals);
        IO_WriteS(Tree_f, (STRING)"      END;", 10L);
        IO_WriteNl(Tree_f);
      }
    }
  } else {
    AssignTempo(t);
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_VarUse:;
  case Tree_Nil:;
  case Tree_Call:;
  case Tree_Binary:;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
  case Tree_Index:;
  case Tree_Parents:;
  case Tree_TargetExpr:;
  case Tree_StringExpr:;
  case Tree_AttrDesc:;
    IO_WriteS(Tree_f, (STRING)"      ", 6L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" := ", 4L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1:;
    IO_WriteS(Tree_f, (STRING)"      begin", 11L);
    Mod_ImplMod(Formals->U_1.V_86.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" (", 2L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    IO_WriteNl(Tree_f);
    break;
  default :
    break;
  }
}

static void BeginFormals
# ifdef __STDC__
(Tree_tTree Formals)
# else
(Formals)
Tree_tTree Formals;
# endif
{
  if (Formals->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_11 = &Formals->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)"      begin", 11L);
      Mod_ImplMod(W_11->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Tree_WI(W_11->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      BeginFormals(W_11->Next);
    }
  }
}

static INTEGER ConsPatterns
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    return ListCount;
  }
  {
    register Tree_yOnePattern *W_12 = &t->U_1.V_45.OnePattern;

    if (W_12->Pattern->U_1.V_1.Kind == Tree_DontCare) {
      return ConsTempos(W_12->Pattern->U_1.V_54.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Tree_WI(W_12->Pattern->U_1.V_49.Pattern.Tempo);
      return ConsPatterns(W_12->Next, ListCount + 1);
    }
  }
}

static INTEGER ConsTempos
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Formal) {
    if (ListCount > 0) {
      IO_WriteS(Tree_f, (STRING)", ", 2L);
    }
    Tree_WI(t->U_1.V_86.Formal.Name);
    return ConsTempos(t->U_1.V_86.Formal.Next, ListCount + 1);
  } else {
    return ListCount;
  }
}

static INTEGER Expressions
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount)
# else
(t, ListCount)
Tree_tTree t;
INTEGER ListCount;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return ListCount;
  }
  {
    register Tree_yOneExpr *W_13 = &t->U_1.V_58.OneExpr;

    if (W_13->Expr->U_1.V_1.Kind == Tree_DontCare) {
      return ConsTempos(W_13->Expr->U_1.V_54.DontCare.Tempos, ListCount);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Expression(W_13->Expr);
      return Expressions(W_13->Next, ListCount + 1);
    }
  }
}

static void Expression
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    Tree_WI(t->U_1.V_61.Compose.Tempo);
    break;
  case Tree_Nil:;
    IO_WriteS(Tree_f, (STRING)"NIL", 3L);
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_14 = &t->U_1.V_62.VarUse;

      if (W_14->Object != Tree_NoTree) {
        Mod_ImplMod(W_14->Object->U_1.V_86.Formal.Path);
      } else {
        Tree_WI(W_14->Name);
      }
    }
    break;
  case Tree_DontCare1:;
    Tree_WI(t->U_1.V_53.DontCare1.Tempo);
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_15 = &t->U_1.V_65.Call;

      Expression(W_15->Expr);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      ListCount = Expressions(W_15->Exprs, 0L);
      if (W_15->Object != Tree_NoTree) {
        ListCount = ConsPatterns(W_15->Patterns, ListCount);
      } else {
        ListCount = Expressions(W_15->Patterns, ListCount);
      }
      IO_WriteS(Tree_f, (STRING)")", 1L);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_16 = &t->U_1.V_66.Binary;

      Expression(W_16->Lop);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_16->Operator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Expression(W_16->Rop);
    }
    break;
  case Tree_PreOperator:;
    Tree_WI(t->U_1.V_67.PreOperator.Operator);
    IO_WriteS(Tree_f, (STRING)" ", 1L);
    Expression(t->U_1.V_67.PreOperator.Expr);
    break;
  case Tree_PostOperator:;
    Expression(t->U_1.V_68.PostOperator.Expr);
    IO_WriteS(Tree_f, (STRING)" ", 1L);
    Tree_WI(t->U_1.V_68.PostOperator.Operator);
    break;
  case Tree_Index:;
    Expression(t->U_1.V_69.Index.Expr);
    IO_WriteS(Tree_f, (STRING)" [", 2L);
    ListCount = Expressions(t->U_1.V_69.Index.Exprs, 0L);
    IO_WriteS(Tree_f, (STRING)"]", 1L);
    break;
  case Tree_Parents:;
    IO_WriteS(Tree_f, (STRING)"(", 1L);
    Expression(t->U_1.V_70.Parents.Expr);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    break;
  case Tree_TargetExpr:;
    Mod_ImplMod(t->U_1.V_71.TargetExpr.Expr);
    break;
  case Tree_StringExpr:;
    StringMem_WriteString(Tree_f, t->U_1.V_72.StringExpr.String);
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_17 = &t->U_1.V_63.AttrDesc;

      Mod_ImplMod(W_17->Object->U_1.V_86.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_17->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_17->Attribute);
    }
    break;
  }
}

static void Tg2
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoPattern || Formals->U_1.V_1.Kind == Tree_NoFormal) {
    return;
  }
  switch (t->U_1.V_45.OnePattern.Pattern->U_1.V_1.Kind) {
  case Tree_Decompose:;
    IO_WriteS(Tree_f, (STRING)"     WITH ", 10L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)"^.", 2L);
    Tree_WI(t->U_1.V_45.OnePattern.Pattern->U_1.V_50.Decompose.Object->U_1.V_5.Class.Name);
    IO_WriteS(Tree_f, (STRING)" DO", 3L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_VarDef:;
  case Tree_NilTest:;
  case Tree_Value:;
  case Tree_DontCare1:;
    break;
  default :
    return;
    break;
  }
  Tg2(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_86.Formal.Next);
}

static void yyAbort
# ifdef __STDC__
(CHAR yyFunction[], LONGCARD O_1)
# else
(yyFunction, O_1)
CHAR yyFunction[];
LONGCARD O_1;
# endif
{
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_1 * sizeof(CHAR), 1)
  COPY_OPEN_ARRAY(yyFunction, O_1, CHAR)
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Mod, routine ", 27L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Mod_Exit)();
  FREE_OPEN_ARRAYS
}

static BOOLEAN yyIsEqual
# ifdef __STDC__
(BYTE yya[], LONGCARD O_3, BYTE yyb[], LONGCARD O_2)
# else
(yya, O_3, yyb, O_2)
BYTE yya[];
LONGCARD O_3;
BYTE yyb[];
LONGCARD O_2;
# endif
{
  INTEGER yyi;
  OPEN_ARRAY_LOCALS

  ALLOC_OPEN_ARRAYS(O_2 * sizeof(WORD) + O_3 * sizeof(WORD), 2)
  COPY_OPEN_ARRAY(yyb, O_2, WORD)
  COPY_OPEN_ARRAY(yya, O_3, WORD)
  {
    LONGINT B_1 = 0, B_2 = (INTEGER)(O_3 - 1);

    if (B_1 <= B_2)
      for (yyi = B_1;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_2) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Mod_MacroMod
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_3 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Spec) {
    {
      register Tree_ySpec *W_18 = &t->U_1.V_26.Spec;

      Mod_MacroMod(W_18->TreeNames);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_19 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"# define begint", 15L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)"(a)	a := NIL;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equalt", 15L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)"(a, b)	", 7L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)".IsEqual", 8L);
      Tree_WI(W_19->Name);
      IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
      IO_WriteNl(Tree_f);
      Mod_MacroMod(W_19->Next);
      return;
    }
  }
}

void Mod_DefMod
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_4 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Spec) {
    {
      register Tree_ySpec *W_20 = &t->U_1.V_26.Spec;

      IO_WriteS(Tree_f, (STRING)"DEFINITION MODULE ", 18L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, IO", 17L);
      Mod_DefMod(W_20->TreeNames);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Import);
      WriteLine(W_20->Codes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_20->Codes->U_1.V_12.Codes.Export);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR yyf	: IO.tFile;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"VAR Exit	: PROC;", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Mod_DefMod(W_20->Public);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_20->TrafoName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_21 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_21->Name);
      Mod_DefMod(W_21->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_22 = &t->U_1.V_25.Name;

      if (W_22->Object != Tree_NoTree) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
        Tree_WI(W_22->Name);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        Mod_DefMod(W_22->Object->U_1.V_32.Routine.InForm);
        Mod_DefMod(W_22->Object->U_1.V_32.Routine.OutForm);
        IO_WriteS(Tree_f, (STRING)")", 1L);
        if (W_22->Object->U_1.V_1.Kind == Tree_Predicate) {
          IO_WriteS(Tree_f, (STRING)": BOOLEAN", 9L);
        } else if (W_22->Object->U_1.V_1.Kind == Tree_Function) {
          IO_WriteS(Tree_f, (STRING)": ", 2L);
          Mod_DefMod(W_22->Object->U_1.V_34.Function.ReturnForm->U_1.V_86.Formal.TypeDesc);
        }
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Mod_DefMod(W_22->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_23 = &t->U_1.V_86.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)"; ", 2L);
      }
      if (W_23->Path->U_1.V_92.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)"VAR ", 4L);
      }
      Tree_WI(W_23->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      Mod_DefMod(W_23->TypeDesc);
      INC(ListCount);
      Mod_DefMod(W_23->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_24 = &t->U_1.V_89.NodeTypes;

      Tree_WI(W_24->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".t", 2L);
      Tree_WI(W_24->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_UserType) {
    {
      register Tree_yUserType *W_25 = &t->U_1.V_90.UserType;

      Tree_WI(W_25->Type);
      return;
    }
  }
}

void Mod_ImplMod
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Spec:;
    {
      register Tree_ySpec *W_26 = &t->U_1.V_26.Spec;

      IO_WriteS(Tree_f, (STRING)"IMPLEMENTATION MODULE ", 22L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('m'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyInline", 17L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"# ifdef yyInline", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, make, ptr, kind) \\", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr := tree.yyPoolFreePtr; \\", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IF SYSTEM.ADDRESS (ptr) >= tree.yyPoolMaxPtr THEN ptr := tree.yyAlloc (); END; \\", 82L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  INC (tree.yyPoolFreePtr, tree.yyNodeSize [tree.kind]); \\", 58L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr^.yyHead.yyMark := 0; \\", 28L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr^.Kind := tree.kind;", 25L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, make, ptr, kind) ptr := tree.make (tree.kind);", 69L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWrite(s) IO.WriteS (yyf, s)", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWriteNl IO.WriteNl (yyf)", 35L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"IMPORT SYSTEM, System, IO", 25L);
      Mod_DefMod(W_26->TreeNames);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_26->Codes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_26->Codes->U_1.V_12.Codes.Global);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyAbort (yyFunction: ARRAY OF CHAR);", 46L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, 'Error: module ", 41L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)", routine ');", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, yyFunction);", 38L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteS (IO.StdError, ' failed');", 37L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.WriteNl (IO.StdError);", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  Exit;", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyAbort;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyIsEqual (yya, yyb: ARRAY OF SYSTEM.BYTE): BOOLEAN;", 62L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" VAR yyi	: INTEGER;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  FOR yyi := 0 TO INTEGER (HIGH (yya)) DO", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"   IF yya [yyi] # yyb [yyi] THEN RETURN FALSE; END;", 51L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  END;", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  RETURN TRUE;", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyIsEqual;", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_26->Routines);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Begin", 15L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      WriteLine(W_26->Codes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_26->Codes->U_1.V_12.Codes.Begin);
      IO_WriteS(Tree_f, (STRING)" END Begin", 10L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE Close", 15L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      WriteLine(W_26->Codes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_26->Codes->U_1.V_12.Codes.Close);
      IO_WriteS(Tree_f, (STRING)" END Close", 10L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"PROCEDURE yyExit;", 17L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  IO.CloseIO; System.Exit (1);", 30L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" END yyExit;", 12L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"BEGIN", 5L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" yyf	:= IO.StdOutput;", 21L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Exit	:= yyExit;", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" Begin", 6L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"END ", 4L);
      Tree_WI(W_26->TrafoName);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_27 = &t->U_1.V_33.Procedure;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_27->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_DefMod(W_27->InForm);
      Mod_DefMod(W_27->OutForm);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      WriteLine(W_27->LocalLine);
      Texts_WriteText(Tree_f, W_27->Local);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kProcedure;
      InFormals = W_27->InForm;
      OutFormals = W_27->OutForm;
      Declare(W_27->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_27->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Mod_ImplMod(W_27->Rules);
        if (Sets_IsElement(ORD('f'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_27->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_27->Decisions);
        if (Sets_IsElement(ORD('f'), &Tree_Options) && !Optimize_NeedsNoFinale(W_27->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_27->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_27->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_27->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_28 = &t->U_1.V_34.Function;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_28->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_DefMod(W_28->InForm);
      Mod_DefMod(W_28->OutForm);
      IO_WriteS(Tree_f, (STRING)"): ", 3L);
      Mod_DefMod(W_28->ReturnForm->U_1.V_86.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_28->LocalLine);
      Texts_WriteText(Tree_f, W_28->Local);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kFunction;
      InFormals = W_28->InForm;
      OutFormals = W_28->OutForm;
      ReturnFormals = W_28->ReturnForm;
      Declare(W_28->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Mod_ImplMod(W_28->Rules);
        IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
        Tree_WI(W_28->Name);
        IO_WriteS(Tree_f, (STRING)"');", 3L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_28->Decisions);
        if (!Optimize_NeedsNoFinale(W_28->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  yyAbort ('", 12L);
          Tree_WI(W_28->Name);
          IO_WriteS(Tree_f, (STRING)"');", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_28->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_28->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_29 = &t->U_1.V_35.Predicate;

      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"PROCEDURE ", 10L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_DefMod(W_29->InForm);
      Mod_DefMod(W_29->OutForm);
      IO_WriteS(Tree_f, (STRING)"): BOOLEAN;", 11L);
      IO_WriteNl(Tree_f);
      WriteLine(W_29->LocalLine);
      Texts_WriteText(Tree_f, W_29->Local);
      IO_WriteS(Tree_f, (STRING)" VAR yyTempo: RECORD CASE : INTEGER OF", 38L);
      IO_WriteNl(Tree_f);
      RoutineKind = kPredicate;
      InFormals = W_29->InForm;
      OutFormals = W_29->OutForm;
      Declare(W_29->Rules);
      IO_WriteS(Tree_f, (STRING)" END; END;", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" BEGIN", 6L);
      IO_WriteNl(Tree_f);
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_29->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        Mod_ImplMod(W_29->Rules);
        IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_29->Decisions);
        if (!Optimize_NeedsNoFinale(W_29->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  RETURN FALSE;", 15L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)" END ", 5L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_29->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_30 = &t->U_1.V_42.Rule;

      WriteLine(W_30->Line);
      if (W_30->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
        Tree_WN((LONGINT)W_30->Index);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
      }
      IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
      IO_WriteNl(Tree_f);
      Decls = W_30->VarDecls;
      Match(W_30->Patterns, InFormals);
      if (Sets_IsElement(ORD('w'), &Tree_Options) && W_30->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        Tg2(W_30->Patterns, InFormals);
      }
      Mod_ImplMod(W_30->Statements);
      if (!W_30->HasRejectOrFail) {
        AssignFormals(W_30->Exprs, OutFormals);
        MatchExprs(W_30->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_30->Expr);
          if (W_30->HasPatterns && W_30->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            IO_WriteS(Tree_f, (STRING)"      ", 6L);
            Tree_WI(W_30->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_30->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_30->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Tree_WI(W_30->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_30->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Expression(W_30->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"      RETURN TRUE;", 18L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) && W_30->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        Tg3(W_30->Patterns);
      }
      IO_WriteS(Tree_f, (STRING)"   END;", 7L);
      IO_WriteNl(Tree_f);
      if (W_30->HasTempos) {
        IO_WriteS(Tree_f, (STRING)"    END;", 8L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_30->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_31 = &t->U_1.V_76.ProcCall;

      WriteLine(W_31->Pos);
      AssignTempo(W_31->Call);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Expression(W_31->Call);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_31->Call);
      Mod_ImplMod(W_31->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_32 = &t->U_1.V_77.Condition;

      WriteLine(W_32->Pos);
      AssignTempo(W_32->Expr);
      IO_WriteS(Tree_f, (STRING)"      IF NOT (", 14L);
      Expression(W_32->Expr);
      IO_WriteS(Tree_f, (STRING)") THEN EXIT; END;", 17L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_32->Expr);
      Mod_ImplMod(W_32->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_33 = &t->U_1.V_78.Assignment;

      WriteLine(W_33->Pos);
      AssignTempo(W_33->Adr);
      AssignTempo(W_33->Expr);
      if (W_33->Object != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Mod_ImplMod(W_33->Object->U_1.V_86.Formal.Path);
      } else {
        IO_WriteS(Tree_f, (STRING)"      ", 6L);
        Expression(W_33->Adr);
      }
      IO_WriteS(Tree_f, (STRING)" := ", 4L);
      Expression(W_33->Expr);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_33->Adr);
      MatchExpr(W_33->Expr);
      Mod_ImplMod(W_33->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_34 = &t->U_1.V_79.Reject;

      WriteLine(W_34->Pos);
      IO_WriteS(Tree_f, (STRING)"      EXIT;", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_35 = &t->U_1.V_80.Fail;

      WriteLine(W_35->Pos);
      IO_WriteS(Tree_f, (STRING)"      RETURN", 12L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE", 6L);
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_36 = &t->U_1.V_81.TargetStmt;

      WriteLine(W_36->Pos);
      IO_WriteS(Tree_f, (STRING)"      ", 6L);
      Mod_ImplMod(W_36->Stmt);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_36->Next);
      return;
    }
    break;
  case Tree_Nl:;
    {
      register Tree_yNl *W_37 = &t->U_1.V_82.Nl;

      WriteLine(W_37->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWriteNl;", 16L);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_37->Next);
      return;
    }
    break;
  case Tree_WriteStr:;
    {
      register Tree_yWriteStr *W_38 = &t->U_1.V_83.WriteStr;

      WriteLine(W_38->Pos);
      IO_WriteS(Tree_f, (STRING)"      yyWrite (", 15L);
      StringMem_WriteString(Tree_f, W_38->String);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      Mod_ImplMod(W_38->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register struct S_6 *W_39 = &yyTempo.U_1.V_1.yyR14;

      {
        register Tree_yIdent *W_40 = &t->U_1.V_16.Ident;

        W_39->Var = Semantics_IdentifyVar(Decls, W_40->Attribute);
        if (W_39->Var != Tree_NoTree) {
          Mod_ImplMod(W_39->Var->U_1.V_86.Formal.Path);
        } else {
          Tree_WI(W_40->Attribute);
        }
        Mod_ImplMod(W_40->Next);
        return;
      }
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_41 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_41->Code);
      Mod_ImplMod(W_41->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_42 = &t->U_1.V_19.Anys;

      Mod_ImplMod(W_42->Layouts);
      Mod_ImplMod(W_42->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_43 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_43->Code);
      Mod_ImplMod(W_43->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_44 = &t->U_1.V_15.Designator;

      Mod_ImplMod(W_44->Object->U_1.V_86.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_44->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_44->Attribute);
      Mod_ImplMod(W_44->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_45 = &t->U_1.V_94.Field;

      Mod_ImplMod(W_45->Next);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_45->Name);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_46 = &t->U_1.V_93.ConsType;

      Mod_ImplMod(W_46->Next);
      IO_WriteS(Tree_f, (STRING)"^.", 2L);
      Tree_WI(W_46->Name);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_47 = &t->U_1.V_92.Var;

      Tree_WI(W_47->Name);
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_48 = &t->U_1.V_89.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_48->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_49 = &t->U_1.V_90.UserType;

      Tree_WI(W_49->Type);
      return;
    }
    break;
  default :
    break;
  }
}

static void Declare
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_7 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Formal:;
    {
      register Tree_yFormal *W_50 = &t->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      Tree_WI(W_50->Name);
      IO_WriteS(Tree_f, (STRING)": ", 2L);
      Mod_DefMod(W_50->TypeDesc);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Declare(W_50->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register struct S_8 *W_51 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yParam *W_52 = &t->U_1.V_38.Param;

        W_51->Var = Semantics_IdentifyVar(Decls, W_52->Name);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_52->Name);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Mod_DefMod(W_51->Var->U_1.V_86.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        Declare(W_52->Next);
        return;
      }
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_53 = &t->U_1.V_42.Rule;

      if (W_53->HasTempos) {
        IO_WriteS(Tree_f, (STRING)" | ", 3L);
        Tree_WN((LONGINT)W_53->Index);
        IO_WriteS(Tree_f, (STRING)": yyR", 5L);
        Tree_WN((LONGINT)W_53->Index);
        IO_WriteS(Tree_f, (STRING)": RECORD", 8L);
        IO_WriteNl(Tree_f);
        Decls = W_53->VarDecls;
        Declare(W_53->Patterns);
        Declare(W_53->Exprs);
        if (RoutineKind == kFunction) {
          Declare(W_53->Expr);
          if (W_53->HasPatterns && W_53->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            IO_WriteS(Tree_f, (STRING)"  ", 2L);
            Tree_WI(W_53->Tempo);
            IO_WriteS(Tree_f, (STRING)": ", 2L);
            Mod_DefMod(ReturnFormals->U_1.V_86.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
        }
        Declare(W_53->Statements);
        IO_WriteS(Tree_f, (STRING)"  END;", 6L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_53->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_54 = &t->U_1.V_76.ProcCall;

      Declare(W_54->Call);
      Declare(W_54->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_55 = &t->U_1.V_77.Condition;

      Declare(W_55->Expr);
      Declare(W_55->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_56 = &t->U_1.V_78.Assignment;

      Declare(W_56->Adr);
      Declare(W_56->Expr);
      Declare(W_56->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_57 = &t->U_1.V_81.TargetStmt;

      Declare(W_57->Parameters);
      Declare(W_57->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_58 = &t->U_1.V_75.Statement;

      Declare(W_58->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_59 = &t->U_1.V_45.OnePattern;

      if (W_59->Pattern->U_1.V_49.Pattern.Tempo != Idents_NoIdent && W_59->Pattern->U_1.V_1.Kind != Tree_DontCare1) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_59->Pattern->U_1.V_49.Pattern.Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Mod_DefMod(W_59->Pattern->U_1.V_49.Pattern.TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_59->Pattern);
      Declare(W_59->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_60 = &t->U_1.V_58.OneExpr;

      Declare(W_60->Expr);
      Declare(W_60->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_61 = &t->U_1.V_50.Decompose;

      Declare(W_61->Patterns);
      return;
    }
    break;
  case Tree_DontCare:;
    {
      register Tree_yDontCare *W_62 = &t->U_1.V_54.DontCare;

      Declare(W_62->Tempos);
      return;
    }
    break;
  case Tree_DontCare1:;
    {
      register Tree_yDontCare1 *W_63 = &t->U_1.V_53.DontCare1;

      if (W_63->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_63->Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Mod_DefMod(W_63->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_64 = &t->U_1.V_55.Value;

      Declare(W_64->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_65 = &t->U_1.V_61.Compose;

      if (W_65->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        Tree_WI(W_65->Tempo);
        IO_WriteS(Tree_f, (STRING)": ", 2L);
        Mod_DefMod(W_65->TypeDesc);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_65->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_66 = &t->U_1.V_65.Call;

      Declare(W_66->Expr);
      Declare(W_66->Exprs);
      Declare(W_66->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_67 = &t->U_1.V_66.Binary;

      Declare(W_67->Lop);
      Declare(W_67->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_68 = &t->U_1.V_67.PreOperator;

      Declare(W_68->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_69 = &t->U_1.V_68.PostOperator;

      Declare(W_69->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_70 = &t->U_1.V_70.Parents;

      Declare(W_70->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_71 = &t->U_1.V_69.Index;

      Declare(W_71->Expr);
      Declare(W_71->Exprs);
      return;
    }
    break;
  default :
    break;
  }
}

static void Tg1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_9 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_72 = &t->U_1.V_86.Formal;

      TheName = W_72->Name;
      Tg1(W_72->TypeDesc);
      Tg1(W_72->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_73 = &t->U_1.V_89.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Tree_WI(TheName);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(W_73->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".No", 3L);
      Tree_WI(W_73->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)" THEN RETURN", 12L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" FALSE", 6L);
      }
      IO_WriteS(Tree_f, (STRING)"; END;", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void Tg3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_10 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_OnePattern) {
    {
      register Tree_yOnePattern *W_74 = &t->U_1.V_45.OnePattern;

      Tg3(W_74->Pattern);
      Tg3(W_74->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Decompose) {
    {
      register Tree_yDecompose *W_75 = &t->U_1.V_50.Decompose;

      IO_WriteS(Tree_f, (STRING)"     END;", 9L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void CommonTestElim2
# ifdef __STDC__
(Tree_tTree OneTest, Tree_tTree yyP1)
# else
(OneTest, yyP1)
Tree_tTree OneTest;
Tree_tTree yyP1;
# endif
{
  struct S_11 yyTempo;

  if (OneTest == Tree_NoTree) {
    return;
  }
  if (yyP1 == Tree_NoTree) {
    return;
  }
  if (OneTest->U_1.V_1.Kind == Tree_TestValue) {
    for (;;) {
      {
        register Tree_yTestValue *W_76 = &OneTest->U_1.V_102.TestValue;

        if (!Optimize_NeedsMatch(W_76->Expr)) {
          goto EXIT_1;
        }
        CommonTestElim(OneTest);
        IO_WriteS(Tree_f, (STRING)"    LOOP", 8L);
        IO_WriteNl(Tree_f);
        MatchExpr(OneTest->U_1.V_102.TestValue.Expr);
        CommonTestElim(yyP1);
        IO_WriteS(Tree_f, (STRING)"    EXIT; END;", 14L);
        IO_WriteNl(Tree_f);
        return;
      }
    } EXIT_1:;
  }
  CommonTestElim(OneTest);
  CommonTestElim(yyP1);
  return;
}

static void CommonTestElim
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_12 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register Tree_yDecision *W_77 = &t->U_1.V_105.Decision;

      if (W_77->Cases == 0) {
        if (!TemposDone && W_77->OneTest->U_1.V_1.Kind == Tree_TestValue && Optimize_NeedsTempo(W_77->Then, &rule)) {
          IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
          Tree_WN((LONGINT)rule->U_1.V_42.Rule.Index);
          IO_WriteS(Tree_f, (STRING)" DO", 3L);
          IO_WriteNl(Tree_f);
          TemposDone = TRUE;
          CommonTestElim2(W_77->OneTest, W_77->Then);
          IO_WriteS(Tree_f, (STRING)"  END;", 6L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)"    END;", 8L);
          IO_WriteNl(Tree_f);
        } else {
          Optimize_GetRule(W_77->Then, &rule);
          Decls = rule->U_1.V_42.Rule.VarDecls;
          CommonTestElim2(W_77->OneTest, W_77->Then);
          IO_WriteS(Tree_f, (STRING)"  END;", 6L);
          IO_WriteNl(Tree_f);
        }
        TemposDone = FALSE;
        CommonTestElim(W_77->Else);
      } else {
        i = W_77->Cases;
        Case(t);
      }
      return;
    }
    break;
  case Tree_Decided:;
    {
      register Tree_yDecided *W_78 = &t->U_1.V_106.Decided;

      CommonTestElim(W_78->Rule);
      if (W_78->Rule->U_1.V_42.Rule.HasExit) {
        TemposDone = FALSE;
        CommonTestElim(W_78->Else);
      }
      return;
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_79 = &t->U_1.V_98.TestKind;

      IO_WriteS(Tree_f, (STRING)"  IF (", 6L);
      Mod_ImplMod(W_79->Path);
      IO_WriteS(Tree_f, (STRING)"^.Kind = ", 9L);
      Tree_WI(W_79->TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_79->Name);
      IO_WriteS(Tree_f, (STRING)") THEN", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_80 = &t->U_1.V_99.TestIsType;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Tree_WI(W_80->TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".IsType (", 9L);
      Mod_ImplMod(W_80->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Tree_WI(W_80->TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_80->Name);
      IO_WriteS(Tree_f, (STRING)") THEN", 6L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNil:;
    {
      register Tree_yTestNil *W_81 = &t->U_1.V_100.TestNil;

      IO_WriteS(Tree_f, (STRING)"  IF ", 5L);
      Mod_ImplMod(W_81->Path);
      IO_WriteS(Tree_f, (STRING)" = NIL THEN", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNonlin:;
    {
      register Tree_yTestNonlin *W_82 = &t->U_1.V_101.TestNonlin;

      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      Mod_ImplMod(W_82->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_ImplMod(W_82->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Mod_ImplMod(W_82->Path2);
      IO_WriteS(Tree_f, (STRING)")) THEN", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestValue:;
    {
      register Tree_yTestValue *W_83 = &t->U_1.V_102.TestValue;

      AssignTempo(W_83->Expr);
      IO_WriteS(Tree_f, (STRING)"  IF (equal", 11L);
      Mod_ImplMod(W_83->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Mod_ImplMod(W_83->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_83->Expr);
      IO_WriteS(Tree_f, (STRING)")) THEN", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_84 = &t->U_1.V_42.Rule;

      WriteLine(W_84->Line);
      if (W_84->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    WITH yyTempo.yyR", 20L);
        Tree_WN((LONGINT)W_84->Index);
        IO_WriteS(Tree_f, (STRING)" DO", 3L);
        IO_WriteNl(Tree_f);
      }
      if (W_84->HasExit) {
        IO_WriteS(Tree_f, (STRING)"   LOOP", 7L);
        IO_WriteNl(Tree_f);
      }
      Decls = W_84->VarDecls;
      if (Sets_IsElement(ORD('w'), &Tree_Options) && W_84->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        Tg2(W_84->Patterns, InFormals);
      }
      Mod_ImplMod(W_84->Statements);
      if (!W_84->HasRejectOrFail) {
        AssignFormals(W_84->Exprs, OutFormals);
        MatchExprs(W_84->Exprs);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"      RETURN;", 13L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          AssignTempo(W_84->Expr);
          if (W_84->HasPatterns && W_84->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            IO_WriteS(Tree_f, (STRING)"      ", 6L);
            Tree_WI(W_84->Tempo);
            IO_WriteS(Tree_f, (STRING)" := ", 4L);
            Expression(W_84->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_84->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Tree_WI(W_84->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          } else {
            MatchExpr(W_84->Expr);
            IO_WriteS(Tree_f, (STRING)"      RETURN ", 13L);
            Expression(W_84->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"      RETURN TRUE;", 18L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (Sets_IsElement(ORD('w'), &Tree_Options) && W_84->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        Tg3(W_84->Patterns);
      }
      if (W_84->HasExit) {
        IO_WriteS(Tree_f, (STRING)"   END;", 7L);
        IO_WriteNl(Tree_f);
      }
      if (W_84->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)"    END;", 8L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  default :
    break;
  }
}

static void Case
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Decision) {
    {
      register struct S_14 *W_85 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_86 = &t->U_1.V_105.Decision;

        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  CASE ", 7L);
        Mod_ImplMod(W_86->OneTest->U_1.V_97.OneTest.Path);
        IO_WriteS(Tree_f, (STRING)"^.Kind OF", 9L);
        IO_WriteNl(Tree_f);
        W_85->n = i;
        while (W_85->n > 0) {
          if (!Sets_IsEmpty(t->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types)) {
            Case(t->U_1.V_105.Decision.OneTest);
            CommonTestElim(t->U_1.V_105.Decision.Then);
          }
          t = t->U_1.V_105.Decision.Else;
          DEC(W_85->n);
        }
        IO_WriteS(Tree_f, (STRING)"  ELSE END;", 11L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        CommonTestElim(t);
        return;
      }
    }
  }
  if (t->U_1.V_1.Kind == Tree_TestKind) {
    {
      register Tree_yTestKind *W_87 = &t->U_1.V_98.TestKind;

      IO_WriteS(Tree_f, (STRING)"  | ", 4L);
      Tree_WI(W_87->TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_87->Name);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TestIsType) {
    {
      register Tree_yTestIsType *W_88 = &t->U_1.V_99.TestIsType;

      {
        register Tree_yNodeTypes *W_89 = &W_88->TypeDesc->U_1.V_89.NodeTypes;

        TheClass = Semantics_LookupClass(W_89->TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&W_89->Types));
        IO_WriteS(Tree_f, (STRING)"  | ", 4L);
        Tree_WI(W_89->TreeName->U_1.V_29.TreeName.Name);
        IO_WriteS(Tree_f, (STRING)".", 1L);
        Tree_WI(TheClass->U_1.V_5.Class.Name);
        Case(W_88->TypeDesc);
        IO_WriteS(Tree_f, (STRING)":", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_90 = &t->U_1.V_89.NodeTypes;

      {
        LONGCARD B_3 = Sets_Minimum(&W_90->Types) + 1, B_4 = Sets_Maximum(&W_90->Types);

        if (B_3 <= B_4)
          for (j = B_3;; j += 1) {
            if (Sets_IsElement(j, &W_90->Types)) {
              TheClass = Semantics_LookupClass(W_90->TreeName->U_1.V_29.TreeName.Classes, j);
              IO_WriteNl(Tree_f);
              IO_WriteS(Tree_f, (STRING)"  , ", 4L);
              Tree_WI(W_90->TreeName->U_1.V_29.TreeName.Name);
              IO_WriteS(Tree_f, (STRING)".", 1L);
              Tree_WI(TheClass->U_1.V_5.Class.Name);
            }
            if (j >= B_4) break;
          }
      }
      return;
    }
  }
}

void Mod_BeginMod
# ifdef __STDC__
()
# else
()
# endif
{
}

void Mod_CloseMod
# ifdef __STDC__
()
# else
()
# endif
{
}

static void yyExit
# ifdef __STDC__
()
# else
()
# endif
{
  IO_CloseIO();
  Exit(1L);
}

void BEGIN_Mod()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_System();
    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_Positions();
    BEGIN_IO();
    BEGIN_StringMem();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Sets();
    BEGIN_Semantics();
    BEGIN_Optimize();
    BEGIN_Tree();

    Mod_yyf = IO_StdOutput;
    Mod_Exit = yyExit;
    Mod_BeginMod();
  }
}
