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

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Mod
#include "Mod.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Positions
#include "Positions.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Optimize
#include "Optimize.h"
#endif

IO_tFile Optimize_yyf;
PROC Optimize_Exit;

static BOOLEAN gHasExit, gHasAssign, gHasTargetCode, gHasRejectOrFail;
static Tree_tTree gRule, nNoDecision, nNoTest;
static BOOLEAN IsDisjoint ARGS((Sets_tSet s1, Sets_tSet s2));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_3 {
    union {
        struct {
            struct S_5 {
                Tree_tTree yyV1;
                Tree_tTree yyV2;
            } yyR1;
        } V_1;
        struct {
            struct S_4 {
                Tree_tTree yyV1;
                Tree_tTree yyV2;
                Sets_tSet yyV3;
                Tree_tTree yyV4;
                SHORTCARD yyV5;
                Sets_tSet yyV6;
            } yyR2;
        } V_2;
    } U_1;
};
struct S_6 {
    union {
        char dummy;
    } U_1;
};
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN NeedsMatch2 ARGS((Tree_tTree yyP4, Tree_tTree yyP3));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
struct S_9 {
    union {
        struct {
            struct S_10 {
                Tree_tTree yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
struct S_11 {
    union {
        char dummy;
    } U_1;
};
struct S_12 {
    union {
        struct {
            struct S_13 {
                Tree_tTree yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static void CollectTests ARGS((Tree_tTree yyP11, Tree_tTree yyP10));
struct S_14 {
    union {
        struct {
            struct S_15 {
                Tree_tTree yyV1;
            } yyR1;
        } V_1;
    } U_1;
};
static void CollectTests2 ARGS((Tree_tTree yyP14, Tree_tTree yyP13, Tree_tTree yyP12, Tree_tTree *yyP15));
struct S_16 {
    union {
        struct {
            struct S_20 {
                Tree_tTree yyV1;
                Tree_tTree yyV2;
            } yyR1;
        } V_1;
        struct {
            struct S_19 {
                Tree_tTree yyV1;
            } yyR2;
        } V_2;
        struct {
            struct S_18 {
                Tree_tTree yyV1;
            } yyR3;
        } V_3;
        struct {
            struct S_17 {
                Tree_tTree yyV1;
            } yyR4;
        } V_4;
    } U_1;
};
static BOOLEAN IsSamePath ARGS((Tree_tTree yyP17, Tree_tTree yyP16));
struct S_21 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN IsSameType ARGS((Tree_tTree yyP19, Tree_tTree yyP18));
struct S_22 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN IsSameTest ARGS((Tree_tTree yyP21, Tree_tTree yyP20));
struct S_23 {
    union {
        char dummy;
    } U_1;
};
static void BuildTree ARGS((Tree_tTree yyP23, Tree_tTree yyP22, Tree_tTree *yyP24));
struct S_24 {
    union {
        struct {
            struct S_25 {
                Tree_tTree yyV1;
                Tree_tTree yyV2;
            } yyR1;
        } V_1;
    } U_1;
};
static void BuildTree2 ARGS((Tree_tTree t, Tree_tTree d, Tree_tTree *yyP25));
struct S_26 {
    union {
        struct {
            struct S_32 {
                Tree_tTree yyV1;
            } yyR1;
        } V_1;
        struct {
            struct S_31 {
                Tree_tTree yyV1;
            } yyR2;
        } V_2;
        struct {
            struct S_30 {
                Tree_tTree yyV1;
            } yyR3;
        } V_3;
        struct {
            struct S_29 {
                Tree_tTree yyV1;
            } yyR4;
        } V_4;
        struct {
            struct S_28 {
                Tree_tTree yyV1;
            } yyR6;
        } V_5;
        struct {
            struct S_27 {
                Tree_tTree yyV1;
            } yyR7;
        } V_6;
    } U_1;
};
static BOOLEAN HasInterference ARGS((Tree_tTree yyP27, Tree_tTree yyP26));
struct S_33 {
    union {
        char dummy;
    } U_1;
};
static void UpdateChange ARGS((Tree_tTree yyP29, Tree_tTree yyP28));
struct S_34 {
    union {
        char dummy;
    } U_1;
};
static BOOLEAN IsChanged ARGS((Tree_tTree yyP31, Tree_tTree yyP30));
struct S_35 {
    union {
        char dummy;
    } U_1;
};
static void FindCases ARGS((Tree_tTree yyP32, Tree_tTree *yyP35, SHORTCARD *yyP34, Sets_tSet *yyP33));
struct S_36 {
    union {
        struct {
            struct S_40 {
                Tree_tTree yyV1;
                SHORTCARD yyV2;
                Sets_tSet yyV3;
                Tree_tTree yyV4;
                SHORTCARD yyV5;
                Sets_tSet yyV6;
                SHORTCARD k;
                Sets_tSet s;
            } yyR1;
        } V_1;
        struct {
            struct S_39 {
                Tree_tTree yyV1;
                SHORTCARD yyV2;
                Sets_tSet yyV3;
                Tree_tTree yyV4;
                SHORTCARD yyV5;
                Sets_tSet yyV6;
                SHORTCARD k;
                Sets_tSet s;
            } yyR2;
        } V_2;
        struct {
            struct S_38 {
                Tree_tTree yyV1;
                SHORTCARD yyV2;
                Sets_tSet yyV3;
                Tree_tTree yyV4;
                SHORTCARD yyV5;
                Sets_tSet yyV6;
            } yyR3;
        } V_3;
        struct {
            struct S_37 {
                Tree_tTree yyV1;
                SHORTCARD yyV2;
                Sets_tSet yyV3;
            } yyR4;
        } V_4;
    } U_1;
};
static void MarkCases ARGS((Tree_tTree yyP38, SHORTCARD yyP37, Sets_tSet yyP36));
struct S_41 {
    union {
        char dummy;
    } U_1;
};
static void ElimDeadTests ARGS((Tree_tTree yyP42, Tree_tTree yyP41, BOOLEAN yyP40, Sets_tSet yyP39));
struct S_42 {
    union {
        struct {
            struct S_48 {
                Sets_tSet s;
                Tree_tTree yyV1;
                Sets_tSet yyV2;
            } yyR1;
        } V_1;
        struct {
            struct S_47 {
                Sets_tSet s;
                Tree_tTree yyV1;
                Sets_tSet yyV2;
            } yyR2;
        } V_2;
        struct {
            struct S_46 {
                Sets_tSet types;
                Sets_tSet s2;
                Tree_tTree yyV1;
                Sets_tSet yyV2;
            } yyR3;
        } V_3;
        struct {
            struct S_45 {
                Sets_tSet types;
                Sets_tSet s2;
                Tree_tTree yyV1;
                Sets_tSet yyV2;
            } yyR4;
        } V_4;
        struct {
            struct S_44 {
                Tree_tTree yyV1;
                Sets_tSet yyV2;
                Tree_tTree yyV3;
                Sets_tSet yyV4;
            } yyR5;
        } V_5;
        struct {
            struct S_43 {
                Tree_tTree yyV1;
                Sets_tSet yyV2;
            } yyR6;
        } V_6;
    } U_1;
};
static BOOLEAN IsDeadEnd ARGS((Tree_tTree yyP43));
struct S_49 {
    union {
        char dummy;
    } U_1;
};
static void ReportWarning ARGS((Tree_tTree yyP44));
struct S_50 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static BOOLEAN IsDisjoint
# ifdef __STDC__
(Sets_tSet s1, Sets_tSet s2)
# else
(s1, s2)
Sets_tSet s1, s2;
# endif
{
  Sets_tSet s;
  BOOLEAN Result;

  Sets_MakeSet(&s, Sets_Size(&s1));
  Sets_Assign(&s, s1);
  Sets_Intersection(&s, s2);
  Result = Sets_IsEmpty(s);
  Sets_ReleaseSet(&s);
  return Result;
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Optimize, routine ", 32L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Optimize_Exit)();
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

void Optimize_Optimize
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  struct S_3 yyTempo;

  if (t->U_1.V_1.Kind == Tree_Spec) {
    {
      register struct S_5 *W_1 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_ySpec *W_2 = &t->U_1.V_26.Spec;

        W_1->yyV1 = (Tree_tTree)Tree_yyPoolFreePtr;
        if ((ADDRESS)W_1->yyV1 >= Tree_yyPoolMaxPtr) {
          W_1->yyV1 = Tree_yyAlloc();
        }
        INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoDecision]);
        W_1->yyV1->U_1.V_2.yyHead.yyMark = 0;
        W_1->yyV1->U_1.V_1.Kind = Tree_NoDecision;
        nNoDecision = W_1->yyV1;
        W_1->yyV2 = (Tree_tTree)Tree_yyPoolFreePtr;
        if ((ADDRESS)W_1->yyV2 >= Tree_yyPoolMaxPtr) {
          W_1->yyV2 = Tree_yyAlloc();
        }
        INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_NoTest]);
        W_1->yyV2->U_1.V_2.yyHead.yyMark = 0;
        W_1->yyV2->U_1.V_1.Kind = Tree_NoTest;
        nNoTest = W_1->yyV2;
        Optimize_Optimize(W_2->Routines);
        return;
      }
    }
  }
  if (Tree_IsType(t, Tree_Routine)) {
    {
      register struct S_4 *W_3 = &yyTempo.U_1.V_2.yyR2;

      {
        register Tree_yRoutine *W_4 = &t->U_1.V_32.Routine;

        Optimize_RuleProperties(W_4->Rules);
        CollectTests(W_4->Rules, W_4->InForm);
        BuildTree(W_4->Rules, nNoDecision, &W_3->yyV1);
        W_4->Decisions = W_3->yyV1;
        ElimDeadTests(W_4->Decisions, W_3->yyV2, FALSE, W_3->yyV3);
        FindCases(W_4->Decisions, &W_3->yyV4, &W_3->yyV5, &W_3->yyV6);
        MarkCases(W_4->Decisions, W_3->yyV5, W_3->yyV6);
        Optimize_Optimize(W_4->Next);
        return;
      }
    }
  }
}

void Optimize_RuleProperties
# ifdef __STDC__
(Tree_tTree yyP1)
# else
(yyP1)
Tree_tTree yyP1;
# endif
{
  struct S_6 yyTempo;

  switch (yyP1->U_1.V_1.Kind) {
  case Tree_Spec:;
    {
      register Tree_ySpec *W_5 = &yyP1->U_1.V_26.Spec;

      Optimize_RuleProperties(W_5->Routines);
      return;
    }
    break;
  case Tree_Routine:;
  case Tree_Procedure:;
  case Tree_Function:;
  case Tree_Predicate:;
    {
      register Tree_yRoutine *W_6 = &yyP1->U_1.V_32.Routine;

      Optimize_RuleProperties(W_6->Rules);
      Optimize_RuleProperties(W_6->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_7 = &yyP1->U_1.V_42.Rule;

      gHasExit = FALSE;
      gHasAssign = FALSE;
      gHasTargetCode = FALSE;
      gHasRejectOrFail = FALSE;
      Optimize_RuleProperties(W_7->Statements);
      Optimize_RuleProperties(W_7->Exprs);
      Optimize_RuleProperties(W_7->Expr);
      W_7->HasExit = gHasExit;
      W_7->HasAssign = gHasAssign;
      W_7->HasTargetCode = gHasTargetCode;
      W_7->HasRejectOrFail = gHasRejectOrFail;
      Optimize_RuleProperties(W_7->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_8 = &yyP1->U_1.V_76.ProcCall;

      Optimize_RuleProperties(W_8->Call);
      Optimize_RuleProperties(W_8->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_9 = &yyP1->U_1.V_78.Assignment;

      gHasAssign = TRUE;
      Optimize_RuleProperties(W_9->Adr);
      Optimize_RuleProperties(W_9->Expr);
      Optimize_RuleProperties(W_9->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_10 = &yyP1->U_1.V_77.Condition;

      gHasExit = TRUE;
      Optimize_RuleProperties(W_10->Next);
      return;
    }
    break;
  case Tree_Reject:;
    {
      register Tree_yReject *W_11 = &yyP1->U_1.V_79.Reject;

      gHasExit = TRUE;
      gHasRejectOrFail = TRUE;
      Optimize_RuleProperties(W_11->Next);
      return;
    }
    break;
  case Tree_Fail:;
    {
      register Tree_yFail *W_12 = &yyP1->U_1.V_80.Fail;

      gHasRejectOrFail = TRUE;
      Optimize_RuleProperties(W_12->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_13 = &yyP1->U_1.V_81.TargetStmt;

      gHasTargetCode = TRUE;
      Optimize_RuleProperties(W_13->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_14 = &yyP1->U_1.V_75.Statement;

      Optimize_RuleProperties(W_14->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_15 = &yyP1->U_1.V_58.OneExpr;

      Optimize_RuleProperties(W_15->Expr);
      Optimize_RuleProperties(W_15->Next);
      return;
    }
    break;
  case Tree_Expr:;
  case Tree_Compose:;
  case Tree_VarUse:;
  case Tree_AttrDesc:;
  case Tree_Nil:;
  case Tree_Call:;
  case Tree_Binary:;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
  case Tree_Index:;
  case Tree_Parents:;
  case Tree_TargetExpr:;
  case Tree_StringExpr:;
    {
      register Tree_yExpr *W_16 = &yyP1->U_1.V_60.Expr;

      gHasExit = gHasExit || Optimize_NeedsMatch(yyP1);
      return;
    }
    break;
  default :
    break;
  }
}

BOOLEAN Optimize_NeedsMatch
# ifdef __STDC__
(Tree_tTree yyP2)
# else
(yyP2)
Tree_tTree yyP2;
# endif
{
  struct S_7 yyTempo;

  if (yyP2->U_1.V_1.Kind == Tree_TestValue) {
    for (;;) {
      {
        register Tree_yTestValue *W_17 = &yyP2->U_1.V_102.TestValue;

        if (!(Optimize_NeedsMatch(W_17->Expr) || Optimize_NeedsMatch(W_17->Next))) {
          goto EXIT_1;
        }
        return TRUE;
      }
    } EXIT_1:;
  }
  switch (yyP2->U_1.V_1.Kind) {
  case Tree_OneTest:;
  case Tree_TestKind:;
  case Tree_TestIsType:;
  case Tree_TestNil:;
  case Tree_TestNonlin:;
  case Tree_TestValue:;
    for (;;) {
      {
        register Tree_yOneTest *W_18 = &yyP2->U_1.V_97.OneTest;

        if (!Optimize_NeedsMatch(W_18->Next)) {
          goto EXIT_2;
        }
        return TRUE;
      }
    } EXIT_2:;
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    for (;;) {
      {
        register Tree_yOneExpr *W_19 = &yyP2->U_1.V_58.OneExpr;

        if (!(Optimize_NeedsMatch(W_19->Expr) || Optimize_NeedsMatch(W_19->Next))) {
          goto EXIT_3;
        }
        return TRUE;
      }
    } EXIT_3:;
    break;
  case Tree_Compose:;
    for (;;) {
      {
        register Tree_yCompose *W_20 = &yyP2->U_1.V_61.Compose;

        if (!Optimize_NeedsMatch(W_20->Exprs)) {
          goto EXIT_4;
        }
        return TRUE;
      }
    } EXIT_4:;
    break;
  case Tree_Call:;
    for (;;) {
      {
        register Tree_yCall *W_21 = &yyP2->U_1.V_65.Call;

        if (!(Optimize_NeedsMatch(W_21->Expr) || Optimize_NeedsMatch(W_21->Exprs) || W_21->Object != Tree_NoTree && NeedsMatch2(W_21->Patterns, W_21->Object->U_1.V_32.Routine.OutForm))) {
          goto EXIT_5;
        }
        return TRUE;
      }
    } EXIT_5:;
    break;
  case Tree_Binary:;
    for (;;) {
      {
        register Tree_yBinary *W_22 = &yyP2->U_1.V_66.Binary;

        if (!(Optimize_NeedsMatch(W_22->Lop) || Optimize_NeedsMatch(W_22->Rop))) {
          goto EXIT_6;
        }
        return TRUE;
      }
    } EXIT_6:;
    break;
  case Tree_Parents:;
    for (;;) {
      {
        register Tree_yParents *W_23 = &yyP2->U_1.V_70.Parents;

        if (!Optimize_NeedsMatch(W_23->Expr)) {
          goto EXIT_7;
        }
        return TRUE;
      }
    } EXIT_7:;
    break;
  case Tree_PreOperator:;
    for (;;) {
      {
        register Tree_yPreOperator *W_24 = &yyP2->U_1.V_67.PreOperator;

        if (!Optimize_NeedsMatch(W_24->Expr)) {
          goto EXIT_8;
        }
        return TRUE;
      }
    } EXIT_8:;
    break;
  case Tree_PostOperator:;
    for (;;) {
      {
        register Tree_yPostOperator *W_25 = &yyP2->U_1.V_68.PostOperator;

        if (!Optimize_NeedsMatch(W_25->Expr)) {
          goto EXIT_9;
        }
        return TRUE;
      }
    } EXIT_9:;
    break;
  case Tree_Index:;
    for (;;) {
      {
        register Tree_yIndex *W_26 = &yyP2->U_1.V_69.Index;

        if (!(Optimize_NeedsMatch(W_26->Expr) || Optimize_NeedsMatch(W_26->Exprs))) {
          goto EXIT_10;
        }
        return TRUE;
      }
    } EXIT_10:;
    break;
  default :
    break;
  }
  return FALSE;
}

static BOOLEAN NeedsMatch2
# ifdef __STDC__
(Tree_tTree yyP4, Tree_tTree yyP3)
# else
(yyP4, yyP3)
Tree_tTree yyP4;
Tree_tTree yyP3;
# endif
{
  struct S_8 yyTempo;

  if (yyP4->U_1.V_1.Kind == Tree_OnePattern) {
    for (;;) {
      {
        register Tree_yOnePattern *W_27 = &yyP4->U_1.V_45.OnePattern;

        if (!(NeedsMatch2(W_27->Pattern, yyP3) || NeedsMatch2(W_27->Next, yyP3->U_1.V_86.Formal.Next))) {
          goto EXIT_11;
        }
        return TRUE;
      }
    } EXIT_11:;
  }
  if (yyP4->U_1.V_1.Kind == Tree_Decompose) {
    for (;;) {
      {
        register Tree_yDecompose *W_28 = &yyP4->U_1.V_50.Decompose;

        {
          register Tree_yFormal *W_29 = &yyP3->U_1.V_86.Formal;

          if (!(yyP3->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind == Tree_UserType || Sets_IsNotEqual(W_28->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.Types, yyP3->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.Types) || NeedsMatch2(W_28->Patterns, W_28->Object->U_1.V_5.Class.Formals))) {
            goto EXIT_12;
          }
          return TRUE;
        }
      }
    } EXIT_12:;
  }
  if (yyP4->U_1.V_1.Kind == Tree_VarDef) {
    for (;;) {
      {
        register Tree_yVarDef *W_30 = &yyP4->U_1.V_51.VarDef;

        if (!(W_30->Object != Tree_NoTree)) {
          goto EXIT_13;
        }
        return TRUE;
      }
    } EXIT_13:;
  }
  if (yyP4->U_1.V_1.Kind == Tree_NilTest) {
    return TRUE;
  }
  if (yyP4->U_1.V_1.Kind == Tree_Value) {
    return TRUE;
  }
  return FALSE;
}

BOOLEAN Optimize_NeedsTempo
# ifdef __STDC__
(Tree_tTree yyP5, Tree_tTree *yyP6)
# else
(yyP5, yyP6)
Tree_tTree yyP5;
Tree_tTree *yyP6;
# endif
{
  struct S_9 yyTempo;

  if (yyP5->U_1.V_1.Kind == Tree_Decision) {
    {
      register struct S_10 *W_31 = &yyTempo.U_1.V_1.yyR1;

      for (;;) {
        {
          register Tree_yDecision *W_32 = &yyP5->U_1.V_105.Decision;

          if (!Optimize_NeedsTempo(yyP5->U_1.V_105.Decision.Then, &W_31->yyV1)) {
            goto EXIT_14;
          }
          *yyP6 = W_31->yyV1;
          return TRUE;
        }
      } EXIT_14:;
    }
  }
  if (yyP5->U_1.V_1.Kind == Tree_Decided) {
    if (yyP5->U_1.V_106.Decided.Rule->U_1.V_42.Rule.HasTempos == TRUE) {
      *yyP6 = yyP5->U_1.V_106.Decided.Rule;
      return TRUE;
    }
  }
  return FALSE;
}

BOOLEAN Optimize_NeedsNoFinale
# ifdef __STDC__
(Tree_tTree yyP7)
# else
(yyP7)
Tree_tTree yyP7;
# endif
{
  struct S_11 yyTempo;

  if (yyP7->U_1.V_1.Kind == Tree_Decision) {
    for (;;) {
      {
        register Tree_yDecision *W_33 = &yyP7->U_1.V_105.Decision;

        if (!Optimize_NeedsNoFinale(yyP7->U_1.V_105.Decision.Else)) {
          goto EXIT_15;
        }
        return TRUE;
      }
    } EXIT_15:;
  }
  if (yyP7->U_1.V_1.Kind == Tree_Decided) {
    if (yyP7->U_1.V_106.Decided.Rule->U_1.V_42.Rule.HasExit == FALSE) {
      return TRUE;
    }
    for (;;) {
      {
        register Tree_yDecided *W_34 = &yyP7->U_1.V_106.Decided;

        if (!Optimize_NeedsNoFinale(yyP7->U_1.V_106.Decided.Else)) {
          goto EXIT_16;
        }
        return TRUE;
      }
    } EXIT_16:;
  }
  return FALSE;
}

void Optimize_GetRule
# ifdef __STDC__
(Tree_tTree yyP8, Tree_tTree *yyP9)
# else
(yyP8, yyP9)
Tree_tTree yyP8;
Tree_tTree *yyP9;
# endif
{
  struct S_12 yyTempo;

  if (yyP8->U_1.V_1.Kind == Tree_Decision) {
    {
      register struct S_13 *W_35 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yDecision *W_36 = &yyP8->U_1.V_105.Decision;

        Optimize_GetRule(yyP8->U_1.V_105.Decision.Then, &W_35->yyV1);
        *yyP9 = W_35->yyV1;
        return;
      }
    }
  }
  if (yyP8->U_1.V_1.Kind == Tree_Decided) {
    *yyP9 = yyP8->U_1.V_106.Decided.Rule;
    return;
  }
}

static void CollectTests
# ifdef __STDC__
(Tree_tTree yyP11, Tree_tTree yyP10)
# else
(yyP11, yyP10)
Tree_tTree yyP11;
Tree_tTree yyP10;
# endif
{
  struct S_14 yyTempo;

  if (yyP11->U_1.V_1.Kind == Tree_Rule) {
    {
      register struct S_15 *W_37 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yRule *W_38 = &yyP11->U_1.V_42.Rule;

        CollectTests2(W_38->Patterns, yyP10, nNoTest, &W_37->yyV1);
        W_38->Tests = W_37->yyV1;
        CollectTests(W_38->Next, yyP10);
        return;
      }
    }
  }
}

static void CollectTests2
# ifdef __STDC__
(Tree_tTree yyP14, Tree_tTree yyP13, Tree_tTree yyP12, Tree_tTree *yyP15)
# else
(yyP14, yyP13, yyP12, yyP15)
Tree_tTree yyP14;
Tree_tTree yyP13;
Tree_tTree yyP12;
Tree_tTree *yyP15;
# endif
{
  struct S_16 yyTempo;

  if (yyP14->U_1.V_1.Kind == Tree_OnePattern) {
    if (yyP13->U_1.V_1.Kind == Tree_Formal) {
      {
        register struct S_20 *W_39 = &yyTempo.U_1.V_1.yyR1;

        {
          register Tree_yOnePattern *W_40 = &yyP14->U_1.V_45.OnePattern;

          {
            register Tree_yFormal *W_41 = &yyP13->U_1.V_86.Formal;

            CollectTests2(yyP14->U_1.V_45.OnePattern.Next, yyP13->U_1.V_86.Formal.Next, yyP12, &W_39->yyV1);
            CollectTests2(yyP14->U_1.V_45.OnePattern.Pattern, yyP13, W_39->yyV1, &W_39->yyV2);
            *yyP15 = W_39->yyV2;
            return;
          }
        }
      }
    }
  }
  if (yyP14->U_1.V_1.Kind == Tree_Decompose) {
    if (yyP13->U_1.V_1.Kind == Tree_Formal) {
      {
        register struct S_19 *W_42 = &yyTempo.U_1.V_2.yyR2;

        for (;;) {
          {
            register Tree_yDecompose *W_43 = &yyP14->U_1.V_50.Decompose;

            {
              register Tree_yFormal *W_44 = &yyP13->U_1.V_86.Formal;

              if (!(yyP13->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind != Tree_UserType && Sets_IsEqual(&W_43->Object->U_1.V_5.Class.TypeDesc->U_1.V_89.NodeTypes.Types, &yyP13->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.Types))) {
                goto EXIT_17;
              }
              CollectTests2(W_43->Patterns, W_43->Object->U_1.V_5.Class.Formals, yyP12, &W_42->yyV1);
              *yyP15 = W_42->yyV1;
              return;
            }
          }
        } EXIT_17:;
      }
      {
        register struct S_18 *W_45 = &yyTempo.U_1.V_3.yyR3;

        for (;;) {
          {
            register Tree_yDecompose *W_46 = &yyP14->U_1.V_50.Decompose;

            {
              register Tree_yFormal *W_47 = &yyP13->U_1.V_86.Formal;

              if (!(yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.Extensions->U_1.V_1.Kind == Tree_NoClass)) {
                goto EXIT_18;
              }
              CollectTests2(yyP14->U_1.V_50.Decompose.Patterns, yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.Formals, yyP12, &W_45->yyV1);
              *yyP15 = (Tree_tTree)Tree_yyPoolFreePtr;
              if ((ADDRESS)(*yyP15) >= Tree_yyPoolMaxPtr) {
                *yyP15 = Tree_yyAlloc();
              }
              INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestKind]);
              (*yyP15)->U_1.V_2.yyHead.yyMark = 0;
              (*yyP15)->U_1.V_1.Kind = Tree_TestKind;
              {
                register Tree_yTestKind *W_48 = &(*yyP15)->U_1.V_98.TestKind;

                W_48->Next = W_45->yyV1;
                W_48->Path = yyP14->U_1.V_50.Decompose.Path;
                W_48->TypeDesc = yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.TypeDesc;
                W_48->Name = yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.Name;
              }
              return;
            }
          }
        } EXIT_18:;
      }
    }
    {
      register struct S_17 *W_49 = &yyTempo.U_1.V_4.yyR4;

      {
        register Tree_yDecompose *W_50 = &yyP14->U_1.V_50.Decompose;

        CollectTests2(yyP14->U_1.V_50.Decompose.Patterns, yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.Formals, yyP12, &W_49->yyV1);
        *yyP15 = (Tree_tTree)Tree_yyPoolFreePtr;
        if ((ADDRESS)(*yyP15) >= Tree_yyPoolMaxPtr) {
          *yyP15 = Tree_yyAlloc();
        }
        INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestIsType]);
        (*yyP15)->U_1.V_2.yyHead.yyMark = 0;
        (*yyP15)->U_1.V_1.Kind = Tree_TestIsType;
        {
          register Tree_yTestIsType *W_51 = &(*yyP15)->U_1.V_99.TestIsType;

          W_51->Next = W_49->yyV1;
          W_51->Path = yyP14->U_1.V_50.Decompose.Path;
          W_51->TypeDesc = yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.TypeDesc;
          W_51->Name = yyP14->U_1.V_50.Decompose.Object->U_1.V_5.Class.Name;
        }
        return;
      }
    }
  }
  if (yyP14->U_1.V_1.Kind == Tree_VarDef) {
    for (;;) {
      {
        register Tree_yVarDef *W_52 = &yyP14->U_1.V_51.VarDef;

        if (!(W_52->Object != Tree_NoTree)) {
          goto EXIT_19;
        }
        *yyP15 = (Tree_tTree)Tree_yyPoolFreePtr;
        if ((ADDRESS)(*yyP15) >= Tree_yyPoolMaxPtr) {
          *yyP15 = Tree_yyAlloc();
        }
        INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestNonlin]);
        (*yyP15)->U_1.V_2.yyHead.yyMark = 0;
        (*yyP15)->U_1.V_1.Kind = Tree_TestNonlin;
        {
          register Tree_yTestNonlin *W_53 = &(*yyP15)->U_1.V_101.TestNonlin;

          W_53->Next = yyP12;
          W_53->Path = W_52->Object->U_1.V_86.Formal.Path;
          W_53->Path2 = yyP14->U_1.V_51.VarDef.Path;
          W_53->TypeDesc = W_52->Object->U_1.V_86.Formal.TypeDesc;
        }
        return;
      }
    } EXIT_19:;
  }
  if (yyP14->U_1.V_1.Kind == Tree_NilTest) {
    *yyP15 = (Tree_tTree)Tree_yyPoolFreePtr;
    if ((ADDRESS)(*yyP15) >= Tree_yyPoolMaxPtr) {
      *yyP15 = Tree_yyAlloc();
    }
    INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestNil]);
    (*yyP15)->U_1.V_2.yyHead.yyMark = 0;
    (*yyP15)->U_1.V_1.Kind = Tree_TestNil;
    {
      register Tree_yTestNil *W_54 = &(*yyP15)->U_1.V_100.TestNil;

      W_54->Next = yyP12;
      W_54->Path = yyP14->U_1.V_52.NilTest.Path;
    }
    return;
  }
  if (yyP14->U_1.V_1.Kind == Tree_Value) {
    if (yyP13->U_1.V_1.Kind == Tree_Formal) {
      *yyP15 = (Tree_tTree)Tree_yyPoolFreePtr;
      if ((ADDRESS)(*yyP15) >= Tree_yyPoolMaxPtr) {
        *yyP15 = Tree_yyAlloc();
      }
      INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_TestValue]);
      (*yyP15)->U_1.V_2.yyHead.yyMark = 0;
      (*yyP15)->U_1.V_1.Kind = Tree_TestValue;
      {
        register Tree_yTestValue *W_55 = &(*yyP15)->U_1.V_102.TestValue;

        W_55->Next = yyP12;
        W_55->Path = yyP14->U_1.V_55.Value.Path;
        W_55->Expr = yyP14->U_1.V_55.Value.Expr;
        W_55->TypeDesc = yyP13->U_1.V_86.Formal.TypeDesc;
      }
      return;
    }
  }
  *yyP15 = yyP12;
  return;
}

