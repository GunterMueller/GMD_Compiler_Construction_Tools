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

#ifndef DEFINITION_Strings
#include "Strings.h"
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

#ifndef DEFINITION_C
#include "C.h"
#endif

IO_tFile C_yyf;
PROC C_Exit;

#define kProcedure	0
#define kFunction	1
#define kPredicate	2
static unsigned char RoutineKind;
static INTEGER WithCount, RuleCount, ListCount;
static CARDINAL i, j;
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
static void AssignSubFormals ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static void AssignSubFormal ARGS((Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static void BeginFormals ARGS((Tree_tTree Formals));
static void BeginSubFormals ARGS((Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer));
static INTEGER ConsPatterns ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER ConsTempos ARGS((Tree_tTree t, INTEGER ListCount, BOOLEAN IsRef));
static INTEGER Expressions ARGS((Tree_tTree t, INTEGER ListCount));
static INTEGER Expressions2 ARGS((Tree_tTree t, INTEGER ListCount, Tree_tTree Formals));
static void Expression ARGS((Tree_tTree t));
static Idents_tIdent MakeWith ARGS(());
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
static void Forward ARGS((Tree_tTree t));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void ProcHead1 ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void ProcHead2 ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void ProcHead3 ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
struct S_9 {
    union {
        struct {
            struct S_10 {
                Tree_tTree Var;
            } yyR14;
        } V_1;
    } U_1;
};
static void Declare ARGS((Tree_tTree t));
struct S_11 {
    union {
        struct {
            struct S_12 {
                Tree_tTree Var;
            } yyR2;
        } V_1;
    } U_1;
};
static void Tg1 ARGS((Tree_tTree t));
struct S_13 {
    union {
        char dummy;
    } U_1;
};
static void CommonTestElim ARGS((Tree_tTree t));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void Case ARGS((Tree_tTree t));
struct S_15 {
    union {
        struct {
            struct S_16 {
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
    if (Sets_IsElement(ORD('6'), &Tree_Options)) {
      IO_WriteS(Tree_f, (STRING)"# line ", 7L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" \"", 2L);
      IO_WriteS(Tree_f, Tree_SourceFile.A, 256L);
      IO_WriteS(Tree_f, (STRING)"\"", 1L);
      IO_WriteNl(Tree_f);
    } else {
      IO_WriteS(Tree_f, (STRING)"/* line ", 8L);
      Tree_WN((LONGINT)Line.Line);
      IO_WriteS(Tree_f, (STRING)" \"", 2L);
      IO_WriteS(Tree_f, Tree_SourceFile.A, 256L);
      IO_WriteS(Tree_f, (STRING)"\" */", 4L);
      IO_WriteNl(Tree_f);
    }
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
          IO_WriteS(Tree_f, (STRING)"   if (", 7L);
          C_ImplC(W_1->Path);
          IO_WriteS(Tree_f, (STRING)"->Kind != k", 11L);
          Tree_WI(W_1->Object->U_1.V_5.Class.Name);
        } else {
          IO_WriteS(Tree_f, (STRING)"   if (! ", 9L);
          Tree_WI(TreeName);
          IO_WriteS(Tree_f, (STRING)"_IsType (", 9L);
          C_ImplC(W_1->Path);
          IO_WriteS(Tree_f, (STRING)", k", 3L);
          Tree_WI(W_1->Object->U_1.V_5.Class.Name);
          IO_WriteS(Tree_f, (STRING)")", 1L);
        }
        IO_WriteS(Tree_f, (STRING)") goto yyL", 10L);
        Tree_WN(RuleCount);
        IO_WriteS(Tree_f, (STRING)";", 1L);
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

          IO_WriteS(Tree_f, (STRING)"   if (! (equal", 15L);
          C_DefC(W_3->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          C_ImplC(W_3->Path);
          IO_WriteS(Tree_f, (STRING)", ", 2L);
          C_ImplC(Pattern->U_1.V_51.VarDef.Path);
          IO_WriteS(Tree_f, (STRING)"))) goto yyL", 12L);
          Tree_WN(RuleCount);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
        }
      }
    }
    break;
  case Tree_NilTest:;
    IO_WriteS(Tree_f, (STRING)"   if (", 7L);
    C_ImplC(Pattern->U_1.V_52.NilTest.Path);
    IO_WriteS(Tree_f, (STRING)" != NULL) goto yyL", 18L);
    Tree_WN(RuleCount);
    IO_WriteS(Tree_f, (STRING)";", 1L);
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
      if (Formals->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind == Tree_UserType && Sets_IsElement((LONGCARD)Formals->U_1.V_86.Formal.TypeDesc->U_1.V_90.UserType.Type, &Semantics_UserTypes)) {
        IO_WriteS(Tree_f, (STRING)"  {", 3L);
        C_DefC(Formals->U_1.V_86.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" yyT; yyT = ", 12L);
        Expression(W_4->Expr);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"   if (! (equal", 15L);
        C_DefC(Formals->U_1.V_86.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        C_ImplC(W_4->Path);
        IO_WriteS(Tree_f, (STRING)", yyT))) goto yyL", 17L);
        Tree_WN(RuleCount);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
      } else {
        IO_WriteS(Tree_f, (STRING)"   if (! (equal", 15L);
        C_DefC(Formals->U_1.V_86.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" (", 2L);
        C_ImplC(W_4->Path);
        IO_WriteS(Tree_f, (STRING)", ", 2L);
        Expression(W_4->Expr);
        IO_WriteS(Tree_f, (STRING)"))) goto yyL", 12L);
        Tree_WN(RuleCount);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
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
      IO_WriteS(Tree_f, (STRING)"   yyALLOC (t", 13L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolFreePtr,", 13L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr,", 12L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_Alloc,", 7L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_NodeSize,Make", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(W_7->Tempo);
      IO_WriteS(Tree_f, (STRING)",k", 2L);
      Tree_WI(W_7->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_7->Exprs, W_7->Object->U_1.V_5.Class.Formals, W_7->Tempo, W_7->Object->U_1.V_5.Class.Name);
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
  MatchExpr(t->U_1.V_58.OneExpr.Expr);
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
  Idents_tIdent TreeName, With;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_10 = &t->U_1.V_61.Compose;

      TreeName = W_10->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      With = MakeWith();
      IO_WriteS(Tree_f, (STRING)"   {register t", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    yyALLOC (t", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolFreePtr,", 13L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr,", 12L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_Alloc,", 7L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_NodeSize,Make", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)",k", 2L);
      Tree_WI(W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    * ", 6L);
      Tree_WI(Formals->U_1.V_86.Formal.Name);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals, With, W_10->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)"   }", 4L);
      IO_WriteNl(Tree_f);
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
    IO_WriteS(Tree_f, (STRING)"   * ", 5L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" = ", 3L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1:;
    IO_WriteS(Tree_f, (STRING)"    begin", 9L);
    C_DefC(Formals->U_1.V_86.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" (* ", 4L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)")", 1L);
    IO_WriteNl(Tree_f);
    break;
  default :
    break;
  }
}

static void AssignSubFormals
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(t, Formals, PrevWith, Composer)
Tree_tTree t, Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr || Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_58.OneExpr.Expr->U_1.V_1.Kind == Tree_DontCare) {
    BeginSubFormals(Formals, PrevWith, Composer);
    return;
  }
  AssignSubFormal(t->U_1.V_58.OneExpr.Expr, Formals, PrevWith, Composer);
  AssignSubFormals(t->U_1.V_58.OneExpr.Next, Formals->U_1.V_86.Formal.Next, PrevWith, Composer);
}

static void AssignSubFormal
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(t, Formals, PrevWith, Composer)
Tree_tTree t, Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  Idents_tIdent TreeName, With;

  if (t->U_1.V_1.Kind == Tree_Compose) {
    {
      register Tree_yCompose *W_11 = &t->U_1.V_61.Compose;

      TreeName = W_11->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name;
      With = MakeWith();
      IO_WriteS(Tree_f, (STRING)"   {register t", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    yyALLOC (t", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolFreePtr,", 13L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_PoolMaxPtr,", 12L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_Alloc,", 7L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)"_NodeSize,Make", 14L);
      Tree_WI(TreeName);
      IO_WriteS(Tree_f, (STRING)",", 1L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)",k", 2L);
      Tree_WI(W_11->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"    ", 4L);
      Tree_WI(PrevWith);
      IO_WriteS(Tree_f, (STRING)"->", 2L);
      Tree_WI(Composer);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(Formals->U_1.V_86.Formal.Name);
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Tree_WI(With);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      AssignSubFormals(W_11->Exprs, W_11->Object->U_1.V_5.Class.Formals, With, W_11->Object->U_1.V_5.Class.Name);
      IO_WriteS(Tree_f, (STRING)"   }", 4L);
      IO_WriteNl(Tree_f);
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
    IO_WriteS(Tree_f, (STRING)"    ", 4L);
    Tree_WI(PrevWith);
    IO_WriteS(Tree_f, (STRING)"->", 2L);
    Tree_WI(Composer);
    IO_WriteS(Tree_f, (STRING)".", 1L);
    Tree_WI(Formals->U_1.V_86.Formal.Name);
    IO_WriteS(Tree_f, (STRING)" = ", 3L);
    Expression(t);
    IO_WriteS(Tree_f, (STRING)";", 1L);
    IO_WriteNl(Tree_f);
    break;
  case Tree_DontCare1:;
    IO_WriteS(Tree_f, (STRING)"    begin", 9L);
    C_DefC(Formals->U_1.V_86.Formal.TypeDesc);
    IO_WriteS(Tree_f, (STRING)" (", 2L);
    Tree_WI(PrevWith);
    IO_WriteS(Tree_f, (STRING)"->", 2L);
    Tree_WI(Composer);
    IO_WriteS(Tree_f, (STRING)".", 1L);
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
      register Tree_yFormal *W_12 = &Formals->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)"    begin", 9L);
      C_DefC(W_12->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (* ", 4L);
      Tree_WI(W_12->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      BeginFormals(W_12->Next);
    }
  }
}

static void BeginSubFormals
# ifdef __STDC__
(Tree_tTree Formals, Idents_tIdent PrevWith, Idents_tIdent Composer)
# else
(Formals, PrevWith, Composer)
Tree_tTree Formals;
Idents_tIdent PrevWith, Composer;
# endif
{
  if (Formals->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_13 = &Formals->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)"    begin", 9L);
      C_DefC(W_13->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      Tree_WI(PrevWith);
      IO_WriteS(Tree_f, (STRING)"->", 2L);
      Tree_WI(Composer);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_13->Name);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      BeginSubFormals(W_13->Next, PrevWith, Composer);
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
    register Tree_yOnePattern *W_14 = &t->U_1.V_45.OnePattern;

    if (W_14->Pattern->U_1.V_1.Kind == Tree_DontCare) {
      return ConsTempos(W_14->Pattern->U_1.V_54.DontCare.Tempos, ListCount, TRUE);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      IO_WriteS(Tree_f, (STRING)"& ", 2L);
      Tree_WI(W_14->Pattern->U_1.V_49.Pattern.Tempo);
      return ConsPatterns(W_14->Next, ListCount + 1);
    }
  }
}