static BOOLEAN IsSamePath
# ifdef __STDC__
(Tree_tTree yyP17, Tree_tTree yyP16)
# else
(yyP17, yyP16)
Tree_tTree yyP17;
Tree_tTree yyP16;
# endif
{
  struct S_21 yyTempo;

  if (yyP17->U_1.V_1.Kind == Tree_Var) {
    if (yyP16->U_1.V_1.Kind == Tree_Var) {
      if (yyP17->U_1.V_92.Var.Name == yyP16->U_1.V_92.Var.Name) {
        return TRUE;
      }
    }
  }
  if (yyP17->U_1.V_1.Kind == Tree_ConsType) {
    if (yyP16->U_1.V_1.Kind == Tree_ConsType) {
      if (yyP17->U_1.V_93.ConsType.Name == yyP16->U_1.V_93.ConsType.Name) {
        for (;;) {
          {
            register Tree_yConsType *W_56 = &yyP17->U_1.V_93.ConsType;

            {
              register Tree_yConsType *W_57 = &yyP16->U_1.V_93.ConsType;

              if (!IsSamePath(yyP17->U_1.V_93.ConsType.Next, yyP16->U_1.V_93.ConsType.Next)) {
                goto EXIT_20;
              }
              return TRUE;
            }
          }
        } EXIT_20:;
      }
    }
  }
  if (yyP17->U_1.V_1.Kind == Tree_Field) {
    if (yyP16->U_1.V_1.Kind == Tree_Field) {
      if (yyP17->U_1.V_94.Field.Name == yyP16->U_1.V_94.Field.Name) {
        for (;;) {
          {
            register Tree_yField *W_58 = &yyP17->U_1.V_94.Field;

            {
              register Tree_yField *W_59 = &yyP16->U_1.V_94.Field;

              if (!IsSamePath(yyP17->U_1.V_94.Field.Next, yyP16->U_1.V_94.Field.Next)) {
                goto EXIT_21;
              }
              return TRUE;
            }
          }
        } EXIT_21:;
      }
    }
  }
  return FALSE;
}