static INTEGER ConsTempos
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount, BOOLEAN IsRef)
# else
(t, ListCount, IsRef)
Tree_tTree t;
INTEGER ListCount;
BOOLEAN IsRef;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Formal) {
    if (ListCount > 0) {
      IO_WriteS(Tree_f, (STRING)", ", 2L);
    }
    if (IsRef) {
      IO_WriteS(Tree_f, (STRING)"& ", 2L);
    }
    Tree_WI(t->U_1.V_86.Formal.Name);
    return ConsTempos(t->U_1.V_86.Formal.Next, ListCount + 1, IsRef);
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
    register Tree_yOneExpr *W_15 = &t->U_1.V_58.OneExpr;

    if (W_15->Expr->U_1.V_1.Kind == Tree_DontCare) {
      return ConsTempos(W_15->Expr->U_1.V_54.DontCare.Tempos, ListCount, FALSE);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Expression(W_15->Expr);
      return Expressions(W_15->Next, ListCount + 1);
    }
  }
}

static INTEGER Expressions2
# ifdef __STDC__
(Tree_tTree t, INTEGER ListCount, Tree_tTree Formals)
# else
(t, ListCount, Formals)
Tree_tTree t;
INTEGER ListCount;
Tree_tTree Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    return ListCount;
  }
  {
    register Tree_yOneExpr *W_16 = &t->U_1.V_58.OneExpr;

    if (W_16->Expr->U_1.V_1.Kind == Tree_DontCare) {
      return ConsTempos(W_16->Expr->U_1.V_54.DontCare.Tempos, ListCount, FALSE);
    } else {
      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      if (Formals->U_1.V_86.Formal.Path->U_1.V_92.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)"& ", 2L);
      }
      Expression(W_16->Expr);
      return Expressions2(W_16->Next, ListCount + 1, Formals->U_1.V_86.Formal.Next);
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
    IO_WriteS(Tree_f, (STRING)"NULL", 4L);
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_17 = &t->U_1.V_62.VarUse;

      if (W_17->Object != Tree_NoTree) {
        C_ImplC(W_17->Object->U_1.V_86.Formal.Path);
      } else {
        Tree_WI(W_17->Name);
      }
    }
    break;
  case Tree_DontCare1:;
    Tree_WI(t->U_1.V_53.DontCare1.Tempo);
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_18 = &t->U_1.V_65.Call;

      Expression(W_18->Expr);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      if (W_18->Object != Tree_NoTree) {
        ListCount = Expressions2(W_18->Exprs, 0L, W_18->Object->U_1.V_32.Routine.InForm);
        ListCount = ConsPatterns(W_18->Patterns, ListCount);
      } else {
        ListCount = Expressions(W_18->Exprs, 0L);
        ListCount = Expressions(W_18->Patterns, ListCount);
      }
      IO_WriteS(Tree_f, (STRING)")", 1L);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_19 = &t->U_1.V_66.Binary;

      Expression(W_19->Lop);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_19->Operator);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Expression(W_19->Rop);
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
    C_ImplC(t->U_1.V_71.TargetExpr.Expr);
    break;
  case Tree_StringExpr:;
    StringMem_WriteString(Tree_f, t->U_1.V_72.StringExpr.String);
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_20 = &t->U_1.V_63.AttrDesc;

      C_ImplC(W_20->Object->U_1.V_86.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"->", 2L);
      Tree_WI(W_20->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_20->Attribute);
    }
    break;
  }
}

static Idents_tIdent MakeWith
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString String1, String2;

  INC(WithCount);
  Strings_ArrayToString((STRING)"yyW", 3L, &String1);
  Strings_IntToString(WithCount, &String2);
  Strings_Concatenate(&String1, &String2);
  return Idents_MakeIdent(&String1);
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module C, routine ", 25L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*C_Exit)();
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

void C_MacroC
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
      register Tree_ySpec *W_21 = &t->U_1.V_26.Spec;

      C_MacroC(W_21->TreeNames);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_22 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"# define begint", 15L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)"(a)	a = NULL;", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define equalt", 15L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)"(a, b)	IsEqual", 14L);
      Tree_WI(W_22->Name);
      IO_WriteS(Tree_f, (STRING)" (a, b)", 7L);
      IO_WriteNl(Tree_f);
      C_MacroC(W_22->Next);
      return;
    }
  }
}

void C_DefC
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
      register Tree_ySpec *W_23 = &t->U_1.V_26.Spec;

      IO_WriteS(Tree_f, (STRING)"# ifndef yy", 11L);
      Tree_WI(W_23->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yy", 11L);
      Tree_WI(W_23->TrafoName);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define ARGS(parameters)	parameters", 36L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define ARGS(parameters)	()", 28L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef bool", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define bool char", 18L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_DefC(W_23->TreeNames);
      IO_WriteNl(Tree_f);
      WriteLine(W_23->Codes->U_1.V_12.Codes.ImportLine);
      Texts_WriteText(Tree_f, W_23->Codes->U_1.V_12.Codes.Import);
      WriteLine(W_23->Codes->U_1.V_12.Codes.ExportLine);
      Texts_WriteText(Tree_f, W_23->Codes->U_1.V_12.Codes.Export);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern void (* ", 15L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)"_Exit) ();", 10L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_DefC(W_23->Public);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern void Begin", 17L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ();", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern void Close", 17L);
      Tree_WI(W_23->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ();", 4L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_24 = &t->U_1.V_29.TreeName;

      IO_WriteS(Tree_f, (STRING)"# include \"", 11L);
      Tree_WI(W_24->Name);
      IO_WriteS(Tree_f, (STRING)".h\"", 3L);
      IO_WriteNl(Tree_f);
      C_DefC(W_24->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_25 = &t->U_1.V_25.Name;

      if (W_25->Object != Tree_NoTree) {
        ListCount = 0;
        IO_WriteS(Tree_f, (STRING)"extern ", 7L);
        if (W_25->Object->U_1.V_1.Kind == Tree_Procedure) {
          IO_WriteS(Tree_f, (STRING)"void", 4L);
        } else if (W_25->Object->U_1.V_1.Kind == Tree_Function) {
          C_DefC(W_25->Object->U_1.V_34.Function.ReturnForm->U_1.V_86.Formal.TypeDesc);
        } else if (W_25->Object->U_1.V_1.Kind == Tree_Predicate) {
          IO_WriteS(Tree_f, (STRING)"bool", 4L);
        }
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_25->Name);
        IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
        C_DefC(W_25->Object->U_1.V_32.Routine.InForm);
        C_DefC(W_25->Object->U_1.V_32.Routine.OutForm);
        IO_WriteS(Tree_f, (STRING)"));", 3L);
        IO_WriteNl(Tree_f);
      }
      C_DefC(W_25->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_26 = &t->U_1.V_86.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      C_DefC(W_26->TypeDesc);
      if (W_26->Path->U_1.V_92.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)" *", 2L);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_26->Name);
      INC(ListCount);
      C_DefC(W_26->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_27 = &t->U_1.V_89.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_27->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_UserType) {
    {
      register Tree_yUserType *W_28 = &t->U_1.V_90.UserType;

      Tree_WI(W_28->Type);
      return;
    }
  }
}

static void Forward
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
  if (t->U_1.V_1.Kind == Tree_Procedure) {
    {
      register Tree_yProcedure *W_29 = &t->U_1.V_33.Procedure;

      ListCount = 0;
      if (!W_29->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"void ", 5L);
      Tree_WI(W_29->Name);
      IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
      C_DefC(W_29->InForm);
      C_DefC(W_29->OutForm);
      IO_WriteS(Tree_f, (STRING)"));", 3L);
      IO_WriteNl(Tree_f);
      Forward(W_29->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_30 = &t->U_1.V_34.Function;

      ListCount = 0;
      if (!W_30->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      C_DefC(W_30->ReturnForm->U_1.V_86.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_30->Name);
      IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
      C_DefC(W_30->InForm);
      C_DefC(W_30->OutForm);
      IO_WriteS(Tree_f, (STRING)"));", 3L);
      IO_WriteNl(Tree_f);
      Forward(W_30->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Predicate) {
    {
      register Tree_yPredicate *W_31 = &t->U_1.V_35.Predicate;

      ListCount = 0;
      if (!W_31->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"bool ", 5L);
      Tree_WI(W_31->Name);
      IO_WriteS(Tree_f, (STRING)" ARGS((", 7L);
      C_DefC(W_31->InForm);
      C_DefC(W_31->OutForm);
      IO_WriteS(Tree_f, (STRING)"));", 3L);
      IO_WriteNl(Tree_f);
      Forward(W_31->Next);
      return;
    }
  }
}

static void ProcHead1
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_6 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_32 = &t->U_1.V_86.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      Tree_WI(W_32->Name);
      INC(ListCount);
      ProcHead1(W_32->Next);
      return;
    }
  }
}