static BOOLEAN IsSameType
# ifdef __STDC__
(Tree_tTree yyP19, Tree_tTree yyP18)
# else
(yyP19, yyP18)
Tree_tTree yyP19;
Tree_tTree yyP18;
# endif
{
  struct S_22 yyTempo;

  if (yyP19->U_1.V_1.Kind == Tree_NodeTypes) {
    if (yyP18->U_1.V_1.Kind == Tree_NodeTypes) {
      if (yyP19->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name == yyP18->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Name) {
        if (Sets_IsEqual(&yyP19->U_1.V_89.NodeTypes.Types, &yyP18->U_1.V_89.NodeTypes.Types)) {
          return TRUE;
        }
      }
    }
  }
  if (yyP19->U_1.V_1.Kind == Tree_UserType) {
    if (yyP18->U_1.V_1.Kind == Tree_UserType) {
      if (yyP19->U_1.V_90.UserType.Type == yyP18->U_1.V_90.UserType.Type) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

static BOOLEAN IsSameTest
# ifdef __STDC__
(Tree_tTree yyP21, Tree_tTree yyP20)
# else
(yyP21, yyP20)
Tree_tTree yyP21;
Tree_tTree yyP20;
# endif
{
  struct S_23 yyTempo;

  if (yyP21->U_1.V_1.Kind == Tree_TestKind) {
    if (yyP20->U_1.V_1.Kind == Tree_TestKind) {
      for (;;) {
        {
          register Tree_yTestKind *W_60 = &yyP21->U_1.V_98.TestKind;

          {
            register Tree_yTestKind *W_61 = &yyP20->U_1.V_98.TestKind;

            if (!IsSamePath(yyP21->U_1.V_98.TestKind.Path, yyP20->U_1.V_98.TestKind.Path)) {
              goto EXIT_22;
            }
            if (!IsSameType(yyP21->U_1.V_98.TestKind.TypeDesc, yyP20->U_1.V_98.TestKind.TypeDesc)) {
              goto EXIT_22;
            }
            return TRUE;
          }
        }
      } EXIT_22:;
    }
  }
  if (yyP21->U_1.V_1.Kind == Tree_TestIsType) {
    if (yyP20->U_1.V_1.Kind == Tree_TestIsType) {
      for (;;) {
        {
          register Tree_yTestIsType *W_62 = &yyP21->U_1.V_99.TestIsType;

          {
            register Tree_yTestIsType *W_63 = &yyP20->U_1.V_99.TestIsType;

            if (!IsSamePath(yyP21->U_1.V_99.TestIsType.Path, yyP20->U_1.V_99.TestIsType.Path)) {
              goto EXIT_23;
            }
            if (!IsSameType(yyP21->U_1.V_99.TestIsType.TypeDesc, yyP20->U_1.V_99.TestIsType.TypeDesc)) {
              goto EXIT_23;
            }
            return TRUE;
          }
        }
      } EXIT_23:;
    }
  }
  if (yyP21->U_1.V_1.Kind == Tree_TestNil) {
    if (yyP20->U_1.V_1.Kind == Tree_TestNil) {
      for (;;) {
        {
          register Tree_yTestNil *W_64 = &yyP21->U_1.V_100.TestNil;

          {
            register Tree_yTestNil *W_65 = &yyP20->U_1.V_100.TestNil;

            if (!IsSamePath(yyP21->U_1.V_100.TestNil.Path, yyP20->U_1.V_100.TestNil.Path)) {
              goto EXIT_24;
            }
            return TRUE;
          }
        }
      } EXIT_24:;
    }
  }
  if (yyP21->U_1.V_1.Kind == Tree_TestNonlin) {
    if (yyP20->U_1.V_1.Kind == Tree_TestNonlin) {
      for (;;) {
        {
          register Tree_yTestNonlin *W_66 = &yyP21->U_1.V_101.TestNonlin;

          {
            register Tree_yTestNonlin *W_67 = &yyP20->U_1.V_101.TestNonlin;

            if (!IsSamePath(yyP21->U_1.V_101.TestNonlin.Path, yyP20->U_1.V_101.TestNonlin.Path)) {
              goto EXIT_25;
            }
            if (!IsSamePath(yyP21->U_1.V_101.TestNonlin.Path2, yyP20->U_1.V_101.TestNonlin.Path2)) {
              goto EXIT_25;
            }
            return TRUE;
          }
        }
      } EXIT_25:;
    }
  }
  return FALSE;
}

static void BuildTree
# ifdef __STDC__
(Tree_tTree yyP23, Tree_tTree yyP22, Tree_tTree *yyP24)
# else
(yyP23, yyP22, yyP24)
Tree_tTree yyP23;
Tree_tTree yyP22;
Tree_tTree *yyP24;
# endif
{
  struct S_24 yyTempo;

  if (yyP23->U_1.V_1.Kind == Tree_Rule) {
    {
      register struct S_25 *W_68 = &yyTempo.U_1.V_1.yyR1;

      {
        register Tree_yRule *W_69 = &yyP23->U_1.V_42.Rule;

        gRule = yyP23;
        BuildTree2(W_69->Tests, yyP22, &W_68->yyV1);
        UpdateChange(W_68->yyV1, gRule);
        BuildTree(W_69->Next, W_68->yyV1, &W_68->yyV2);
        *yyP24 = W_68->yyV2;
        return;
      }
    }
  }
  if (yyP23->U_1.V_1.Kind == Tree_NoRule) {
    *yyP24 = yyP22;
    return;
  }
}

static void BuildTree2
# ifdef __STDC__
(Tree_tTree t, Tree_tTree d, Tree_tTree *yyP25)
# else
(t, d, yyP25)
Tree_tTree t;
Tree_tTree d;
Tree_tTree *yyP25;
# endif
{
  struct S_26 yyTempo;

  if (Tree_IsType(t, Tree_OneTest)) {
    if (d->U_1.V_1.Kind == Tree_NoDecision) {
      {
        register struct S_32 *W_70 = &yyTempo.U_1.V_1.yyR1;

        {
          register Tree_yOneTest *W_71 = &t->U_1.V_97.OneTest;

          {
            register Tree_yNoDecision *W_72 = &d->U_1.V_104.NoDecision;

            BuildTree2(t->U_1.V_97.OneTest.Next, d, &W_70->yyV1);
            UpdateChange(W_70->yyV1, gRule);
            *yyP25 = (Tree_tTree)Tree_yyPoolFreePtr;
            if ((ADDRESS)(*yyP25) >= Tree_yyPoolMaxPtr) {
              *yyP25 = Tree_yyAlloc();
            }
            INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decision]);
            (*yyP25)->U_1.V_2.yyHead.yyMark = 0;
            (*yyP25)->U_1.V_1.Kind = Tree_Decision;
            {
              register Tree_yDecision *W_73 = &(*yyP25)->U_1.V_105.Decision;

              W_73->Then = W_70->yyV1;
              W_73->Else = d;
              W_73->OneTest = t;
              W_73->Cases = 0;
              W_73->IsUnchanged = TRUE;
            }
            return;
          }
        }
      }
    }
    if (d->U_1.V_1.Kind == Tree_Decision) {
      {
        register struct S_31 *W_74 = &yyTempo.U_1.V_2.yyR2;

        if (d->U_1.V_105.Decision.IsUnchanged == TRUE) {
          for (;;) {
            {
              register Tree_yOneTest *W_75 = &t->U_1.V_97.OneTest;

              {
                register Tree_yDecision *W_76 = &d->U_1.V_105.Decision;

                if (!IsSameTest(t, d->U_1.V_105.Decision.OneTest)) {
                  goto EXIT_26;
                }
                if (!!HasInterference(t, d->U_1.V_105.Decision.Else)) {
                  goto EXIT_26;
                }
                BuildTree2(t->U_1.V_97.OneTest.Next, d->U_1.V_105.Decision.Then, &W_74->yyV1);
                d->U_1.V_105.Decision.Then = W_74->yyV1;
                UpdateChange(W_74->yyV1, gRule);
                *yyP25 = d;
                return;
              }
            }
          } EXIT_26:;
        }
      }
      {
        register struct S_30 *W_77 = &yyTempo.U_1.V_3.yyR3;

        {
          register Tree_yOneTest *W_78 = &t->U_1.V_97.OneTest;

          {
            register Tree_yDecision *W_79 = &d->U_1.V_105.Decision;

            BuildTree2(t, d->U_1.V_105.Decision.Else, &W_77->yyV1);
            d->U_1.V_105.Decision.Else = W_77->yyV1;
            UpdateChange(W_77->yyV1, gRule);
            *yyP25 = d;
            return;
          }
        }
      }
    }
    if (d->U_1.V_1.Kind == Tree_Decided) {
      {
        register struct S_29 *W_80 = &yyTempo.U_1.V_4.yyR4;

        {
          register Tree_yOneTest *W_81 = &t->U_1.V_97.OneTest;

          {
            register Tree_yDecided *W_82 = &d->U_1.V_106.Decided;

            BuildTree2(t, d->U_1.V_106.Decided.Else, &W_80->yyV1);
            d->U_1.V_106.Decided.Else = W_80->yyV1;
            UpdateChange(W_80->yyV1, gRule);
            *yyP25 = d;
            return;
          }
        }
      }
    }
  }
  if (t->U_1.V_1.Kind == Tree_NoTest) {
    if (d->U_1.V_1.Kind == Tree_NoDecision) {
      *yyP25 = (Tree_tTree)Tree_yyPoolFreePtr;
      if ((ADDRESS)(*yyP25) >= Tree_yyPoolMaxPtr) {
        *yyP25 = Tree_yyAlloc();
      }
      INC1(Tree_yyPoolFreePtr, Tree_yyNodeSize.A[Tree_Decided]);
      (*yyP25)->U_1.V_2.yyHead.yyMark = 0;
      (*yyP25)->U_1.V_1.Kind = Tree_Decided;
      {
        register Tree_yDecided *W_83 = &(*yyP25)->U_1.V_106.Decided;

        W_83->Else = d;
        W_83->Rule = gRule;
      }
      return;
    }
    if (d->U_1.V_1.Kind == Tree_Decision) {
      {
        register struct S_28 *W_84 = &yyTempo.U_1.V_5.yyR6;

        {
          register Tree_yNoTest *W_85 = &t->U_1.V_96.NoTest;

          {
            register Tree_yDecision *W_86 = &d->U_1.V_105.Decision;

            BuildTree2(t, d->U_1.V_105.Decision.Else, &W_84->yyV1);
            d->U_1.V_105.Decision.Else = W_84->yyV1;
            *yyP25 = d;
            return;
          }
        }
      }
    }
    if (d->U_1.V_1.Kind == Tree_Decided) {
      {
        register struct S_27 *W_87 = &yyTempo.U_1.V_6.yyR7;

        {
          register Tree_yNoTest *W_88 = &t->U_1.V_96.NoTest;

          {
            register Tree_yDecided *W_89 = &d->U_1.V_106.Decided;

            BuildTree2(t, d->U_1.V_106.Decided.Else, &W_87->yyV1);
            d->U_1.V_106.Decided.Else = W_87->yyV1;
            *yyP25 = d;
            return;
          }
        }
      }
    }
  }
}

static BOOLEAN HasInterference
# ifdef __STDC__
(Tree_tTree yyP27, Tree_tTree yyP26)
# else
(yyP27, yyP26)
Tree_tTree yyP27;
Tree_tTree yyP26;
# endif
{
  struct S_33 yyTempo;

  if (yyP26->U_1.V_1.Kind == Tree_Decided) {
    return TRUE;
  }
  if (yyP27->U_1.V_1.Kind == Tree_TestKind) {
    if (yyP26->U_1.V_1.Kind == Tree_Decision) {
      if (yyP26->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestKind) {
        for (;;) {
          {
            register Tree_yTestKind *W_90 = &yyP27->U_1.V_98.TestKind;

            {
              register Tree_yDecision *W_91 = &yyP26->U_1.V_105.Decision;

              if (!IsSamePath(yyP27->U_1.V_98.TestKind.Path, yyP26->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path)) {
                goto EXIT_27;
              }
              if (!!IsDisjoint(yyP27->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, yyP26->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types)) {
                goto EXIT_27;
              }
              return TRUE;
            }
          }
        } EXIT_27:;
      }
      if (yyP26->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestIsType) {
        for (;;) {
          {
            register Tree_yTestKind *W_92 = &yyP27->U_1.V_98.TestKind;

            {
              register Tree_yDecision *W_93 = &yyP26->U_1.V_105.Decision;

              if (!IsSamePath(yyP27->U_1.V_98.TestKind.Path, yyP26->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path)) {
                goto EXIT_28;
              }
              if (!!IsDisjoint(yyP27->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, yyP26->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types)) {
                goto EXIT_28;
              }
              return TRUE;
            }
          }
        } EXIT_28:;
      }
    }
  }
  if (yyP27->U_1.V_1.Kind == Tree_TestIsType) {
    if (yyP26->U_1.V_1.Kind == Tree_Decision) {
      if (yyP26->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestKind) {
        for (;;) {
          {
            register Tree_yTestIsType *W_94 = &yyP27->U_1.V_99.TestIsType;

            {
              register Tree_yDecision *W_95 = &yyP26->U_1.V_105.Decision;

              if (!IsSamePath(yyP27->U_1.V_99.TestIsType.Path, yyP26->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path)) {
                goto EXIT_29;
              }
              if (!!IsDisjoint(yyP27->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, yyP26->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types)) {
                goto EXIT_29;
              }
              return TRUE;
            }
          }
        } EXIT_29:;
      }
      if (yyP26->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestIsType) {
        for (;;) {
          {
            register Tree_yTestIsType *W_96 = &yyP27->U_1.V_99.TestIsType;

            {
              register Tree_yDecision *W_97 = &yyP26->U_1.V_105.Decision;

              if (!IsSamePath(yyP27->U_1.V_99.TestIsType.Path, yyP26->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path)) {
                goto EXIT_30;
              }
              if (!!IsDisjoint(yyP27->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, yyP26->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types)) {
                goto EXIT_30;
              }
              return TRUE;
            }
          }
        } EXIT_30:;
      }
    }
  }
  if (yyP26->U_1.V_1.Kind == Tree_Decision) {
    for (;;) {
      {
        register Tree_yDecision *W_98 = &yyP26->U_1.V_105.Decision;

        if (!HasInterference(yyP27, yyP26->U_1.V_105.Decision.Else)) {
          goto EXIT_31;
        }
        return TRUE;
      }
    } EXIT_31:;
  }
  return FALSE;
}

static void UpdateChange
# ifdef __STDC__
(Tree_tTree yyP29, Tree_tTree yyP28)
# else
(yyP29, yyP28)
Tree_tTree yyP29;
Tree_tTree yyP28;
# endif
{
  struct S_34 yyTempo;

  if (yyP29->U_1.V_1.Kind == Tree_Decision) {
    if (yyP29->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestKind) {
      if (yyP28->U_1.V_42.Rule.HasExit == TRUE) {
        if (yyP28->U_1.V_42.Rule.HasAssign == TRUE) {
          for (;;) {
            {
              register Tree_yDecision *W_99 = &yyP29->U_1.V_105.Decision;

              {
                register Tree_yRule *W_100 = &yyP28->U_1.V_42.Rule;

                if (!IsChanged(yyP29->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, yyP28->U_1.V_42.Rule.Statements)) {
                  goto EXIT_32;
                }
                yyP29->U_1.V_105.Decision.IsUnchanged = FALSE;
                return;
              }
            }
          } EXIT_32:;
        }
      }
    }
    if (yyP29->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestIsType) {
      if (yyP28->U_1.V_42.Rule.HasExit == TRUE) {
        if (yyP28->U_1.V_42.Rule.HasAssign == TRUE) {
          for (;;) {
            {
              register Tree_yDecision *W_101 = &yyP29->U_1.V_105.Decision;

              {
                register Tree_yRule *W_102 = &yyP28->U_1.V_42.Rule;

                if (!IsChanged(yyP29->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, yyP28->U_1.V_42.Rule.Statements)) {
                  goto EXIT_33;
                }
                yyP29->U_1.V_105.Decision.IsUnchanged = FALSE;
                return;
              }
            }
          } EXIT_33:;
        }
      }
    }
  }
}

static BOOLEAN IsChanged
# ifdef __STDC__
(Tree_tTree yyP31, Tree_tTree yyP30)
# else
(yyP31, yyP30)
Tree_tTree yyP31;
Tree_tTree yyP30;
# endif
{
  struct S_35 yyTempo;

  if (yyP30->U_1.V_1.Kind == Tree_Assignment) {
    for (;;) {
      {
        register Tree_yAssignment *W_103 = &yyP30->U_1.V_78.Assignment;

        if (!(yyP30->U_1.V_78.Assignment.Object != NIL)) {
          goto EXIT_34;
        }
        if (!IsSamePath(yyP31, yyP30->U_1.V_78.Assignment.Object->U_1.V_86.Formal.Path)) {
          goto EXIT_34;
        }
        return TRUE;
      }
    } EXIT_34:;
  }
  if (Tree_IsType(yyP30, Tree_Statement)) {
    for (;;) {
      {
        register Tree_yStatement *W_104 = &yyP30->U_1.V_75.Statement;

        if (!IsChanged(yyP31, yyP30->U_1.V_75.Statement.Next)) {
          goto EXIT_35;
        }
        return TRUE;
      }
    } EXIT_35:;
  }
  return FALSE;
}

static void FindCases
# ifdef __STDC__
(Tree_tTree yyP32, Tree_tTree *yyP35, SHORTCARD *yyP34, Sets_tSet *yyP33)
# else
(yyP32, yyP35, yyP34, yyP33)
Tree_tTree yyP32;
Tree_tTree *yyP35;
SHORTCARD *yyP34;
Sets_tSet *yyP33;
# endif
{
  struct S_36 yyTempo;

  if (yyP32->U_1.V_1.Kind == Tree_Decision) {
    if (yyP32->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestKind) {
      {
        register struct S_40 *W_105 = &yyTempo.U_1.V_1.yyR1;

        {
          register Tree_yDecision *W_106 = &yyP32->U_1.V_105.Decision;

          FindCases(yyP32->U_1.V_105.Decision.Then, &W_105->yyV1, &W_105->yyV2, &W_105->yyV3);
          MarkCases(yyP32->U_1.V_105.Decision.Then, W_105->yyV2, W_105->yyV3);
          FindCases(yyP32->U_1.V_105.Decision.Else, &W_105->yyV4, &W_105->yyV5, &W_105->yyV6);
          if (W_105->yyV5 == 0) {
            W_105->k = 1;
            Sets_MakeSet(&W_105->s, (LONGCARD)yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            Sets_Assign(&W_105->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types);
          } else if (IsSamePath(yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, W_105->yyV4) && IsDisjoint(W_105->yyV6, yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types)) {
            W_105->k = W_105->yyV5 + 1;
            W_105->s = W_105->yyV6;
            Sets_Union(&W_105->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types);
          } else {
            MarkCases(yyP32->U_1.V_105.Decision.Else, W_105->yyV5, W_105->yyV6);
            W_105->k = 1;
            Sets_MakeSet(&W_105->s, (LONGCARD)yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            Sets_Assign(&W_105->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types);
          }
          *yyP35 = yyP32->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path;
          *yyP34 = W_105->k;
          *yyP33 = W_105->s;
          return;
        }
      }
    }
    if (yyP32->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestIsType) {
      {
        register struct S_39 *W_107 = &yyTempo.U_1.V_2.yyR2;

        {
          register Tree_yDecision *W_108 = &yyP32->U_1.V_105.Decision;

          FindCases(yyP32->U_1.V_105.Decision.Then, &W_107->yyV1, &W_107->yyV2, &W_107->yyV3);
          MarkCases(yyP32->U_1.V_105.Decision.Then, W_107->yyV2, W_107->yyV3);
          FindCases(yyP32->U_1.V_105.Decision.Else, &W_107->yyV4, &W_107->yyV5, &W_107->yyV6);
          if (W_107->yyV5 == 0) {
            W_107->k = 1;
            Sets_MakeSet(&W_107->s, (LONGCARD)yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            Sets_Assign(&W_107->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types);
          } else if (IsSamePath(yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, W_107->yyV4) && IsDisjoint(W_107->yyV6, yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types)) {
            W_107->k = W_107->yyV5 + 1;
            W_107->s = W_107->yyV6;
            Sets_Union(&W_107->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types);
          } else {
            MarkCases(yyP32->U_1.V_105.Decision.Else, W_107->yyV5, W_107->yyV6);
            W_107->k = 1;
            Sets_MakeSet(&W_107->s, (LONGCARD)yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            Sets_Assign(&W_107->s, yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types);
          }
          *yyP35 = yyP32->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path;
          *yyP34 = W_107->k;
          *yyP33 = W_107->s;
          return;
        }
      }
    }
    {
      register struct S_38 *W_109 = &yyTempo.U_1.V_3.yyR3;

      {
        register Tree_yDecision *W_110 = &yyP32->U_1.V_105.Decision;

        FindCases(yyP32->U_1.V_105.Decision.Then, &W_109->yyV1, &W_109->yyV2, &W_109->yyV3);
        MarkCases(yyP32->U_1.V_105.Decision.Then, W_109->yyV2, W_109->yyV3);
        FindCases(yyP32->U_1.V_105.Decision.Else, &W_109->yyV4, &W_109->yyV5, &W_109->yyV6);
        MarkCases(yyP32->U_1.V_105.Decision.Else, W_109->yyV5, W_109->yyV6);
        *yyP35 = NIL;
        *yyP34 = 0;
        return;
      }
    }
  }
  if (yyP32->U_1.V_1.Kind == Tree_Decided) {
    {
      register struct S_37 *W_111 = &yyTempo.U_1.V_4.yyR4;

      {
        register Tree_yDecided *W_112 = &yyP32->U_1.V_106.Decided;

        FindCases(yyP32->U_1.V_106.Decided.Else, &W_111->yyV1, &W_111->yyV2, &W_111->yyV3);
        MarkCases(yyP32->U_1.V_106.Decided.Else, W_111->yyV2, W_111->yyV3);
        *yyP35 = NIL;
        *yyP34 = 0;
        return;
      }
    }
  }
  if (yyP32->U_1.V_1.Kind == Tree_NoDecision) {
    *yyP35 = NIL;
    *yyP34 = 0;
    return;
  }
}

static void MarkCases
# ifdef __STDC__
(Tree_tTree yyP38, SHORTCARD yyP37, Sets_tSet yyP36)
# else
(yyP38, yyP37, yyP36)
Tree_tTree yyP38;
SHORTCARD yyP37;
Sets_tSet yyP36;
# endif
{
  struct S_41 yyTempo;

  if (yyP38->U_1.V_1.Kind == Tree_Decision) {
    for (;;) {
      {
        register Tree_yDecision *W_113 = &yyP38->U_1.V_105.Decision;

        if (!(yyP37 >= 7)) {
          goto EXIT_36;
        }
        yyP38->U_1.V_105.Decision.Cases = yyP37;
        Sets_ReleaseSet(&yyP36);
        return;
      }
    } EXIT_36:;
  }
}

static void ElimDeadTests
# ifdef __STDC__
(Tree_tTree yyP42, Tree_tTree yyP41, BOOLEAN yyP40, Sets_tSet yyP39)
# else
(yyP42, yyP41, yyP40, yyP39)
Tree_tTree yyP42;
Tree_tTree yyP41;
BOOLEAN yyP40;
Sets_tSet yyP39;
# endif
{
  struct S_42 yyTempo;

  if (yyP42->U_1.V_1.Kind == Tree_Decision) {
    if (yyP42->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestKind) {
      {
        register struct S_48 *W_114 = &yyTempo.U_1.V_1.yyR1;

        if (yyP40 == FALSE) {
          {
            register Tree_yDecision *W_115 = &yyP42->U_1.V_105.Decision;

            Sets_MakeSet(&W_114->s, (LONGCARD)yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            if (IsDeadEnd(yyP42->U_1.V_105.Decision.Then)) {
              Sets_Assign(&W_114->s, yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types);
            }
            ElimDeadTests(yyP42->U_1.V_105.Decision.Else, yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, TRUE, W_114->s);
            ElimDeadTests(yyP42->U_1.V_105.Decision.Then, W_114->yyV1, FALSE, W_114->yyV2);
            return;
          }
        }
      }
      {
        register struct S_46 *W_116 = &yyTempo.U_1.V_3.yyR3;

        {
          register Tree_yDecision *W_117 = &yyP42->U_1.V_105.Decision;

          W_116->s2 = yyP39;
          if (IsSamePath(yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, yyP41)) {
            if (!IsDisjoint(yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, yyP39)) {
              W_116->types = yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types;
              yyP42->U_1.V_105.Decision.OneTest = Tree_mTestIsType(yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Next, yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, Tree_mNodeTypes(yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.TreeName, W_116->types), yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Name);
              Sets_MakeSet(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, (LONGCARD)yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
              Sets_Assign(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, W_116->types);
              Sets_Difference(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types, yyP39);
            }
          } else {
            Sets_AssignEmpty(&W_116->s2);
          }
          if (IsDeadEnd(yyP42->U_1.V_105.Decision.Then)) {
            Sets_Union(&W_116->s2, yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.TypeDesc->U_1.V_89.NodeTypes.Types);
          }
          ElimDeadTests(yyP42->U_1.V_105.Decision.Else, yyP42->U_1.V_105.Decision.OneTest->U_1.V_98.TestKind.Path, TRUE, W_116->s2);
          ElimDeadTests(yyP42->U_1.V_105.Decision.Then, W_116->yyV1, FALSE, W_116->yyV2);
          return;
        }
      }
    }
    if (yyP42->U_1.V_105.Decision.OneTest->U_1.V_1.Kind == Tree_TestIsType) {
      {
        register struct S_47 *W_118 = &yyTempo.U_1.V_2.yyR2;

        if (yyP40 == FALSE) {
          {
            register Tree_yDecision *W_119 = &yyP42->U_1.V_105.Decision;

            Sets_MakeSet(&W_118->s, (LONGCARD)yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
            if (IsDeadEnd(yyP42->U_1.V_105.Decision.Then)) {
              Sets_Assign(&W_118->s, yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types);
            }
            ElimDeadTests(yyP42->U_1.V_105.Decision.Else, yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, TRUE, W_118->s);
            ElimDeadTests(yyP42->U_1.V_105.Decision.Then, W_118->yyV1, FALSE, W_118->yyV2);
            return;
          }
        }
      }
      {
        register struct S_45 *W_120 = &yyTempo.U_1.V_4.yyR4;

        {
          register Tree_yDecision *W_121 = &yyP42->U_1.V_105.Decision;

          W_120->s2 = yyP39;
          if (IsSamePath(yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, yyP41)) {
            if (!IsDisjoint(yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, yyP39)) {
              W_120->types = yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types;
              yyP42->U_1.V_105.Decision.OneTest = Tree_mTestIsType(yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Next, yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, Tree_mNodeTypes(yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.TreeName, W_120->types), yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Name);
              Sets_MakeSet(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, (LONGCARD)yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
              Sets_Assign(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, W_120->types);
              Sets_Difference(&yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types, yyP39);
            }
          } else {
            Sets_AssignEmpty(&W_120->s2);
          }
          if (IsDeadEnd(yyP42->U_1.V_105.Decision.Then)) {
            Sets_Union(&W_120->s2, yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.TypeDesc->U_1.V_89.NodeTypes.Types);
          }
          ElimDeadTests(yyP42->U_1.V_105.Decision.Else, yyP42->U_1.V_105.Decision.OneTest->U_1.V_99.TestIsType.Path, TRUE, W_120->s2);
          ElimDeadTests(yyP42->U_1.V_105.Decision.Then, W_120->yyV1, FALSE, W_120->yyV2);
          return;
        }
      }
    }
    {
      register struct S_44 *W_122 = &yyTempo.U_1.V_5.yyR5;

      {
        register Tree_yDecision *W_123 = &yyP42->U_1.V_105.Decision;

        if (yyP40) {
          Sets_ReleaseSet(&yyP39);
        }
        ElimDeadTests(yyP42->U_1.V_105.Decision.Else, W_122->yyV1, FALSE, W_122->yyV2);
        ElimDeadTests(yyP42->U_1.V_105.Decision.Then, W_122->yyV3, FALSE, W_122->yyV4);
        return;
      }
    }
  }
  if (yyP42->U_1.V_1.Kind == Tree_Decided) {
    {
      register struct S_43 *W_124 = &yyTempo.U_1.V_6.yyR6;

      {
        register Tree_yDecided *W_125 = &yyP42->U_1.V_106.Decided;

        if (yyP40) {
          Sets_ReleaseSet(&yyP39);
        }
        if (!yyP42->U_1.V_106.Decided.Rule->U_1.V_42.Rule.HasExit) {
          ReportWarning(yyP42->U_1.V_106.Decided.Else);
        }
        ElimDeadTests(yyP42->U_1.V_106.Decided.Else, W_124->yyV1, FALSE, W_124->yyV2);
        return;
      }
    }
  }
  if (yyP42->U_1.V_1.Kind == Tree_NoDecision) {
    if (yyP40 == TRUE) {
      {
        register Tree_yNoDecision *W_126 = &yyP42->U_1.V_104.NoDecision;

        Sets_ReleaseSet(&yyP39);
        return;
      }
    }
  }
}

static BOOLEAN IsDeadEnd
# ifdef __STDC__
(Tree_tTree yyP43)
# else
(yyP43)
Tree_tTree yyP43;
# endif
{
  struct S_49 yyTempo;

  if (yyP43->U_1.V_1.Kind == Tree_Decided) {
    for (;;) {
      {
        register Tree_yDecided *W_127 = &yyP43->U_1.V_106.Decided;

        if (!(!yyP43->U_1.V_106.Decided.Rule->U_1.V_42.Rule.HasExit || IsDeadEnd(yyP43->U_1.V_106.Decided.Else))) {
          goto EXIT_37;
        }
        return TRUE;
      }
    } EXIT_37:;
  }
  return FALSE;
}

static void ReportWarning
# ifdef __STDC__
(Tree_tTree yyP44)
# else
(yyP44)
Tree_tTree yyP44;
# endif
{
  struct S_50 yyTempo;

  if (yyP44->U_1.V_1.Kind == Tree_Decided) {
    {
      register Tree_yDecided *W_128 = &yyP44->U_1.V_106.Decided;

      Scanner_Warning((STRING)"unreachable code", 16L, yyP44->U_1.V_106.Decided.Rule->U_1.V_42.Rule.Line);
      ReportWarning(yyP44->U_1.V_106.Decided.Else);
      return;
    }
  }
  if (yyP44->U_1.V_1.Kind == Tree_Decision) {
    {
      register Tree_yDecision *W_129 = &yyP44->U_1.V_105.Decision;

      ReportWarning(yyP44->U_1.V_105.Decision.Then);
      ReportWarning(yyP44->U_1.V_105.Decision.Else);
      return;
    }
  }
}

void Optimize_BeginOptimize
# ifdef __STDC__
()
# else
()
# endif
{
}

void Optimize_CloseOptimize
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

void BEGIN_Optimize()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_System();
    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_IO();
    BEGIN_Idents();
    BEGIN_Mod();
    BEGIN_Tree();
    BEGIN_Scanner();
    BEGIN_Positions();
    BEGIN_Sets();
    BEGIN_Sets();

    Optimize_yyf = IO_StdOutput;
    Optimize_Exit = yyExit;
    Optimize_BeginOptimize();
  }
}