static void ProcHead2
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
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_33 = &t->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)" ", 1L);
      if (W_33->TypeDesc->U_1.V_1.Kind == Tree_NodeTypes && W_33->Path->U_1.V_92.Var.IsRegister) {
        IO_WriteS(Tree_f, (STRING)"register ", 9L);
      }
      C_ImplC(W_33->TypeDesc);
      if (W_33->Path->U_1.V_92.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)" *", 2L);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_33->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      ProcHead2(W_33->Next);
      return;
    }
  }
}

static void ProcHead3
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_8 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_34 = &t->U_1.V_86.Formal;

      if (ListCount > 0) {
        IO_WriteS(Tree_f, (STRING)", ", 2L);
      }
      if (W_34->TypeDesc->U_1.V_1.Kind == Tree_NodeTypes && W_34->Path->U_1.V_92.Var.IsRegister) {
        IO_WriteS(Tree_f, (STRING)"register ", 9L);
      }
      C_ImplC(W_34->TypeDesc);
      if (W_34->Path->U_1.V_92.Var.IsOutput) {
        IO_WriteS(Tree_f, (STRING)" *", 2L);
      }
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_34->Name);
      INC(ListCount);
      ProcHead3(W_34->Next);
      return;
    }
  }
}

void C_ImplC
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Spec:;
    {
      register Tree_ySpec *W_35 = &t->U_1.V_26.Spec;

      IO_WriteS(Tree_f, (STRING)"# include \"", 11L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)".h\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifdef __cplusplus", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"extern \"C\" {", 12L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"System.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include \"System.h\"", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# include <stdio.h>", 19L);
      IO_WriteNl(Tree_f);
      C_DefC(W_35->TreeNames);
      IO_WriteNl(Tree_f);
      if (!Sets_IsElement(ORD('m'), &Tree_Options)) {
        IO_WriteS(Tree_f, (STRING)"# define yyInline", 17L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"# ifndef NULL", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define NULL 0L", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef false", 14L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define false 0", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifndef true", 13L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define true 1", 15L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifdef yyInline", 16L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, free, max, alloc, nodesize, make, ptr, kind) \\", 69L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  if ((ptr = (tree) free) >= (tree) max) ptr = alloc (); \\", 58L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  free += nodesize [kind]; \\", 28L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr->yyHead.yyMark = 0; \\", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"  ptr->Kind = kind;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyALLOC(tree, free, max, alloc, nodesize, make, ptr, kind) ptr = make (kind);", 86L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWrite(s) (void) fputs (s, yyf)", 41L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# define yyWriteNl (void) fputc ('\\n', yyf)", 43L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      WriteLine(W_35->Codes->U_1.V_12.Codes.GlobalLine);
      Texts_WriteText(Tree_f, W_35->Codes->U_1.V_12.Codes.Global);
      IO_WriteS(Tree_f, (STRING)"# include \"yy", 13L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)".w\"", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static void yyExit () { Exit (1); }", 35L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void (* ", 8L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)"_Exit) () = yyExit;", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static FILE * yyf = stdout;", 27L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"static void yyAbort", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# ifdef __cplusplus", 19L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (char * yyFunction)", 20L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (yyFunction) char * yyFunction;", 32L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" (void) fprintf (stderr, \"Error: module ", 40L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)", routine %s failed\\n\", yyFunction);", 36L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)"_Exit ();", 9L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      Forward(W_35->Routines);
      IO_WriteNl(Tree_f);
      C_ImplC(W_35->Routines);
      IO_WriteS(Tree_f, (STRING)"void Begin", 10L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_35->Codes->U_1.V_12.Codes.BeginLine);
      Texts_WriteText(Tree_f, W_35->Codes->U_1.V_12.Codes.Begin);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"void Close", 10L);
      Tree_WI(W_35->TrafoName);
      IO_WriteS(Tree_f, (STRING)" ()", 3L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_35->Codes->U_1.V_12.Codes.CloseLine);
      Texts_WriteText(Tree_f, W_35->Codes->U_1.V_12.Codes.Close);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_36 = &t->U_1.V_33.Procedure;

      if (!W_36->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"void ", 5L);
      Tree_WI(W_36->Name);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead3(W_36->InForm);
      ProcHead3(W_36->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead1(W_36->InForm);
      ProcHead1(W_36->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      ProcHead2(W_36->InForm);
      ProcHead2(W_36->OutForm);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_36->LocalLine);
      Texts_WriteText(Tree_f, W_36->Local);
      RoutineKind = kProcedure;
      InFormals = W_36->InForm;
      OutFormals = W_36->OutForm;
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_36->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        C_ImplC(W_36->Rules);
        if (Sets_IsElement(ORD('f'), &Tree_Options)) {
          IO_WriteS(Tree_f, (STRING)" yyAbort (\"", 11L);
          Tree_WI(W_36->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_36->Decisions);
        if (Sets_IsElement(ORD('f'), &Tree_Options) && !Optimize_NeedsNoFinale(W_36->Decisions)) {
          IO_WriteS(Tree_f, (STRING)" yyAbort (\"", 11L);
          Tree_WI(W_36->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_ImplC(W_36->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_37 = &t->U_1.V_34.Function;

      if (!W_37->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      C_DefC(W_37->ReturnForm->U_1.V_86.Formal.TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_37->Name);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead3(W_37->InForm);
      ProcHead3(W_37->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead1(W_37->InForm);
      ProcHead1(W_37->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      ProcHead2(W_37->InForm);
      ProcHead2(W_37->OutForm);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_37->LocalLine);
      Texts_WriteText(Tree_f, W_37->Local);
      RoutineKind = kFunction;
      InFormals = W_37->InForm;
      OutFormals = W_37->OutForm;
      ReturnFormals = W_37->ReturnForm;
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        C_ImplC(W_37->Rules);
        IO_WriteS(Tree_f, (STRING)" yyAbort (\"", 11L);
        Tree_WI(W_37->Name);
        IO_WriteS(Tree_f, (STRING)"\");", 3L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_37->Decisions);
        if (!Optimize_NeedsNoFinale(W_37->Decisions)) {
          IO_WriteS(Tree_f, (STRING)" yyAbort (\"", 11L);
          Tree_WI(W_37->Name);
          IO_WriteS(Tree_f, (STRING)"\");", 3L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_ImplC(W_37->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_38 = &t->U_1.V_35.Predicate;

      if (!W_38->IsExtern) {
        IO_WriteS(Tree_f, (STRING)"static ", 7L);
      }
      IO_WriteS(Tree_f, (STRING)"bool ", 5L);
      Tree_WI(W_38->Name);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# if defined __STDC__ | defined __cplusplus", 43L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead3(W_38->InForm);
      ProcHead3(W_38->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"# else", 6L);
      IO_WriteNl(Tree_f);
      ListCount = 0;
      IO_WriteS(Tree_f, (STRING)"(", 1L);
      ProcHead1(W_38->InForm);
      ProcHead1(W_38->OutForm);
      IO_WriteS(Tree_f, (STRING)")", 1L);
      IO_WriteNl(Tree_f);
      ProcHead2(W_38->InForm);
      ProcHead2(W_38->OutForm);
      IO_WriteS(Tree_f, (STRING)"# endif", 7L);
      IO_WriteNl(Tree_f);
      IO_WriteS(Tree_f, (STRING)"{", 1L);
      IO_WriteNl(Tree_f);
      WriteLine(W_38->LocalLine);
      Texts_WriteText(Tree_f, W_38->Local);
      RoutineKind = kPredicate;
      InFormals = W_38->InForm;
      OutFormals = W_38->OutForm;
      if (Sets_IsElement(ORD('n'), &Tree_Options)) {
        Tg1(W_38->InForm);
      }
      if (Sets_IsElement(ORD('b'), &Tree_Options)) {
        C_ImplC(W_38->Rules);
        IO_WriteS(Tree_f, (STRING)"  return false;", 15L);
        IO_WriteNl(Tree_f);
      } else {
        TemposDone = FALSE;
        CommonTestElim(W_38->Decisions);
        if (!Optimize_NeedsNoFinale(W_38->Decisions)) {
          IO_WriteS(Tree_f, (STRING)"  return false;", 15L);
          IO_WriteNl(Tree_f);
        }
      }
      IO_WriteS(Tree_f, (STRING)"}", 1L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_ImplC(W_38->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_39 = &t->U_1.V_42.Rule;

      WriteLine(W_39->Line);
      if (W_39->HasTempos) {
        IO_WriteS(Tree_f, (STRING)" {", 2L);
        IO_WriteNl(Tree_f);
      }
      RuleCount = W_39->Index;
      WithCount = 0;
      Decls = W_39->VarDecls;
      Declare(W_39->Patterns);
      Declare(W_39->Exprs);
      Declare(W_39->Statements);
      Match(W_39->Patterns, InFormals);
      if (W_39->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        IO_WriteS(Tree_f, (STRING)"  {", 3L);
        IO_WriteNl(Tree_f);
        C_ImplC(W_39->Statements);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
      }
      if (!W_39->HasRejectOrFail) {
        AssignFormals(W_39->Exprs, OutFormals);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"   return;", 10L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          if (W_39->HasPatterns && W_39->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            IO_WriteS(Tree_f, (STRING)"  {register ", 12L);
            C_DefC(ReturnFormals->U_1.V_86.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)" ", 1L);
            Tree_WI(W_39->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            Declare(W_39->Expr);
            AssignTempo(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)"   ", 3L);
            Tree_WI(W_39->Tempo);
            IO_WriteS(Tree_f, (STRING)" = ", 3L);
            Expression(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Tree_WI(W_39->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"  }", 3L);
            IO_WriteNl(Tree_f);
          } else if (W_39->HasTempos) {
            IO_WriteS(Tree_f, (STRING)"  {", 3L);
            IO_WriteNl(Tree_f);
            Declare(W_39->Expr);
            AssignTempo(W_39->Expr);
            MatchExpr(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Expression(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"  }", 3L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Expression(W_39->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"   return true;", 15L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (W_39->HasTempos) {
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
      }
      IO_WriteS(Tree_f, (STRING)"yyL", 3L);
      Tree_WN(RuleCount);
      IO_WriteS(Tree_f, (STRING)":;", 2L);
      IO_WriteNl(Tree_f);
      IO_WriteNl(Tree_f);
      C_ImplC(W_39->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_40 = &t->U_1.V_76.ProcCall;

      WriteLine(W_40->Pos);
      AssignTempo(W_40->Call);
      IO_WriteS(Tree_f, (STRING)"   ", 3L);
      Expression(W_40->Call);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_40->Call);
      C_ImplC(W_40->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_41 = &t->U_1.V_77.Condition;

      WriteLine(W_41->Pos);
      AssignTempo(W_41->Expr);
      IO_WriteS(Tree_f, (STRING)"   if (! (", 10L);
      Expression(W_41->Expr);
      IO_WriteS(Tree_f, (STRING)")) goto yyL", 11L);
      Tree_WN(RuleCount);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_41->Expr);
      if (W_41->Next->U_1.V_1.Kind != Tree_NoStatement) {
        IO_WriteS(Tree_f, (STRING)"  {", 3L);
        IO_WriteNl(Tree_f);
        C_ImplC(W_41->Next);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_42 = &t->U_1.V_78.Assignment;

      WriteLine(W_42->Pos);
      AssignTempo(W_42->Adr);
      AssignTempo(W_42->Expr);
      if (W_42->Object != Tree_NoTree) {
        IO_WriteS(Tree_f, (STRING)"   ", 3L);
        C_ImplC(W_42->Object->U_1.V_86.Formal.Path);
      } else {
        IO_WriteS(Tree_f, (STRING)"   ", 3L);
        Expression(W_42->Adr);
      }
      IO_WriteS(Tree_f, (STRING)" = ", 3L);
      Expression(W_42->Expr);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_42->Adr);
      MatchExpr(W_42->Expr);
      C_ImplC(W_42->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_43 = &t->U_1.V_79.Reject;

      WriteLine(W_43->Pos);
      IO_WriteS(Tree_f, (STRING)"   goto yyL", 11L);
      Tree_WN(RuleCount);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_44 = &t->U_1.V_80.Fail;

      WriteLine(W_44->Pos);
      IO_WriteS(Tree_f, (STRING)"   return", 9L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" false", 6L);
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_45 = &t->U_1.V_81.TargetStmt;

      WriteLine(W_45->Pos);
      C_ImplC(W_45->Stmt);
      IO_WriteNl(Tree_f);
      C_ImplC(W_45->Next);
      return;
    }
    break;
  case Tree_Nl:;
    {
      register Tree_yNl *W_46 = &t->U_1.V_82.Nl;

      WriteLine(W_46->Pos);
      IO_WriteS(Tree_f, (STRING)"   yyWriteNl;", 13L);
      IO_WriteNl(Tree_f);
      C_ImplC(W_46->Next);
      return;
    }
    break;
  case Tree_WriteStr:;
    {
      register Tree_yWriteStr *W_47 = &t->U_1.V_83.WriteStr;

      WriteLine(W_47->Pos);
      IO_WriteS(Tree_f, (STRING)"   yyWrite (", 12L);
      StringMem_WriteString(Tree_f, W_47->String);
      IO_WriteS(Tree_f, (STRING)");", 2L);
      IO_WriteNl(Tree_f);
      C_ImplC(W_47->Next);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register struct S_10 *W_48 = &yyTempo.U_1.V_1.yyR14;

      {
        register Tree_yIdent *W_49 = &t->U_1.V_16.Ident;

        W_48->Var = Semantics_IdentifyVar(Decls, W_49->Attribute);
        if (W_48->Var != Tree_NoTree) {
          C_ImplC(W_48->Var->U_1.V_86.Formal.Path);
        } else {
          Tree_WI(W_49->Attribute);
        }
        C_ImplC(W_49->Next);
        return;
      }
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_50 = &t->U_1.V_18.Any;

      StringMem_WriteString(Tree_f, W_50->Code);
      C_ImplC(W_50->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_51 = &t->U_1.V_19.Anys;

      C_ImplC(W_51->Layouts);
      C_ImplC(W_51->Next);
      return;
    }
    break;
  case Tree_LayoutAny:;
    {
      register Tree_yLayoutAny *W_52 = &t->U_1.V_22.LayoutAny;

      StringMem_WriteString(Tree_f, W_52->Code);
      C_ImplC(W_52->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_53 = &t->U_1.V_15.Designator;

      C_ImplC(W_53->Object->U_1.V_86.Formal.Path);
      IO_WriteS(Tree_f, (STRING)"->", 2L);
      Tree_WI(W_53->Type);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_53->Attribute);
      C_ImplC(W_53->Next);
      return;
    }
    break;
  case Tree_Field:;
    {
      register Tree_yField *W_54 = &t->U_1.V_94.Field;

      C_ImplC(W_54->Next);
      IO_WriteS(Tree_f, (STRING)".", 1L);
      Tree_WI(W_54->Name);
      return;
    }
    break;
  case Tree_ConsType:;
    {
      register Tree_yConsType *W_55 = &t->U_1.V_93.ConsType;

      C_ImplC(W_55->Next);
      IO_WriteS(Tree_f, (STRING)"->", 2L);
      Tree_WI(W_55->Name);
      return;
    }
    break;
  case Tree_Var:;
    {
      register Tree_yVar *W_56 = &t->U_1.V_92.Var;

      if (W_56->IsOutput) {
        IO_WriteS(Tree_f, (STRING)"(* ", 3L);
        Tree_WI(W_56->Name);
        IO_WriteS(Tree_f, (STRING)")", 1L);
      } else {
        Tree_WI(W_56->Name);
      }
      return;
    }
    break;
  case Tree_NodeTypes:;
    {
      register Tree_yNodeTypes *W_57 = &t->U_1.V_89.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"t", 1L);
      Tree_WI(W_57->TreeName->U_1.V_29.TreeName.Name);
      return;
    }
    break;
  case Tree_UserType:;
    {
      register Tree_yUserType *W_58 = &t->U_1.V_90.UserType;

      if (!Sets_IsElement((LONGCARD)W_58->Type, &Semantics_UserTypes)) {
        IO_WriteS(Tree_f, (STRING)"register ", 9L);
      }
      Tree_WI(W_58->Type);
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
  struct S_11 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Formal:;
    {
      register Tree_yFormal *W_59 = &t->U_1.V_86.Formal;

      IO_WriteS(Tree_f, (STRING)"  ", 2L);
      C_DefC(W_59->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" ", 1L);
      Tree_WI(W_59->Name);
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      Declare(W_59->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register struct S_12 *W_60 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yParam *W_61 = &t->U_1.V_38.Param;

        W_60->Var = Semantics_IdentifyVar(Decls, W_61->Name);
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        C_DefC(W_60->Var->U_1.V_86.Formal.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_61->Name);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
        Declare(W_61->Next);
        return;
      }
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_62 = &t->U_1.V_76.ProcCall;

      Declare(W_62->Call);
      Declare(W_62->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_63 = &t->U_1.V_77.Condition;

      Declare(W_63->Expr);
      Declare(W_63->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_64 = &t->U_1.V_78.Assignment;

      Declare(W_64->Adr);
      Declare(W_64->Expr);
      Declare(W_64->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_65 = &t->U_1.V_81.TargetStmt;

      Declare(W_65->Parameters);
      Declare(W_65->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_66 = &t->U_1.V_75.Statement;

      Declare(W_66->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_67 = &t->U_1.V_45.OnePattern;

      if (W_67->Pattern->U_1.V_49.Pattern.Tempo != Idents_NoIdent && W_67->Pattern->U_1.V_1.Kind != Tree_DontCare1) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        C_DefC(W_67->Pattern->U_1.V_49.Pattern.TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_67->Pattern->U_1.V_49.Pattern.Tempo);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_67->Pattern);
      Declare(W_67->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_68 = &t->U_1.V_58.OneExpr;

      Declare(W_68->Expr);
      Declare(W_68->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_69 = &t->U_1.V_50.Decompose;

      Declare(W_69->Patterns);
      return;
    }
    break;
  case Tree_DontCare:;
    {
      register Tree_yDontCare *W_70 = &t->U_1.V_54.DontCare;

      Declare(W_70->Tempos);
      return;
    }
    break;
  case Tree_DontCare1:;
    {
      register Tree_yDontCare1 *W_71 = &t->U_1.V_53.DontCare1;

      if (W_71->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  ", 2L);
        C_DefC(W_71->TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_71->Tempo);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_72 = &t->U_1.V_55.Value;

      Declare(W_72->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_73 = &t->U_1.V_61.Compose;

      if (W_73->Tempo != Idents_NoIdent) {
        IO_WriteS(Tree_f, (STRING)"  register ", 11L);
        C_DefC(W_73->TypeDesc);
        IO_WriteS(Tree_f, (STRING)" ", 1L);
        Tree_WI(W_73->Tempo);
        IO_WriteS(Tree_f, (STRING)";", 1L);
        IO_WriteNl(Tree_f);
      }
      Declare(W_73->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_74 = &t->U_1.V_65.Call;

      Declare(W_74->Expr);
      Declare(W_74->Exprs);
      Declare(W_74->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_75 = &t->U_1.V_66.Binary;

      Declare(W_75->Lop);
      Declare(W_75->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_76 = &t->U_1.V_67.PreOperator;

      Declare(W_76->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_77 = &t->U_1.V_68.PostOperator;

      Declare(W_77->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_78 = &t->U_1.V_70.Parents;

      Declare(W_78->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_79 = &t->U_1.V_69.Index;

      Declare(W_79->Expr);
      Declare(W_79->Exprs);
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
  struct S_13 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_80 = &t->U_1.V_86.Formal;

      TheName = W_80->Name;
      Tg1(W_80->TypeDesc);
      Tg1(W_80->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_81 = &t->U_1.V_89.NodeTypes;

      IO_WriteS(Tree_f, (STRING)"  if (", 6L);
      Tree_WI(TheName);
      IO_WriteS(Tree_f, (STRING)" == No", 6L);
      Tree_WI(W_81->TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)") return", 8L);
      if (RoutineKind == kPredicate) {
        IO_WriteS(Tree_f, (STRING)" false", 6L);
      }
      IO_WriteS(Tree_f, (STRING)";", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
}

static void CommonTestElim
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_14 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Decision:;
    {
      register Tree_yDecision *W_82 = &t->U_1.V_105.Decision;

      if (W_82->Cases == 0) {
        if (!TemposDone && W_82->OneTest->U_1.V_1.Kind == Tree_TestValue && Optimize_NeedsTempo(W_82->Then, &rule)) {
          IO_WriteS(Tree_f, (STRING)" {", 2L);
          IO_WriteNl(Tree_f);
          TemposDone = TRUE;
          {
            register Tree_yRule *W_83 = &rule->U_1.V_42.Rule;

            RuleCount = W_83->Index;
            Decls = W_83->VarDecls;
            Declare(W_83->Patterns);
            Declare(W_83->Exprs);
            Declare(W_83->Statements);
          }
          CommonTestElim(W_82->OneTest);
          CommonTestElim(W_82->Then);
          IO_WriteS(Tree_f, (STRING)"  }", 3L);
          IO_WriteNl(Tree_f);
          IO_WriteS(Tree_f, (STRING)" }", 2L);
          IO_WriteNl(Tree_f);
        } else {
          Optimize_GetRule(W_82->Then, &rule);
          Decls = rule->U_1.V_42.Rule.VarDecls;
          CommonTestElim(W_82->OneTest);
          CommonTestElim(W_82->Then);
          IO_WriteS(Tree_f, (STRING)"  }", 3L);
          IO_WriteNl(Tree_f);
        }
        if (W_82->OneTest->U_1.V_1.Kind == Tree_TestValue && W_82->OneTest->U_1.V_102.TestValue.TypeDesc->U_1.V_1.Kind == Tree_UserType && Sets_IsElement((LONGCARD)W_82->OneTest->U_1.V_102.TestValue.TypeDesc->U_1.V_90.UserType.Type, &Semantics_UserTypes)) {
          IO_WriteS(Tree_f, (STRING)"  }", 3L);
          IO_WriteNl(Tree_f);
        }
        TemposDone = FALSE;
        CommonTestElim(W_82->Else);
      } else {
        i = W_82->Cases;
        Case(t);
      }
      return;
    }
    break;
  case Tree_Decided:;
    {
      register Tree_yDecided *W_84 = &t->U_1.V_106.Decided;

      CommonTestElim(W_84->Rule);
      if (W_84->Rule->U_1.V_42.Rule.HasExit) {
        TemposDone = FALSE;
        CommonTestElim(W_84->Else);
      }
      return;
    }
    break;
  case Tree_TestKind:;
    {
      register Tree_yTestKind *W_85 = &t->U_1.V_98.TestKind;

      IO_WriteS(Tree_f, (STRING)"  if (", 6L);
      C_ImplC(W_85->Path);
      IO_WriteS(Tree_f, (STRING)"->Kind == k", 11L);
      Tree_WI(W_85->Name);
      IO_WriteS(Tree_f, (STRING)") {", 3L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestIsType:;
    {
      register Tree_yTestIsType *W_86 = &t->U_1.V_99.TestIsType;

      IO_WriteS(Tree_f, (STRING)"  if (", 6L);
      Tree_WI(W_86->TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name);
      IO_WriteS(Tree_f, (STRING)"_IsType (", 9L);
      C_ImplC(W_86->Path);
      IO_WriteS(Tree_f, (STRING)", k", 3L);
      Tree_WI(W_86->Name);
      IO_WriteS(Tree_f, (STRING)")) {", 4L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNil:;
    {
      register Tree_yTestNil *W_87 = &t->U_1.V_100.TestNil;

      IO_WriteS(Tree_f, (STRING)"  if (", 6L);
      C_ImplC(W_87->Path);
      IO_WriteS(Tree_f, (STRING)" == NULL) {", 11L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestNonlin:;
    {
      register Tree_yTestNonlin *W_88 = &t->U_1.V_101.TestNonlin;

      IO_WriteS(Tree_f, (STRING)"  if (equal", 11L);
      C_DefC(W_88->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      C_ImplC(W_88->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      C_ImplC(W_88->Path2);
      IO_WriteS(Tree_f, (STRING)")) {", 4L);
      IO_WriteNl(Tree_f);
      return;
    }
    break;
  case Tree_TestValue:;
    if (t->U_1.V_102.TestValue.TypeDesc->U_1.V_1.Kind == Tree_UserType) {
      for (;;) {
        {
          register Tree_yTestValue *W_89 = &t->U_1.V_102.TestValue;

          if (!Sets_IsElement((LONGCARD)t->U_1.V_102.TestValue.TypeDesc->U_1.V_90.UserType.Type, &Semantics_UserTypes)) {
            goto EXIT_1;
          }
          AssignTempo(W_89->Expr);
          IO_WriteS(Tree_f, (STRING)"  {", 3L);
          C_DefC(W_89->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" yyT; yyT = ", 12L);
          Expression(W_89->Expr);
          IO_WriteS(Tree_f, (STRING)";", 1L);
          IO_WriteNl(Tree_f);
          MatchExpr(W_89->Expr);
          IO_WriteS(Tree_f, (STRING)"  if (equal", 11L);
          C_DefC(W_89->TypeDesc);
          IO_WriteS(Tree_f, (STRING)" (", 2L);
          C_ImplC(W_89->Path);
          IO_WriteS(Tree_f, (STRING)", yyT)) {", 9L);
          IO_WriteNl(Tree_f);
          return;
        }
      } EXIT_1:;
    }
    {
      register Tree_yTestValue *W_90 = &t->U_1.V_102.TestValue;

      AssignTempo(W_90->Expr);
      IO_WriteS(Tree_f, (STRING)"  if (equal", 11L);
      C_DefC(W_90->TypeDesc);
      IO_WriteS(Tree_f, (STRING)" (", 2L);
      C_ImplC(W_90->Path);
      IO_WriteS(Tree_f, (STRING)", ", 2L);
      Expression(W_90->Expr);
      IO_WriteS(Tree_f, (STRING)")) {", 4L);
      IO_WriteNl(Tree_f);
      MatchExpr(W_90->Expr);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_91 = &t->U_1.V_42.Rule;

      WriteLine(W_91->Line);
      RuleCount = W_91->Index;
      WithCount = 0;
      Decls = W_91->VarDecls;
      if (W_91->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)" {", 2L);
        IO_WriteNl(Tree_f);
        Declare(W_91->Patterns);
        Declare(W_91->Exprs);
        Declare(W_91->Statements);
      }
      if (W_91->Statements->U_1.V_1.Kind != Tree_NoStatement) {
        IO_WriteS(Tree_f, (STRING)"  {", 3L);
        IO_WriteNl(Tree_f);
        C_ImplC(W_91->Statements);
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
      }
      if (!W_91->HasRejectOrFail) {
        AssignFormals(W_91->Exprs, OutFormals);
        switch (RoutineKind) {
        case kProcedure:;
          IO_WriteS(Tree_f, (STRING)"   return;", 10L);
          IO_WriteNl(Tree_f);
          break;
        case kFunction:;
          if (W_91->HasPatterns && W_91->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            IO_WriteS(Tree_f, (STRING)"  {register ", 12L);
            C_DefC(ReturnFormals->U_1.V_86.Formal.TypeDesc);
            IO_WriteS(Tree_f, (STRING)" ", 1L);
            Tree_WI(W_91->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            Declare(W_91->Expr);
            AssignTempo(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)"   ", 3L);
            Tree_WI(W_91->Tempo);
            IO_WriteS(Tree_f, (STRING)" = ", 3L);
            Expression(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            MatchExpr(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Tree_WI(W_91->Tempo);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"  }", 3L);
            IO_WriteNl(Tree_f);
          } else if (W_91->HasTempos) {
            IO_WriteS(Tree_f, (STRING)"  {", 3L);
            IO_WriteNl(Tree_f);
            Declare(W_91->Expr);
            AssignTempo(W_91->Expr);
            MatchExpr(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Expression(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
            IO_WriteS(Tree_f, (STRING)"  }", 3L);
            IO_WriteNl(Tree_f);
          } else {
            IO_WriteS(Tree_f, (STRING)"   return ", 10L);
            Expression(W_91->Expr);
            IO_WriteS(Tree_f, (STRING)";", 1L);
            IO_WriteNl(Tree_f);
          }
          break;
        case kPredicate:;
          IO_WriteS(Tree_f, (STRING)"   return true;", 15L);
          IO_WriteNl(Tree_f);
          break;
        }
      }
      if (W_91->HasTempos && !TemposDone) {
        IO_WriteS(Tree_f, (STRING)" }", 2L);
        IO_WriteNl(Tree_f);
      }
      if (W_91->HasExit || Optimize_NeedsMatch(W_91->Tests)) {
        IO_WriteS(Tree_f, (STRING)"yyL", 3L);
        Tree_WN(RuleCount);
        IO_WriteS(Tree_f, (STRING)":;", 2L);
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
  struct S_15 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Decision) {
    {
      register struct S_16 *W_92 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_93 = &t->U_1.V_105.Decision;

        IO_WriteNl(Tree_f);
        IO_WriteS(Tree_f, (STRING)"  switch (", 10L);
        C_ImplC(W_93->OneTest->U_1.V_97.OneTest.Path);
        IO_WriteS(Tree_f, (STRING)"->Kind) {", 9L);
        IO_WriteNl(Tree_f);
        W_92->n = i;
        while (W_92->n > 0) {
          if (!Sets_IsEmpty(t->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types)) {
            Case(t->U_1.V_105.Decision.OneTest);
            CommonTestElim(t->U_1.V_105.Decision.Then);
            if (!Optimize_NeedsNoFinale(t->U_1.V_105.Decision.Then)) {
              IO_WriteS(Tree_f, (STRING)"  break;", 8L);
              IO_WriteNl(Tree_f);
            }
          }
          t = t->U_1.V_105.Decision.Else;
          DEC(W_92->n);
        }
        IO_WriteS(Tree_f, (STRING)"  }", 3L);
        IO_WriteNl(Tree_f);
        IO_WriteNl(Tree_f);
        CommonTestElim(t);
        return;
      }
    }
  }
  if (t->U_1.V_1.Kind == Tree_TestKind) {
    {
      register Tree_yTestKind *W_94 = &t->U_1.V_98.TestKind;

      IO_WriteS(Tree_f, (STRING)"  case k", 8L);
      Tree_WI(W_94->Name);
      IO_WriteS(Tree_f, (STRING)":", 1L);
      IO_WriteNl(Tree_f);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TestIsType) {
    {
      register Tree_yTestIsType *W_95 = &t->U_1.V_99.TestIsType;

      Case(W_95->TypeDesc);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_NodeTypes) {
    {
      register Tree_yNodeTypes *W_96 = &t->U_1.V_89.NodeTypes;

      {
        LONGCARD B_3 = Sets_Minimum(&W_96->Types), B_4 = Sets_Maximum(&W_96->Types);

        if (B_3 <= B_4)
          for (j = B_3;; j += 1) {
            if (Sets_IsElement(j, &W_96->Types)) {
              TheClass = Semantics_LookupClass(W_96->TreeName->U_1.V_29.TreeName.Classes, j);
              IO_WriteS(Tree_f, (STRING)"  case k", 8L);
              Tree_WI(TheClass->U_1.V_5.Class.Name);
              IO_WriteS(Tree_f, (STRING)":", 1L);
              IO_WriteNl(Tree_f);
            }
            if (j >= B_4) break;
          }
      }
      return;
    }
  }
}

void C_BeginC
# ifdef __STDC__
()
# else
()
# endif
{
}

void C_CloseC
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

void BEGIN_C()
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
    BEGIN_Strings();
    BEGIN_StringMem();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Sets();
    BEGIN_Semantics();
    BEGIN_Optimize();
    BEGIN_Tree();

    C_yyf = IO_StdOutput;
    C_Exit = yyExit;
    C_BeginC();
  }
}
