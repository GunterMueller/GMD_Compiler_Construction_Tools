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

#ifndef DEFINITION_General
#include "General.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Strings
#include "Strings.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Texts
#include "Texts.h"
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

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

SHORTCARD Semantics_TypeCount;
Sets_tSet Semantics_TypeNames, Semantics_UserTypes;
IO_tFile Semantics_yyf;
PROC Semantics_Exit;

static Sets_tSet ExternNames, LocExternNames, ActTypes, ActNames, UserNames, LabelNames, ParamNames, RoutineNames;
static Tree_tTree dFormals, Parameters, Decls, Args, InFormals, OutFormals, ReturnFormal, Node, Var, TreeName, ActTree, ActClass;
static INTEGER RuleCount, VarCount;
static Idents_tIdent ProcName, ParamName;
static BOOLEAN HasLocals, IsFunction, IsOutput, Mode, Success;
static Strings_tString String, String1;
static CARDINAL i;
static Tree_tTree nNoFormal;
static Tree_tTree IdentifyClass ARGS((Tree_tTree t, Idents_tIdent Ident));
static Tree_tTree IdentifyTree ARGS((Idents_tIdent i));
static Tree_tTree IdentifyProc ARGS((Idents_tIdent i));
static Tree_tTree IdentifyClass2 ARGS((Idents_tIdent i, Tree_tTree *TreeName));
static void MakeTypes ARGS((INTEGER Index, Tree_tTree Classes, Sets_tSet *Types));
static void CheckSubtype ARGS((Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos));
static void CheckType ARGS((Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos));
static Tree_tTree TransformPattern ARGS((Tree_tTree t));
static Tree_tTree TransformExpr ARGS((Tree_tTree t));
static Tree_tTree TransformStmt ARGS((Tree_tTree t));
static Tree_tTree TransformName ARGS((Tree_tTree t, Tree_tTree Formals));
struct S_3 {
    Tree_tTree A[50000 + 1];
};
static INTEGER Lookup ARGS((Idents_tIdent Ident, Tree_tTree Formals));
static void CheckExprList ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckInParams ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckCallExprs ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckExprVar ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckExpr ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckExpr2 ARGS((Tree_tTree t));
static void CheckPatternList ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckSubPatterns ARGS((Tree_tTree t, Tree_tTree Formals, Tree_tTree Path));
static void CheckCallPatterns ARGS((Tree_tTree t, Tree_tTree Formals));
static void CheckPattern ARGS((Tree_tTree t, Tree_tTree Formals, Tree_tTree Path));
static Idents_tIdent MakeVar ARGS(());
static Tree_tTree MakeTempos ARGS((Tree_tTree Formals));
static void yyAbort ARGS((CHAR yyFunction[], LONGCARD ));
static BOOLEAN yyIsEqual ARGS((BYTE yya[], LONGCARD , BYTE yyb[], LONGCARD ));
struct S_4 {
    union {
        char dummy;
    } U_1;
};
static void CollectExtern ARGS((Tree_tTree t, Sets_tSet *Names));
struct S_5 {
    union {
        char dummy;
    } U_1;
};
static void ProcFormals ARGS((Tree_tTree t));
struct S_6 {
    union {
        char dummy;
    } U_1;
};
static void ClassFormals ARGS((Tree_tTree t));
struct S_7 {
    union {
        char dummy;
    } U_1;
};
static void CountClasses ARGS((Tree_tTree t));
struct S_8 {
    union {
        char dummy;
    } U_1;
};
static void ClassTypes ARGS((Tree_tTree t));
struct S_9 {
    union {
        char dummy;
    } U_1;
};
static void Check ARGS((Tree_tTree t));
struct S_10 {
    union {
        char dummy;
    } U_1;
};
static void CheckTargetCode ARGS((Tree_tTree t));
struct S_11 {
    union {
        char dummy;
    } U_1;
};
struct S_12 {
    union {
        struct {
            struct S_13 {
                Strings_tString String1;
                Strings_tString String2;
                Idents_tIdent i;
            } yyR2;
        } V_1;
    } U_1;
};
static BOOLEAN HasReject ARGS((Tree_tTree yyP1));
struct S_14 {
    union {
        char dummy;
    } U_1;
};
static void yyExit ARGS(());


static Tree_tTree IdentifyClass
# ifdef __STDC__
(Tree_tTree t, Idents_tIdent Ident)
# else
(t, Ident)
Tree_tTree t;
Idents_tIdent Ident;
# endif
{
  Tree_tTree class;

  while (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_1 = &t->U_1.V_5.Class;

      if (W_1->Name == Ident) {
        return t;
      }
      class = IdentifyClass(W_1->Extensions, Ident);
      if (class != Tree_NoTree) {
        return class;
      }
      t = W_1->Next;
    }
  }
  return Tree_NoTree;
}

static Tree_tTree IdentifyTree
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Tree_tTree Node;

  Node = Tree_TreeRoot->U_1.V_26.Spec.TreeNames;
  while (Node->U_1.V_1.Kind == Tree_TreeName) {
    if (Node->U_1.V_29.TreeName.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_29.TreeName.Next;
  }
  return Tree_NoTree;
}

static Tree_tTree IdentifyProc
# ifdef __STDC__
(Idents_tIdent i)
# else
(i)
Idents_tIdent i;
# endif
{
  Tree_tTree Node;

  Node = Tree_TreeRoot->U_1.V_26.Spec.Routines;
  while (Node->U_1.V_1.Kind != Tree_NoRoutine) {
    if (Node->U_1.V_32.Routine.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_32.Routine.Next;
  }
  return Tree_NoTree;
}

Tree_tTree Semantics_IdentifyVar
# ifdef __STDC__
(Tree_tTree Node, Idents_tIdent i)
# else
(Node, i)
Tree_tTree Node;
Idents_tIdent i;
# endif
{
  while (Node->U_1.V_1.Kind != Tree_NoFormal) {
    if (Node->U_1.V_86.Formal.Name == i) {
      return Node;
    }
    Node = Node->U_1.V_86.Formal.Next;
  }
  return Tree_NoTree;
}

static Tree_tTree IdentifyClass2
# ifdef __STDC__
(Idents_tIdent i, Tree_tTree *TreeName)
# else
(i, TreeName)
Idents_tIdent i;
Tree_tTree *TreeName;
# endif
{
  Tree_tTree Class;

  *TreeName = Tree_TreeRoot->U_1.V_26.Spec.TreeNames;
  while ((*TreeName)->U_1.V_1.Kind == Tree_TreeName) {
    Class = IdentifyClass((*TreeName)->U_1.V_29.TreeName.Classes, i);
    if (Class != Tree_NoTree) {
      return Class;
    }
    *TreeName = (*TreeName)->U_1.V_29.TreeName.Next;
  }
  *TreeName = Tree_NoTree;
  return Tree_NoTree;
}

Tree_tTree Semantics_LookupClass
# ifdef __STDC__
(Tree_tTree Classes, CARDINAL i)
# else
(Classes, i)
Tree_tTree Classes;
CARDINAL i;
# endif
{
  Tree_tTree Class;

  if (Classes->U_1.V_1.Kind == Tree_NoClass) {
    return Tree_NoTree;
  }
  {
    register Tree_yClass *W_2 = &Classes->U_1.V_5.Class;

    if (W_2->Index == i) {
      return Classes;
    }
    Class = Semantics_LookupClass(W_2->Extensions, i);
    if (Class != Tree_NoTree) {
      return Class;
    }
    return Semantics_LookupClass(W_2->Next, i);
  }
}

static void MakeTypes
# ifdef __STDC__
(INTEGER Index, Tree_tTree Classes, Sets_tSet *Types)
# else
(Index, Classes, Types)
INTEGER Index;
Tree_tTree Classes;
Sets_tSet *Types;
# endif
{
  ActTypes = *Types;
  Tree_ForallClasses(Classes, (Tree_ProcOfT)ProcFormals);
  Sets_Include(&ActTypes, (LONGCARD)Index);
  *Types = ActTypes;
}

static void CheckSubtype
# ifdef __STDC__
(Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos)
# else
(t1, t2, Pos)
Tree_tTree t1, t2;
Positions_tPosition Pos;
# endif
{
  if (t1->U_1.V_1.Kind == Tree_NodeTypes) {
    if (t2->U_1.V_1.Kind == Tree_UserType) {
      Scanner_Warning((STRING)"tree-type required", 18L, Pos);
    } else if (t2->U_1.V_89.NodeTypes.TreeName != t1->U_1.V_89.NodeTypes.TreeName) {
      Scanner_Error((STRING)"incompatible tree types", 23L, Pos);
    } else if (!Sets_IsSubset(t2->U_1.V_89.NodeTypes.Types, t1->U_1.V_89.NodeTypes.Types)) {
      Scanner_Error((STRING)"subtype required", 16L, Pos);
    }
  } else if (t1->U_1.V_1.Kind == Tree_UserType) {
    if (t2->U_1.V_1.Kind == Tree_NodeTypes) {
      Scanner_Warning((STRING)"user-type required", 18L, Pos);
    } else if (t2->U_1.V_90.UserType.Type != t1->U_1.V_90.UserType.Type) {
      Scanner_Warning((STRING)"incompatible types", 18L, Pos);
    }
  }
}

static void CheckType
# ifdef __STDC__
(Tree_tTree t1, Tree_tTree t2, Positions_tPosition Pos)
# else
(t1, t2, Pos)
Tree_tTree t1, t2;
Positions_tPosition Pos;
# endif
{
  Sets_tSet t;

  if (t1->U_1.V_1.Kind == Tree_NodeTypes) {
    if (t2->U_1.V_1.Kind == Tree_UserType) {
      Scanner_Warning((STRING)"tree-type required", 18L, Pos);
    } else if (t2->U_1.V_89.NodeTypes.TreeName != t1->U_1.V_89.NodeTypes.TreeName) {
      Scanner_Error((STRING)"incompatible tree types", 23L, Pos);
    } else {
      Sets_MakeSet(&t, (LONGCARD)t1->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.ClassCount);
      Sets_Assign(&t, t1->U_1.V_89.NodeTypes.Types);
      Sets_Intersection(&t, t2->U_1.V_89.NodeTypes.Types);
      if (Sets_IsEmpty(t)) {
        Scanner_Warning((STRING)"incompatible node types", 23L, Pos);
      }
      Sets_ReleaseSet(&t);
    }
  } else if (t1->U_1.V_1.Kind == Tree_UserType) {
    if (t2->U_1.V_1.Kind == Tree_NodeTypes) {
      Scanner_Warning((STRING)"user-type required", 18L, Pos);
    } else if (t2->U_1.V_90.UserType.Type != t1->U_1.V_90.UserType.Type) {
      Scanner_Warning((STRING)"incompatible types", 18L, Pos);
    }
  }
}

static Tree_tTree TransformPattern
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree TreeName, s, object;

  switch (t->U_1.V_1.Kind) {
  case Tree_NoExpr:;
    return Tree_mNoPattern(t->U_1.V_57.NoExpr.Pos);
    break;
  case Tree_OneExpr:;
    {
      register Tree_yOneExpr *W_3 = &t->U_1.V_58.OneExpr;

      return Tree_mOnePattern(TransformPattern(W_3->Expr), TransformPattern(W_3->Next));
    }
    break;
  case Tree_NamedExpr:;
    {
      register Tree_yNamedExpr *W_4 = &t->U_1.V_59.NamedExpr;

      Scanner_Error((STRING)"pattern name illegal", 20L, W_4->Expr->U_1.V_60.Expr.Pos);
      return Tree_mOnePattern(TransformPattern(W_4->Expr), TransformPattern(W_4->Next));
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_5 = &t->U_1.V_61.Compose;

      if (W_5->Expr->U_1.V_1.Kind == Tree_VarUse) {
        W_5->Object = IdentifyClass2(W_5->Expr->U_1.V_62.VarUse.Name, &TreeName);
        if (W_5->Object == Tree_NoTree) {
          W_5->Object = IdentifyProc(W_5->Expr->U_1.V_62.VarUse.Name);
        }
      } else if (W_5->Expr->U_1.V_1.Kind == Tree_Binary && W_5->Expr->U_1.V_66.Binary.Lop->U_1.V_1.Kind == Tree_VarUse && W_5->Expr->U_1.V_66.Binary.Rop->U_1.V_1.Kind == Tree_VarUse) {
        W_5->Object = IdentifyTree(W_5->Expr->U_1.V_66.Binary.Lop->U_1.V_62.VarUse.Name);
        if (W_5->Object != Tree_NoTree) {
          W_5->Object = IdentifyClass(W_5->Object->U_1.V_29.TreeName.Classes, W_5->Expr->U_1.V_66.Binary.Rop->U_1.V_62.VarUse.Name);
        }
      } else {
        W_5->Object = Tree_NoTree;
      }
      W_5->Expr = TransformExpr(W_5->Expr);
      if (W_5->Object != Tree_NoTree) {
        if (W_5->Object->U_1.V_1.Kind == Tree_Class) {
          W_5->Exprs = TransformName(W_5->Exprs, W_5->Object->U_1.V_5.Class.Formals);
          s = Tree_mDecompose(W_5->Pos, W_5->Selector, W_5->Expr, TransformPattern(W_5->Exprs), W_5->Widen);
          s->U_1.V_50.Decompose.Object = W_5->Object;
          return s;
        } else {
          s = Tree_mCall(W_5->Pos, W_5->Expr, TransformExpr(W_5->Exprs), Tree_mNoPattern(W_5->Pos));
          s->U_1.V_65.Call.Object = W_5->Object;
          return Tree_mValue(W_5->Pos, s);
        }
      } else {
        s = Tree_mCall(W_5->Pos, W_5->Expr, TransformExpr(W_5->Exprs), Tree_mNoExpr(W_5->Pos));
        s->U_1.V_65.Call.Object = W_5->Object;
        return Tree_mValue(W_5->Pos, s);
      }
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_6 = &t->U_1.V_62.VarUse;

      W_6->Object = IdentifyClass2(W_6->Name, &TreeName);
      if (W_6->Object != Tree_NoTree && Sets_IsElement(ORD('p'), &Tree_Options)) {
        s = Tree_mDecompose(W_6->Pos, Idents_NoIdent, t, Tree_mOnePattern(Tree_mDontCare(W_6->Pos), Tree_mNoPattern(W_6->Pos)), FALSE);
        s->U_1.V_50.Decompose.Object = W_6->Object;
        return s;
      } else {
        return Tree_mVarDef(W_6->Pos, W_6->Name);
      }
    }
    break;
  case Tree_Nil:;
    return Tree_mNilTest(t->U_1.V_64.Nil.Pos, t->U_1.V_64.Nil.Selector);
    break;
  case Tree_DontCare1:;
  case Tree_DontCare:;
    return t;
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_7 = &t->U_1.V_66.Binary;

      if (Sets_IsElement(ORD('p'), &Tree_Options) && W_7->Operator == Idents_MakeIdent(&String1) && W_7->Lop->U_1.V_1.Kind == Tree_VarUse && W_7->Rop->U_1.V_1.Kind == Tree_VarUse) {
        object = IdentifyTree(W_7->Lop->U_1.V_62.VarUse.Name);
        if (object != Tree_NoTree) {
          object = IdentifyClass(object->U_1.V_29.TreeName.Classes, W_7->Rop->U_1.V_62.VarUse.Name);
          if (object != Tree_NoTree) {
            s = Tree_mDecompose(W_7->Pos, Idents_NoIdent, t, Tree_mOnePattern(Tree_mDontCare(W_7->Pos), Tree_mNoPattern(W_7->Pos)), FALSE);
            s->U_1.V_50.Decompose.Object = object;
            return s;
          }
        }
      }
      return Tree_mValue(W_7->Pos, TransformExpr(t));
    }
    break;
  case Tree_Call:;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
  case Tree_Index:;
  case Tree_Parents:;
  case Tree_TargetExpr:;
  case Tree_StringExpr:;
  case Tree_AttrDesc:;
    return Tree_mValue(t->U_1.V_60.Expr.Pos, TransformExpr(t));
    break;
  }
}

static Tree_tTree TransformExpr
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  Tree_tTree TreeName, s, object;

  switch (t->U_1.V_1.Kind) {
  case Tree_NoExpr:;
    break;
  case Tree_OneExpr:;
    {
      register Tree_yOneExpr *W_8 = &t->U_1.V_58.OneExpr;

      W_8->Expr = TransformExpr(W_8->Expr);
      W_8->Next = TransformExpr(W_8->Next);
    }
    break;
  case Tree_NamedExpr:;
    {
      register Tree_yNamedExpr *W_9 = &t->U_1.V_59.NamedExpr;

      Scanner_Error((STRING)"argument name illegal", 21L, t->U_1.V_59.NamedExpr.Expr->U_1.V_60.Expr.Pos);
      return Tree_mOneExpr(TransformExpr(W_9->Expr), TransformExpr(W_9->Next));
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_10 = &t->U_1.V_61.Compose;

      if (W_10->Expr->U_1.V_1.Kind == Tree_VarUse) {
        W_10->Object = IdentifyClass2(W_10->Expr->U_1.V_62.VarUse.Name, &TreeName);
        if (W_10->Object == Tree_NoTree) {
          W_10->Object = IdentifyProc(W_10->Expr->U_1.V_62.VarUse.Name);
        }
      } else if (W_10->Expr->U_1.V_1.Kind == Tree_Binary && W_10->Expr->U_1.V_66.Binary.Lop->U_1.V_1.Kind == Tree_VarUse && W_10->Expr->U_1.V_66.Binary.Rop->U_1.V_1.Kind == Tree_VarUse) {
        W_10->Object = IdentifyTree(W_10->Expr->U_1.V_66.Binary.Lop->U_1.V_62.VarUse.Name);
        if (W_10->Object != Tree_NoTree) {
          W_10->Object = IdentifyClass(W_10->Object->U_1.V_29.TreeName.Classes, W_10->Expr->U_1.V_66.Binary.Rop->U_1.V_62.VarUse.Name);
        }
      } else {
        W_10->Object = Tree_NoTree;
      }
      W_10->Expr = TransformExpr(W_10->Expr);
      if (W_10->Object != Tree_NoTree) {
        if (W_10->Object->U_1.V_1.Kind == Tree_Class) {
          W_10->Exprs = TransformName(W_10->Exprs, W_10->Object->U_1.V_5.Class.Formals);
          W_10->Exprs = TransformExpr(W_10->Exprs);
          return t;
        } else {
          s = Tree_mCall(W_10->Pos, W_10->Expr, TransformExpr(W_10->Exprs), Tree_mNoPattern(W_10->Pos));
          s->U_1.V_65.Call.Object = W_10->Object;
          return s;
        }
      } else {
        s = Tree_mCall(W_10->Pos, W_10->Expr, TransformExpr(W_10->Exprs), Tree_mNoExpr(W_10->Pos));
        s->U_1.V_65.Call.Object = W_10->Object;
        return s;
      }
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_11 = &t->U_1.V_62.VarUse;

      W_11->Object = IdentifyClass2(W_11->Name, &TreeName);
      if (W_11->Object != Tree_NoTree && Sets_IsElement(ORD('p'), &Tree_Options)) {
        s = Tree_mCompose(W_11->Pos, Idents_NoIdent, t, Tree_mOneExpr(Tree_mDontCare(W_11->Pos), Tree_mNoExpr(W_11->Pos)), FALSE);
        s->U_1.V_61.Compose.Object = W_11->Object;
        return s;
      } else {
        W_11->Object = Tree_NoTree;
        return t;
      }
    }
    break;
  case Tree_Nil:;
    break;
  case Tree_DontCare1:;
    break;
  case Tree_DontCare:;
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_12 = &t->U_1.V_65.Call;

      if (W_12->Expr->U_1.V_1.Kind == Tree_VarUse) {
        W_12->Object = IdentifyProc(W_12->Expr->U_1.V_62.VarUse.Name);
      } else {
        W_12->Object = Tree_NoTree;
      }
      W_12->Expr = TransformExpr(W_12->Expr);
      W_12->Exprs = TransformExpr(W_12->Exprs);
      if (W_12->Object != Tree_NoTree) {
        W_12->Patterns = TransformPattern(W_12->Patterns);
      } else {
        W_12->Patterns = TransformExpr(W_12->Patterns);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_13 = &t->U_1.V_66.Binary;

      if (Sets_IsElement(ORD('p'), &Tree_Options) && W_13->Lop->U_1.V_1.Kind == Tree_VarUse && W_13->Rop->U_1.V_1.Kind == Tree_VarUse) {
        object = IdentifyTree(W_13->Lop->U_1.V_62.VarUse.Name);
        if (object != Tree_NoTree) {
          object = IdentifyClass(object->U_1.V_29.TreeName.Classes, W_13->Rop->U_1.V_62.VarUse.Name);
          if (object != Tree_NoTree) {
            s = Tree_mCompose(W_13->Pos, Idents_NoIdent, t, Tree_mOneExpr(Tree_mDontCare(W_13->Pos), Tree_mNoExpr(W_13->Pos)), FALSE);
            s->U_1.V_61.Compose.Object = object;
            return s;
          }
        }
      }
      W_13->Lop = TransformExpr(W_13->Lop);
      W_13->Rop = TransformExpr(W_13->Rop);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    {
      register Tree_yPreOperator *W_14 = &t->U_1.V_67.PreOperator;

      W_14->Expr = TransformExpr(W_14->Expr);
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_15 = &t->U_1.V_69.Index;

      W_15->Expr = TransformExpr(W_15->Expr);
      W_15->Exprs = TransformExpr(W_15->Exprs);
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_16 = &t->U_1.V_70.Parents;

      W_16->Expr = TransformExpr(W_16->Expr);
    }
    break;
  case Tree_TargetExpr:;
    break;
  case Tree_StringExpr:;
    break;
  case Tree_AttrDesc:;
    break;
  }
  return t;
}

static Tree_tTree TransformStmt
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_NoStatement:;
    return t;
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_17 = &t->U_1.V_76.ProcCall;

      W_17->Call = TransformExpr(W_17->Call);
      if (W_17->Call->U_1.V_1.Kind == Tree_Call) {
        {
          register Tree_yCall *W_18 = &W_17->Call->U_1.V_65.Call;

          if (W_18->Object != Tree_NoTree && (W_18->Object->U_1.V_1.Kind == Tree_Predicate || W_18->Object->U_1.V_1.Kind == Tree_Function)) {
            t->U_1.V_1.Kind = Tree_Condition;
          }
        }
      } else if (W_17->Call->U_1.V_1.Kind == Tree_StringExpr) {
        t = Tree_mWriteStr(W_17->Pos, W_17->Next, W_17->Call->U_1.V_72.StringExpr.String);
      } else {
        t->U_1.V_1.Kind = Tree_Condition;
      }
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_19 = &t->U_1.V_78.Assignment;

      W_19->Adr = TransformExpr(W_19->Adr);
      W_19->Expr = TransformExpr(W_19->Expr);
    }
    break;
  case Tree_Reject:;
    break;
  case Tree_Fail:;
    break;
  case Tree_TargetStmt:;
    break;
  case Tree_Nl:;
    break;
  case Tree_WriteStr:;
    break;
  }
  t->U_1.V_75.Statement.Next = TransformStmt(t->U_1.V_75.Statement.Next);
  return t;
}

static INTEGER Lookup
# ifdef __STDC__
(Idents_tIdent Ident, Tree_tTree Formals)
# else
(Ident, Formals)
Idents_tIdent Ident;
Tree_tTree Formals;
# endif
{
  INTEGER i;

  i = 0;
  while (Formals->U_1.V_1.Kind == Tree_Formal) {
    INC(i);
    if (Formals->U_1.V_86.Formal.Name == Ident) {
      return i;
    }
    Formals = Formals->U_1.V_86.Formal.Next;
  }
  return 0;
}

static Tree_tTree TransformName
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Exprs;
  Tree_tTree *Last;
  INTEGER n, i, Minimum, Maximum;
  LONGINT PatternsSize;
  struct S_3 *PatternsPtr;

  Exprs = t;
  while (Exprs->U_1.V_1.Kind == Tree_OneExpr) {
    Exprs = Exprs->U_1.V_58.OneExpr.Next;
  }
  if (Exprs->U_1.V_1.Kind == Tree_NoExpr) {
    return t;
  }
  n = 0;
  Exprs = Formals;
  while (Exprs->U_1.V_1.Kind == Tree_Formal) {
    INC(n);
    Exprs = Exprs->U_1.V_86.Formal.Next;
  }
  PatternsSize = n + 1;
  DynArray_MakeArray((ADDRESS *)&PatternsPtr, &PatternsSize, (LONGINT)sizeof(Tree_tTree));
  {
    LONGINT B_1 = 1, B_2 = n;

    if (B_1 <= B_2)
      for (i = B_1;; i += 1) {
        PatternsPtr->A[i] = Tree_NoTree;
        if (i >= B_2) break;
      }
  }
  Last = (Tree_tTree *)ADR(t);
  Exprs = t;
  i = 0;
  while (Exprs->U_1.V_1.Kind == Tree_OneExpr) {
    INC(i);
    PatternsPtr->A[i] = Exprs->U_1.V_58.OneExpr.Expr;
    Last = (Tree_tTree *)ADR(Exprs->U_1.V_58.OneExpr.Next);
    Exprs = Exprs->U_1.V_58.OneExpr.Next;
  }
  Minimum = i + 1;
  Maximum = i;
  while (Exprs->U_1.V_1.Kind == Tree_NamedExpr) {
    i = Lookup(Exprs->U_1.V_59.NamedExpr.Name, Formals);
    if (i == 0) {
      Scanner_Error((STRING)"identifier not declared", 23L, Exprs->U_1.V_59.NamedExpr.Expr->U_1.V_60.Expr.Pos);
    } else if (PatternsPtr->A[i] != Tree_NoTree) {
      Scanner_Error((STRING)"pattern or argument multiply supplied", 37L, Exprs->U_1.V_59.NamedExpr.Expr->U_1.V_60.Expr.Pos);
    } else {
      PatternsPtr->A[i] = Exprs->U_1.V_59.NamedExpr.Expr;
    }
    Maximum = General_Max(Maximum, i);
    Exprs = Exprs->U_1.V_59.NamedExpr.Next;
  }
  Exprs = Tree_mOneExpr(Tree_mDontCare(Positions_NoPosition), Tree_mNoExpr(Positions_NoPosition));
  {
    LONGINT B_3 = Maximum, B_4 = Minimum;

    if (B_3 >= B_4)
      for (i = B_3;; i += -1) {
        if (PatternsPtr->A[i] == Tree_NoTree) {
          Exprs = Tree_mOneExpr(Tree_mDontCare1(Positions_NoPosition), Exprs);
        } else {
          Exprs = Tree_mOneExpr(PatternsPtr->A[i], Exprs);
        }
        if (i <= B_4) break;
      }
  }
  *Last = Exprs;
  DynArray_ReleaseArray((ADDRESS *)&PatternsPtr, &PatternsSize, (LONGINT)sizeof(Tree_tTree));
  return t;
}

static void CheckExprList
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr && Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    Scanner_Error((STRING)"too few expressions or arguments", 32L, t->U_1.V_57.NoExpr.Pos);
    return;
  }
  {
    register Tree_yOneExpr *W_20 = &t->U_1.V_58.OneExpr;

    if (W_20->Expr->U_1.V_1.Kind == Tree_DontCare) {
      return;
    }
    if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
      Scanner_Error((STRING)"too many expressions or arguments", 33L, W_20->Expr->U_1.V_60.Expr.Pos);
      return;
    }
    CheckExpr(W_20->Expr, Formals);
    CheckExprList(W_20->Next, Formals->U_1.V_86.Formal.Next);
  }
}

static void CheckInParams
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
  {
    register Tree_yOneExpr *W_21 = &t->U_1.V_58.OneExpr;

    if (W_21->Expr->U_1.V_1.Kind == Tree_DontCare) {
      return;
    }
    if (Formals->U_1.V_86.Formal.Path->U_1.V_92.Var.IsOutput && W_21->Expr->U_1.V_1.Kind == Tree_VarUse && W_21->Expr->U_1.V_62.VarUse.Object != Tree_NoTree && W_21->Expr->U_1.V_62.VarUse.Object->U_1.V_86.Formal.Path->U_1.V_1.Kind == Tree_Var && !W_21->Expr->U_1.V_62.VarUse.Object->U_1.V_86.Formal.Path->U_1.V_92.Var.IsOutput) {
      W_21->Expr->U_1.V_62.VarUse.Object->U_1.V_86.Formal.Path->U_1.V_92.Var.IsRegister = FALSE;
    }
    CheckInParams(W_21->Next, Formals->U_1.V_86.Formal.Next);
  }
}

static void CheckCallExprs
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoExpr && Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoExpr) {
    Scanner_Error((STRING)"too few expressions or arguments", 32L, t->U_1.V_57.NoExpr.Pos);
    return;
  }
  {
    register Tree_yOneExpr *W_22 = &t->U_1.V_58.OneExpr;

    if (W_22->Expr->U_1.V_1.Kind == Tree_DontCare) {
      W_22->Expr->U_1.V_54.DontCare.Tempos = MakeTempos(Formals);
      return;
    }
    if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
      Scanner_Error((STRING)"too many expressions or arguments", 33L, W_22->Expr->U_1.V_60.Expr.Pos);
      return;
    }
    CheckExprVar(W_22->Expr, Formals);
    CheckCallExprs(W_22->Next, Formals->U_1.V_86.Formal.Next);
  }
}

static void CheckExprVar
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_Compose) {
    t->U_1.V_61.Compose.Tempo = MakeVar();
    if (Formals->U_1.V_1.Kind == Tree_Formal) {
      t->U_1.V_61.Compose.TypeDesc = Formals->U_1.V_86.Formal.TypeDesc;
    } else {
      t->U_1.V_61.Compose.TypeDesc = t->U_1.V_61.Compose.Object->U_1.V_5.Class.TypeDesc;
    }
  } else if (t->U_1.V_1.Kind == Tree_DontCare1) {
    t->U_1.V_53.DontCare1.Tempo = MakeVar();
    if (Formals->U_1.V_1.Kind == Tree_Formal) {
      t->U_1.V_53.DontCare1.TypeDesc = Formals->U_1.V_86.Formal.TypeDesc;
    }
  }
  CheckExpr(t, Formals);
}

static void CheckExpr
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Compose:;
    {
      register Tree_yCompose *W_23 = &t->U_1.V_61.Compose;

      if (W_23->Selector != Idents_NoIdent) {
        Scanner_Warning((STRING)"label ignored", 13L, W_23->Pos);
      }
      if (Formals->U_1.V_1.Kind == Tree_Formal) {
        CheckSubtype(Formals->U_1.V_86.Formal.TypeDesc, W_23->Object->U_1.V_5.Class.TypeDesc, W_23->Pos);
      }
      if (W_23->Object == Tree_NoTree) {
        CheckExpr(W_23->Expr, dFormals);
      } else {
        CheckExpr2(W_23->Expr);
      }
      CheckExprList(W_23->Exprs, W_23->Object->U_1.V_5.Class.Formals);
    }
    break;
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_24 = &t->U_1.V_62.VarUse;

      if (Sets_IsElement((LONGCARD)W_24->Name, &LabelNames)) {
        W_24->Object = Semantics_IdentifyVar(Decls, W_24->Name);
        if (W_24->Object != Tree_NoTree && Formals->U_1.V_1.Kind == Tree_Formal) {
          CheckSubtype(Formals->U_1.V_86.Formal.TypeDesc, W_24->Object->U_1.V_86.Formal.TypeDesc, W_24->Pos);
        }
      } else if (!Sets_IsElement((LONGCARD)W_24->Name, &ExternNames) && !Sets_IsElement((LONGCARD)W_24->Name, &LocExternNames) && !Sets_IsElement((LONGCARD)W_24->Name, &UserNames)) {
        if (Sets_IsElement(ORD('e'), &Tree_Options)) {
          Scanner_ErrorI((STRING)"label not declared or computed", 30L, W_24->Pos, W_24->Name);
        } else if (Sets_IsElement(ORD('v'), &Tree_Options) && !Sets_IsElement(ORD('s'), &Tree_Options)) {
          Scanner_WarningI((STRING)"label not declared or computed", 30L, W_24->Pos, W_24->Name);
        }
        Sets_Include(&UserNames, (LONGCARD)W_24->Name);
      }
    }
    break;
  case Tree_Nil:;
    {
      register Tree_yNil *W_25 = &t->U_1.V_64.Nil;

      if (W_25->Selector != Idents_NoIdent) {
        Scanner_Warning((STRING)"label ignored", 13L, W_25->Pos);
      }
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_26 = &t->U_1.V_65.Call;

      if (W_26->Object == Tree_NoTree) {
        CheckExpr(W_26->Expr, dFormals);
        if (W_26->Expr->U_1.V_1.Kind == Tree_VarUse) {
          ProcName = W_26->Expr->U_1.V_62.VarUse.Name;
        } else if (W_26->Expr->U_1.V_1.Kind == Tree_Binary && W_26->Expr->U_1.V_66.Binary.Lop->U_1.V_1.Kind == Tree_VarUse) {
          ProcName = W_26->Expr->U_1.V_66.Binary.Lop->U_1.V_62.VarUse.Name;
        } else {
          ProcName = Idents_NoIdent;
        }
        if (!Sets_IsElement((LONGCARD)ProcName, &ExternNames) && !Sets_IsElement((LONGCARD)ProcName, &LocExternNames) && !Sets_IsElement((LONGCARD)ProcName, &UserNames)) {
          if (Sets_IsElement(ORD('e'), &Tree_Options)) {
            Scanner_ErrorI((STRING)"subroutine identifier not declared", 34L, W_26->Pos, ProcName);
          } else if (Sets_IsElement(ORD('v'), &Tree_Options) && !Sets_IsElement(ORD('s'), &Tree_Options)) {
            Scanner_WarningI((STRING)"subroutine identifier not declared", 34L, W_26->Pos, ProcName);
          }
          Sets_Include(&UserNames, (LONGCARD)ProcName);
        }
        CheckCallExprs(W_26->Exprs, dFormals);
        CheckCallExprs(W_26->Patterns, dFormals);
      } else if (Tree_IsType(W_26->Object, Tree_Routine)) {
        CheckExpr2(W_26->Expr);
        if (W_26->Object->U_1.V_1.Kind == Tree_Function && Formals->U_1.V_1.Kind == Tree_Formal) {
          CheckSubtype(Formals->U_1.V_86.Formal.TypeDesc, W_26->Object->U_1.V_34.Function.ReturnForm->U_1.V_86.Formal.TypeDesc, W_26->Pos);
        }
        CheckCallExprs(W_26->Exprs, W_26->Object->U_1.V_32.Routine.InForm);
        CheckCallPatterns(W_26->Patterns, W_26->Object->U_1.V_32.Routine.OutForm);
        CheckInParams(W_26->Exprs, W_26->Object->U_1.V_32.Routine.InForm);
      } else {
        Scanner_Error((STRING)"subroutine identifier required", 30L, W_26->Pos);
      }
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_27 = &t->U_1.V_66.Binary;

      CheckExprVar(W_27->Lop, dFormals);
      CheckExprVar(W_27->Rop, dFormals);
    }
    break;
  case Tree_PreOperator:;
  case Tree_PostOperator:;
    {
      register Tree_yPreOperator *W_28 = &t->U_1.V_67.PreOperator;

      CheckExprVar(W_28->Expr, Formals);
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_29 = &t->U_1.V_69.Index;

      CheckExprVar(W_29->Expr, dFormals);
      CheckExprList(W_29->Exprs, dFormals);
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_30 = &t->U_1.V_70.Parents;

      CheckExprVar(W_30->Expr, Formals);
    }
    break;
  case Tree_AttrDesc:;
    {
      register Tree_yAttrDesc *W_31 = &t->U_1.V_63.AttrDesc;

      if (Sets_IsElement((LONGCARD)W_31->Name, &LabelNames)) {
        W_31->Object = Semantics_IdentifyVar(Decls, W_31->Name);
        if (W_31->Object->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          ActClass = Semantics_LookupClass(W_31->Object->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&W_31->Object->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.Types));
          W_31->Type = ActClass->U_1.V_5.Class.Name;
        } else {
          Scanner_Error((STRING)"tree-type required", 18L, W_31->Pos);
        }
      } else {
        Scanner_Error((STRING)"label not declared or computed", 30L, W_31->Pos);
      }
    }
    break;
  default :
    break;
  }
}

static void CheckExpr2
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_VarUse:;
    {
      register Tree_yVarUse *W_32 = &t->U_1.V_62.VarUse;

      W_32->Object = Semantics_IdentifyVar(Decls, W_32->Name);
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_33 = &t->U_1.V_66.Binary;

      CheckExpr2(W_33->Lop);
      CheckExpr2(W_33->Rop);
    }
    break;
  case Tree_Compose:;
    CheckExpr(t, dFormals);
    break;
  }
}

static void CheckPatternList
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  Tree_tTree Pattern;

  if (t->U_1.V_1.Kind == Tree_NoPattern && Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    Scanner_Error((STRING)"too few patterns", 16L, t->U_1.V_44.NoPattern.Pos);
    return;
  }
  Pattern = t->U_1.V_45.OnePattern.Pattern;
  if (Pattern->U_1.V_1.Kind == Tree_DontCare) {
    return;
  }
  if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
    Scanner_Error((STRING)"too many patterns", 17L, t->U_1.V_45.OnePattern.Pattern->U_1.V_49.Pattern.Pos);
    return;
  }
  CheckPattern(Pattern, Formals, Formals->U_1.V_86.Formal.Path);
  CheckPatternList(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_86.Formal.Next);
}

static void CheckSubPatterns
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Tree_tTree Path)
# else
(t, Formals, Path)
Tree_tTree t, Formals, Path;
# endif
{
  Tree_tTree Pattern;

  if (t->U_1.V_1.Kind == Tree_NoPattern && Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    Scanner_Error((STRING)"too few patterns", 16L, t->U_1.V_44.NoPattern.Pos);
    return;
  }
  Pattern = t->U_1.V_45.OnePattern.Pattern;
  if (Pattern->U_1.V_1.Kind == Tree_DontCare) {
    return;
  }
  if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
    Scanner_Error((STRING)"too many patterns", 17L, Pattern->U_1.V_49.Pattern.Pos);
    return;
  }
  CheckPattern(Pattern, Formals, Tree_mField(Path, Formals->U_1.V_86.Formal.Name));
  CheckSubPatterns(t->U_1.V_45.OnePattern.Next, Formals->U_1.V_86.Formal.Next, Path);
}

static void CheckCallPatterns
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals)
# else
(t, Formals)
Tree_tTree t, Formals;
# endif
{
  if (t->U_1.V_1.Kind == Tree_NoPattern && Formals->U_1.V_1.Kind != Tree_Formal) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_NoPattern) {
    Scanner_Error((STRING)"too few patterns or arguments", 29L, t->U_1.V_44.NoPattern.Pos);
    return;
  }
  {
    register Tree_yOnePattern *W_34 = &t->U_1.V_45.OnePattern;

    if (W_34->Pattern->U_1.V_1.Kind == Tree_DontCare) {
      W_34->Pattern->U_1.V_54.DontCare.Tempos = MakeTempos(Formals);
      return;
    }
    if (Formals->U_1.V_1.Kind == Tree_NoFormal) {
      Scanner_Error((STRING)"too many patterns or arguments", 30L, W_34->Pattern->U_1.V_49.Pattern.Pos);
      return;
    }
    W_34->Pattern->U_1.V_49.Pattern.Tempo = MakeVar();
    W_34->Pattern->U_1.V_49.Pattern.TypeDesc = Formals->U_1.V_86.Formal.TypeDesc;
    CheckPattern(W_34->Pattern, Formals, Tree_mVar(W_34->Pattern->U_1.V_49.Pattern.Tempo, FALSE, TRUE));
    CheckCallPatterns(W_34->Next, Formals->U_1.V_86.Formal.Next);
  }
}

static void CheckPattern
# ifdef __STDC__
(Tree_tTree t, Tree_tTree Formals, Tree_tTree Path)
# else
(t, Formals, Path)
Tree_tTree t, Formals, Path;
# endif
{
  t->U_1.V_49.Pattern.Path = Path;
  switch (t->U_1.V_1.Kind) {
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_35 = &t->U_1.V_50.Decompose;

      if (W_35->Selector != Idents_NoIdent) {
        if (Sets_IsElement((LONGCARD)W_35->Selector, &LabelNames)) {
          Scanner_Error((STRING)"label multiply declared", 23L, W_35->Pos);
        } else {
          Sets_Include(&LabelNames, (LONGCARD)W_35->Selector);
        }
        if (W_35->Widen && Formals->U_1.V_1.Kind == Tree_Formal) {
          Decls = Tree_mFormal(Decls, W_35->Selector, Formals->U_1.V_86.Formal.TypeDesc, W_35->Path);
        } else {
          Decls = Tree_mFormal(Decls, W_35->Selector, W_35->Object->U_1.V_5.Class.TypeDesc, W_35->Path);
        }
      }
      if (Formals->U_1.V_1.Kind == Tree_Formal) {
        CheckSubtype(Formals->U_1.V_86.Formal.TypeDesc, W_35->Object->U_1.V_5.Class.TypeDesc, W_35->Pos);
      }
      if (W_35->Object == Tree_NoTree) {
        CheckExpr(W_35->Expr, dFormals);
      } else {
        CheckExpr2(W_35->Expr);
      }
      CheckSubPatterns(W_35->Patterns, W_35->Object->U_1.V_5.Class.Formals, Tree_mConsType(W_35->Path, W_35->Object->U_1.V_5.Class.Name));
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_36 = &t->U_1.V_51.VarDef;

      if (Sets_IsElement((LONGCARD)W_36->Name, &LabelNames)) {
        if (!Sets_IsElement(ORD('k'), &Tree_Options)) {
          Scanner_Error((STRING)"label multiply declared", 23L, W_36->Pos);
        }
        W_36->Object = Semantics_IdentifyVar(Decls, W_36->Name);
        if (Formals->U_1.V_1.Kind == Tree_Formal) {
          CheckType(Formals->U_1.V_86.Formal.TypeDesc, W_36->Object->U_1.V_86.Formal.TypeDesc, W_36->Pos);
        }
      } else {
        Sets_Include(&LabelNames, (LONGCARD)W_36->Name);
        if (Formals->U_1.V_1.Kind == Tree_Formal) {
          Decls = Tree_mFormal(Decls, W_36->Name, Formals->U_1.V_86.Formal.TypeDesc, W_36->Path);
        }
        W_36->Object = Tree_NoTree;
      }
    }
    break;
  case Tree_NilTest:;
    {
      register Tree_yNilTest *W_37 = &t->U_1.V_52.NilTest;

      if (W_37->Selector != Idents_NoIdent) {
        if (Sets_IsElement((LONGCARD)W_37->Selector, &LabelNames)) {
          Scanner_Error((STRING)"label multiply declared", 23L, W_37->Pos);
        } else {
          Sets_Include(&LabelNames, (LONGCARD)W_37->Selector);
        }
        if (Formals->U_1.V_1.Kind == Tree_Formal) {
          Decls = Tree_mFormal(Decls, W_37->Selector, Formals->U_1.V_86.Formal.TypeDesc, W_37->Path);
        }
      }
    }
    break;
  case Tree_Value:;
    CheckExprVar(t->U_1.V_55.Value.Expr, dFormals);
    break;
  default :
    break;
  }
}

static Idents_tIdent MakeVar
# ifdef __STDC__
()
# else
()
# endif
{
  Strings_tString String1, String2;

  INC(VarCount);
  Strings_ArrayToString((STRING)"yyV", 3L, &String1);
  Strings_IntToString(VarCount, &String2);
  Strings_Concatenate(&String1, &String2);
  return Idents_MakeIdent(&String1);
}

static Tree_tTree MakeTempos
# ifdef __STDC__
(Tree_tTree Formals)
# else
(Formals)
Tree_tTree Formals;
# endif
{
  if (Formals->U_1.V_1.Kind == Tree_Formal) {
    {
      register Tree_yFormal *W_38 = &Formals->U_1.V_86.Formal;

      return Tree_mFormal(MakeTempos(W_38->Next), MakeVar(), W_38->TypeDesc, W_38->Path);
    }
  } else {
    return nNoFormal;
  }
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
  IO_WriteS((System_tFile)IO_StdError, (STRING)"Error: module Semantics, routine ", 33L);
  IO_WriteS((System_tFile)IO_StdError, yyFunction, O_1);
  IO_WriteS((System_tFile)IO_StdError, (STRING)" failed", 7L);
  IO_WriteNl((System_tFile)IO_StdError);
  (*Semantics_Exit)();
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
    LONGINT B_5 = 0, B_6 = (INTEGER)(O_3 - 1);

    if (B_5 <= B_6)
      for (yyi = B_5;; yyi += 1) {
        if (yya[yyi] != yyb[yyi]) {
          FREE_OPEN_ARRAYS
          return FALSE;
        }
        if (yyi >= B_6) break;
      }
  }
  FREE_OPEN_ARRAYS
  return TRUE;
}

void Semantics_Semantics
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
      register Tree_ySpec *W_39 = &t->U_1.V_26.Spec;

      Semantics_TypeCount = Idents_MaxIdent();
      Sets_MakeSet(&RoutineNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&LabelNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&ParamNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&Semantics_TypeNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&ExternNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&LocExternNames, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&Semantics_UserTypes, (LONGCARD)Semantics_TypeCount);
      Sets_MakeSet(&UserNames, (LONGCARD)Semantics_TypeCount);
      ClassFormals(W_39->TreeNames);
      Semantics_Semantics(W_39->Public);
      CollectExtern(W_39->Extern, &ExternNames);
      ProcFormals(W_39->Routines);
      Semantics_Semantics(W_39->Routines);
      if (Sets_IsElement(ORD('o'), &Tree_Options) && !Sets_IsEmpty(UserNames)) {
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"Undefined External Names", 24L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteS((System_tFile)IO_StdOutput, (STRING)"------------------------", 24L);
        IO_WriteNl((System_tFile)IO_StdOutput);
        IO_WriteNl((System_tFile)IO_StdOutput);
        {
          LONGCARD B_7 = 1, B_8 = Semantics_TypeCount;

          if (B_7 <= B_8)
            for (i = B_7;; i += 1) {
              if (Sets_IsElement(i, &UserNames)) {
                Idents_WriteIdent((System_tFile)IO_StdOutput, (SHORTCARD)i);
                IO_WriteNl((System_tFile)IO_StdOutput);
              }
              if (i >= B_8) break;
            }
        }
      }
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_40 = &t->U_1.V_25.Name;

      W_40->Object = IdentifyProc(W_40->Name);
      if (W_40->Object == Tree_NoTree) {
        Scanner_ErrorI((STRING)"subroutine identifier not declared", 34L, W_40->Pos, W_40->Name);
      } else {
        W_40->Object->U_1.V_32.Routine.IsExtern = TRUE;
      }
      Semantics_Semantics(W_40->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Procedure) {
    {
      register Tree_yProcedure *W_41 = &t->U_1.V_33.Procedure;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_41->Extern, &LocExternNames);
      if (Sets_IsElement((LONGCARD)W_41->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier multiply declared", 36L, W_41->Pos);
      } else {
        Sets_Include(&RoutineNames, (LONGCARD)W_41->Name);
      }
      Sets_AssignEmpty(&ParamNames);
      Check(W_41->InParams);
      Check(W_41->OutParams);
      InFormals = W_41->InForm;
      OutFormals = W_41->OutForm;
      Parameters = W_41->ParamDecls;
      IsFunction = FALSE;
      RuleCount = 0;
      Check(W_41->Rules);
      Semantics_Semantics(W_41->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Predicate) {
    {
      register Tree_yPredicate *W_42 = &t->U_1.V_35.Predicate;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_42->Extern, &LocExternNames);
      if (Sets_IsElement((LONGCARD)W_42->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier multiply declared", 36L, W_42->Pos);
      } else {
        Sets_Include(&RoutineNames, (LONGCARD)W_42->Name);
      }
      Sets_AssignEmpty(&ParamNames);
      Check(W_42->InParams);
      Check(W_42->OutParams);
      InFormals = W_42->InForm;
      OutFormals = W_42->OutForm;
      Parameters = W_42->ParamDecls;
      IsFunction = FALSE;
      RuleCount = 0;
      Check(W_42->Rules);
      Semantics_Semantics(W_42->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Function) {
    {
      register Tree_yFunction *W_43 = &t->U_1.V_34.Function;

      Sets_AssignEmpty(&LocExternNames);
      CollectExtern(W_43->Extern, &LocExternNames);
      if (Sets_IsElement((LONGCARD)W_43->Name, &RoutineNames)) {
        Scanner_Error((STRING)"routine identifier multiply declared", 36L, W_43->Pos);
      } else {
        Sets_Include(&RoutineNames, (LONGCARD)W_43->Name);
      }
      Sets_AssignEmpty(&ParamNames);
      Check(W_43->InParams);
      Check(W_43->OutParams);
      Check(W_43->ReturnParams);
      InFormals = W_43->InForm;
      OutFormals = W_43->OutForm;
      ReturnFormal = W_43->ReturnForm;
      Parameters = W_43->ParamDecls;
      IsFunction = TRUE;
      RuleCount = 0;
      Check(W_43->Rules);
      Semantics_Semantics(W_43->Next);
      return;
    }
  }
}

static void CollectExtern
# ifdef __STDC__
(Tree_tTree t, Sets_tSet *Names)
# else
(t, Names)
Tree_tTree t;
Sets_tSet *Names;
# endif
{
  struct S_5 yyTempo;

  if (t == Tree_NoTree) {
    return;
  }
  if (t->U_1.V_1.Kind == Tree_Name) {
    {
      register Tree_yName *W_44 = &t->U_1.V_25.Name;

      Sets_Include(Names, (LONGCARD)W_44->Name);
      CollectExtern(W_44->Next, Names);
      return;
    }
  }
}

static void ProcFormals
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
  switch (t->U_1.V_1.Kind) {
  case Tree_Procedure:;
    {
      register Tree_yProcedure *W_45 = &t->U_1.V_33.Procedure;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_45->InParams);
      W_45->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_45->OutParams);
      W_45->OutForm = Tree_ReverseTree(Args);
      W_45->ParamDecls = Decls;
      ProcFormals(W_45->Next);
      return;
    }
    break;
  case Tree_Predicate:;
    {
      register Tree_yPredicate *W_46 = &t->U_1.V_35.Predicate;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_46->InParams);
      W_46->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_46->OutParams);
      W_46->OutForm = Tree_ReverseTree(Args);
      W_46->ParamDecls = Decls;
      ProcFormals(W_46->Next);
      return;
    }
    break;
  case Tree_Function:;
    {
      register Tree_yFunction *W_47 = &t->U_1.V_34.Function;

      Args = nNoFormal;
      Decls = nNoFormal;
      Sets_AssignEmpty(&ParamNames);
      IsOutput = FALSE;
      ProcFormals(W_47->InParams);
      W_47->InForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_47->OutParams);
      W_47->OutForm = Tree_ReverseTree(Args);
      Args = nNoFormal;
      IsOutput = TRUE;
      ProcFormals(W_47->ReturnParams);
      W_47->ReturnForm = Tree_ReverseTree(Args);
      W_47->ParamDecls = Decls;
      ProcFormals(W_47->Next);
      return;
    }
    break;
  case Tree_Param:;
    {
      register Tree_yParam *W_48 = &t->U_1.V_38.Param;

      if (Sets_IsElement((LONGCARD)W_48->Name, &ParamNames)) {
        Scanner_Error((STRING)"parameter identifier multiply declared", 38L, W_48->Pos);
      } else {
        Sets_Include(&ParamNames, (LONGCARD)W_48->Name);
      }
      ParamName = W_48->Name;
      Mode = W_48->IsRef;
      ProcFormals(W_48->Type);
      ProcFormals(W_48->Next);
      return;
    }
    break;
  case Tree_Type:;
    {
      register Tree_yType *W_49 = &t->U_1.V_39.Type;

      if (W_49->Name != Idents_NoIdent && W_49->Names->U_1.V_1.Kind != Tree_NoName) {
        TreeName = IdentifyTree(W_49->Name);
        if (TreeName != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (LONGCARD)TreeName->U_1.V_29.TreeName.ClassCount);
        } else {
          Scanner_Error((STRING)"tree type not declared", 22L, W_49->Pos);
        }
      } else if (W_49->Name != Idents_NoIdent && W_49->Names->U_1.V_1.Kind == Tree_NoName) {
        TreeName = IdentifyTree(W_49->Name);
        if (TreeName != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (LONGCARD)TreeName->U_1.V_29.TreeName.ClassCount);
          MakeTypes((LONGINT)TreeName->U_1.V_29.TreeName.Classes->U_1.V_5.Class.Index, TreeName->U_1.V_29.TreeName.Classes, &ActTypes);
        } else {
          ActClass = IdentifyClass2(W_49->Name, &TreeName);
          if (ActClass != Tree_NoTree) {
            Sets_MakeSet(&ActTypes, (LONGCARD)TreeName->U_1.V_29.TreeName.ClassCount);
            MakeTypes((LONGINT)ActClass->U_1.V_5.Class.Index, ActClass->U_1.V_5.Class.Extensions, &ActTypes);
          }
        }
      } else if (W_49->Name == Idents_NoIdent && W_49->Names->U_1.V_1.Kind != Tree_NoName) {
        ActClass = IdentifyClass2(W_49->Names->U_1.V_25.Name.Name, &TreeName);
        if (ActClass != Tree_NoTree) {
          Sets_MakeSet(&ActTypes, (LONGCARD)TreeName->U_1.V_29.TreeName.ClassCount);
        } else {
          Scanner_Error((STRING)"node type not declared", 22L, W_49->Names->U_1.V_25.Name.Pos);
        }
      } else {
        TreeName = Tree_NoTree;
      }
      if (TreeName != Tree_NoTree) {
        ActTree = TreeName->U_1.V_29.TreeName.Classes;
        ProcFormals(W_49->Names);
        Node = Tree_mNodeTypes(TreeName, ActTypes);
      } else {
        if (W_49->Name == Idents_NoIdent) {
          Scanner_Error((STRING)"incorrect type", 14L, W_49->Pos);
        } else {
          Sets_Include(&Semantics_TypeNames, (LONGCARD)W_49->Name);
        }
        Node = Tree_mUserType(W_49->Name);
      }
      Var = Tree_mVar(ParamName, (BOOLEAN)(IsOutput || Mode), TRUE);
      Args = Tree_mFormal(Args, ParamName, Node, Var);
      Decls = Tree_mFormal(Decls, ParamName, Node, Var);
      return;
    }
    break;
  case Tree_Name:;
    {
      register Tree_yName *W_50 = &t->U_1.V_25.Name;

      ActClass = IdentifyClass(ActTree, W_50->Name);
      if (ActClass != Tree_NoTree) {
        Sets_Include(&ActTypes, (LONGCARD)ActClass->U_1.V_5.Class.Index);
        Tree_ForallClasses(ActClass->U_1.V_5.Class.Extensions, (Tree_ProcOfT)ProcFormals);
      } else {
        Scanner_Error((STRING)"node type not declared", 22L, W_50->Pos);
      }
      ProcFormals(W_50->Next);
      return;
    }
    break;
  case Tree_Class:;
    {
      register Tree_yClass *W_51 = &t->U_1.V_5.Class;

      Sets_Include(&ActTypes, (LONGCARD)W_51->Index);
      return;
    }
    break;
  default :
    break;
  }
}

static void ClassFormals
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
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register Tree_yTreeName *W_52 = &t->U_1.V_29.TreeName;

      ActTree = t;
      W_52->ClassCount = 0;
      Tree_ForallClasses(W_52->Classes, (Tree_ProcOfT)CountClasses);
      Tree_ForallClasses(W_52->Classes, (Tree_ProcOfT)ClassTypes);
      Tree_ForallClasses(W_52->Classes, (Tree_ProcOfT)ClassFormals);
      ClassFormals(W_52->Next);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_53 = &t->U_1.V_5.Class;

      Args = nNoFormal;
      Tree_ForallAttributes(t, (Tree_ProcOfT)ClassFormals);
      W_53->Formals = Tree_ReverseTree(Args);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Child) {
    {
      register Tree_yChild *W_54 = &t->U_1.V_9.Child;

      ActClass = IdentifyClass(ActTree->U_1.V_29.TreeName.Classes, W_54->Type);
      Args = Tree_mFormal(Args, W_54->Name, ActClass->U_1.V_5.Class.TypeDesc, (Tree_tTree)Tree_NoTree);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Attribute) {
    {
      register Tree_yAttribute *W_55 = &t->U_1.V_10.Attribute;

      if (((SET_ELEM(Tree_Test) | SET_ELEM(Tree_Dummy)) & W_55->Properties) == 0X0L) {
        Args = Tree_mFormal(Args, W_55->Name, Tree_mUserType(W_55->Type), (Tree_tTree)Tree_NoTree);
        Sets_Include(&Semantics_TypeNames, (LONGCARD)W_55->Type);
      }
      return;
    }
  }
}

static void CountClasses
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_56 = &t->U_1.V_5.Class;

      INC(ActTree->U_1.V_29.TreeName.ClassCount);
      W_56->Index = ActTree->U_1.V_29.TreeName.ClassCount;
      return;
    }
  }
}

static void ClassTypes
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
  if (t->U_1.V_1.Kind == Tree_Class) {
    {
      register Tree_yClass *W_57 = &t->U_1.V_5.Class;

      W_57->TypeDesc = Tree_mNodeTypes(ActTree, ActTypes);
      Sets_MakeSet(&W_57->TypeDesc->U_1.V_89.NodeTypes.Types, (LONGCARD)ActTree->U_1.V_29.TreeName.ClassCount);
      MakeTypes((LONGINT)W_57->Index, W_57->Extensions, &W_57->TypeDesc->U_1.V_89.NodeTypes.Types);
      return;
    }
  }
}

static void Check
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
  if (t->U_1.V_1.Kind == Tree_Reject) {
    if (Tree_IsType(t->U_1.V_79.Reject.Next, Tree_Statement)) {
      for (;;) {
        {
          register Tree_yReject *W_58 = &t->U_1.V_79.Reject;

          Scanner_Warning((STRING)"statement not reachable", 23L, t->U_1.V_79.Reject.Next->U_1.V_75.Statement.Pos);
          goto EXIT_1;
        }
      } EXIT_1:;
    }
  }
  if (t->U_1.V_1.Kind == Tree_Fail) {
    if (Tree_IsType(t->U_1.V_80.Fail.Next, Tree_Statement)) {
      for (;;) {
        {
          register Tree_yFail *W_59 = &t->U_1.V_80.Fail;

          Scanner_Warning((STRING)"statement not reachable", 23L, t->U_1.V_80.Fail.Next->U_1.V_75.Statement.Pos);
          goto EXIT_2;
        }
      } EXIT_2:;
    }
    {
      register Tree_yFail *W_60 = &t->U_1.V_80.Fail;

      if (IsFunction) {
        Scanner_Error((STRING)"FAIL not allowed in function", 28L, W_60->Pos);
      }
      Check(W_60->Next);
      return;
    }
  }
  switch (t->U_1.V_1.Kind) {
  case Tree_Param:;
    {
      register Tree_yParam *W_61 = &t->U_1.V_38.Param;

      Sets_Include(&ParamNames, (LONGCARD)W_61->Name);
      Check(W_61->Next);
      return;
    }
    break;
  case Tree_Rule:;
    {
      register Tree_yRule *W_62 = &t->U_1.V_42.Rule;

      INC(RuleCount);
      W_62->Index = RuleCount;
      W_62->Patterns = TransformName(W_62->Patterns, InFormals);
      W_62->Patterns = TransformPattern(W_62->Patterns);
      W_62->Exprs = TransformName(W_62->Exprs, OutFormals);
      W_62->Exprs = TransformExpr(W_62->Exprs);
      W_62->Expr = TransformExpr(W_62->Expr);
      W_62->Statements = TransformStmt(W_62->Statements);
      VarCount = 0;
      HasLocals = FALSE;
      Decls = Parameters;
      Sets_Assign(&LabelNames, ParamNames);
      CheckPatternList(W_62->Patterns, InFormals);
      Check(W_62->Patterns);
      Check(W_62->Statements);
      CheckExprList(W_62->Exprs, OutFormals);
      Check(W_62->Exprs);
      if (IsFunction) {
        if (W_62->Expr->U_1.V_1.Kind == Tree_NoExpr) {
          if (!HasReject(W_62->Statements)) {
            Scanner_Error((STRING)"function requires RETURN expression", 35L, W_62->Expr->U_1.V_60.Expr.Pos);
          }
        } else {
          CheckExprVar(W_62->Expr, ReturnFormal);
          Success = FALSE;
          Check(W_62->Expr);
          W_62->HasPatterns = Success;
          if (W_62->HasPatterns && W_62->Expr->U_1.V_1.Kind != Tree_Compose && t->U_1.V_1.Kind != Tree_DontCare1) {
            W_62->Tempo = MakeVar();
          }
        }
      }
      if (!IsFunction && W_62->Expr->U_1.V_1.Kind != Tree_NoExpr) {
        Scanner_Error((STRING)"illegal RETURN", 14L, W_62->Expr->U_1.V_60.Expr.Pos);
      }
      W_62->VarDecls = Decls;
      if (Sets_IsElement(ORD('c'), &Tree_Options)) {
        W_62->HasTempos = VarCount > 0 || HasLocals;
      } else {
        W_62->HasTempos = VarCount > 0 || HasLocals || W_62->HasPatterns;
      }
      CheckTargetCode(W_62->Patterns);
      CheckTargetCode(W_62->Exprs);
      if (IsFunction) {
        CheckTargetCode(W_62->Expr);
      }
      CheckTargetCode(W_62->Statements);
      Check(W_62->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_63 = &t->U_1.V_76.ProcCall;

      CheckExprVar(W_63->Call, dFormals);
      Check(W_63->Call);
      Check(W_63->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_64 = &t->U_1.V_77.Condition;

      CheckExprVar(W_64->Expr, dFormals);
      Check(W_64->Expr);
      Check(W_64->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_65 = &t->U_1.V_78.Assignment;

      if (W_65->Adr->U_1.V_1.Kind == Tree_VarUse) {
        W_65->Object = Semantics_IdentifyVar(Decls, W_65->Adr->U_1.V_62.VarUse.Name);
      } else {
        W_65->Object = Tree_NoTree;
      }
      CheckExprVar(W_65->Adr, dFormals);
      if (W_65->Object != Tree_NoTree) {
        CheckExprVar(W_65->Expr, W_65->Object);
      } else {
        CheckExprVar(W_65->Expr, dFormals);
      }
      Check(W_65->Adr);
      Check(W_65->Expr);
      Check(W_65->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_66 = &t->U_1.V_81.TargetStmt;

      CheckTargetCode(W_66->Parameters);
      Sets_MakeSet(&W_66->UsedNames, (LONGCARD)Idents_MaxIdent());
      ActNames = W_66->UsedNames;
      Check(W_66->Stmt);
      W_66->UsedNames = ActNames;
      Check(W_66->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_67 = &t->U_1.V_75.Statement;

      Check(W_67->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_68 = &t->U_1.V_45.OnePattern;

      Check(W_68->Pattern);
      Check(W_68->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_69 = &t->U_1.V_58.OneExpr;

      Check(W_69->Expr);
      Check(W_69->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_70 = &t->U_1.V_50.Decompose;

      Check(W_70->Expr);
      Success = TRUE;
      Check(W_70->Patterns);
      return;
    }
    break;
  case Tree_VarDef:;
    {
      register Tree_yVarDef *W_71 = &t->U_1.V_51.VarDef;

      if (W_71->Object != Tree_NoTree) {
        Success = TRUE;
      }
      return;
    }
    break;
  case Tree_NilTest:;
    {
      register Tree_yNilTest *W_72 = &t->U_1.V_52.NilTest;

      Success = TRUE;
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_73 = &t->U_1.V_55.Value;

      Success = TRUE;
      Check(W_73->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_74 = &t->U_1.V_61.Compose;

      Check(W_74->Expr);
      Check(W_74->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_75 = &t->U_1.V_65.Call;

      Check(W_75->Expr);
      Check(W_75->Exprs);
      Check(W_75->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_76 = &t->U_1.V_66.Binary;

      Check(W_76->Lop);
      Check(W_76->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_77 = &t->U_1.V_67.PreOperator;

      Check(W_77->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_78 = &t->U_1.V_68.PostOperator;

      Check(W_78->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_79 = &t->U_1.V_70.Parents;

      Check(W_79->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_80 = &t->U_1.V_69.Index;

      Check(W_80->Expr);
      Check(W_80->Exprs);
      return;
    }
    break;
  case Tree_TargetExpr:;
    {
      register Tree_yTargetExpr *W_81 = &t->U_1.V_71.TargetExpr;

      Sets_MakeSet(&W_81->UsedNames, (LONGCARD)Idents_MaxIdent());
      ActNames = W_81->UsedNames;
      Check(W_81->Expr);
      W_81->UsedNames = ActNames;
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_82 = &t->U_1.V_16.Ident;

      if (Semantics_IdentifyVar(Decls, W_82->Attribute) == Tree_NoTree) {
        Sets_Include(&ActNames, (LONGCARD)W_82->Attribute);
      }
      Check(W_82->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_83 = &t->U_1.V_18.Any;

      Check(W_83->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_84 = &t->U_1.V_19.Anys;

      Check(W_84->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_85 = &t->U_1.V_15.Designator;

      if (Sets_IsElement((LONGCARD)W_85->Selector, &LabelNames)) {
        W_85->Object = Semantics_IdentifyVar(Decls, W_85->Selector);
        if (W_85->Object->U_1.V_86.Formal.TypeDesc->U_1.V_1.Kind == Tree_NodeTypes) {
          ActClass = Semantics_LookupClass(W_85->Object->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.TreeName->U_1.V_29.TreeName.Classes, Sets_Minimum(&W_85->Object->U_1.V_86.Formal.TypeDesc->U_1.V_89.NodeTypes.Types));
          W_85->Type = ActClass->U_1.V_5.Class.Name;
        } else {
          Scanner_Error((STRING)"tree-type required", 18L, W_85->Pos);
        }
      } else {
        Scanner_Error((STRING)"label not declared or computed", 30L, W_85->Pos);
      }
      Check(W_85->Next);
      return;
    }
    break;
  default :
    break;
  }
}

static void CheckTargetCode
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
  case Tree_Param:;
    {
      register Tree_yParam *W_86 = &t->U_1.V_38.Param;

      HasLocals = TRUE;
      ParamName = W_86->Name;
      IsOutput = FALSE;
      ProcFormals(W_86->Type);
      if (Sets_IsElement((LONGCARD)W_86->Name, &LabelNames)) {
        Scanner_Error((STRING)"label multiply declared or computed", 35L, W_86->Pos);
      } else {
        Sets_Include(&LabelNames, (LONGCARD)W_86->Name);
      }
      CheckTargetCode(W_86->Next);
      return;
    }
    break;
  case Tree_ProcCall:;
    {
      register Tree_yProcCall *W_87 = &t->U_1.V_76.ProcCall;

      CheckTargetCode(W_87->Call);
      CheckTargetCode(W_87->Next);
      return;
    }
    break;
  case Tree_Condition:;
    {
      register Tree_yCondition *W_88 = &t->U_1.V_77.Condition;

      CheckTargetCode(W_88->Expr);
      CheckTargetCode(W_88->Next);
      return;
    }
    break;
  case Tree_Assignment:;
    {
      register Tree_yAssignment *W_89 = &t->U_1.V_78.Assignment;

      CheckTargetCode(W_89->Expr);
      CheckTargetCode(W_89->Next);
      return;
    }
    break;
  case Tree_TargetStmt:;
    {
      register Tree_yTargetStmt *W_90 = &t->U_1.V_81.TargetStmt;

      ActNames = W_90->UsedNames;
      CheckTargetCode(W_90->Stmt);
      Sets_ReleaseSet(&W_90->UsedNames);
      CheckTargetCode(W_90->Next);
      return;
    }
    break;
  case Tree_Statement:;
  case Tree_Reject:;
  case Tree_Fail:;
  case Tree_Nl:;
  case Tree_WriteStr:;
    {
      register Tree_yStatement *W_91 = &t->U_1.V_75.Statement;

      CheckTargetCode(W_91->Next);
      return;
    }
    break;
  case Tree_OnePattern:;
    {
      register Tree_yOnePattern *W_92 = &t->U_1.V_45.OnePattern;

      CheckTargetCode(W_92->Pattern);
      CheckTargetCode(W_92->Next);
      return;
    }
    break;
  case Tree_OneExpr:;
  case Tree_NamedExpr:;
    {
      register Tree_yOneExpr *W_93 = &t->U_1.V_58.OneExpr;

      CheckTargetCode(W_93->Expr);
      CheckTargetCode(W_93->Next);
      return;
    }
    break;
  case Tree_Decompose:;
    {
      register Tree_yDecompose *W_94 = &t->U_1.V_50.Decompose;

      CheckTargetCode(W_94->Expr);
      CheckTargetCode(W_94->Patterns);
      return;
    }
    break;
  case Tree_Value:;
    {
      register Tree_yValue *W_95 = &t->U_1.V_55.Value;

      CheckTargetCode(W_95->Expr);
      return;
    }
    break;
  case Tree_Compose:;
    {
      register Tree_yCompose *W_96 = &t->U_1.V_61.Compose;

      CheckTargetCode(W_96->Expr);
      CheckTargetCode(W_96->Exprs);
      return;
    }
    break;
  case Tree_Call:;
    {
      register Tree_yCall *W_97 = &t->U_1.V_65.Call;

      CheckTargetCode(W_97->Expr);
      CheckTargetCode(W_97->Exprs);
      CheckTargetCode(W_97->Patterns);
      return;
    }
    break;
  case Tree_Binary:;
    {
      register Tree_yBinary *W_98 = &t->U_1.V_66.Binary;

      CheckTargetCode(W_98->Lop);
      CheckTargetCode(W_98->Rop);
      return;
    }
    break;
  case Tree_PreOperator:;
    {
      register Tree_yPreOperator *W_99 = &t->U_1.V_67.PreOperator;

      CheckTargetCode(W_99->Expr);
      return;
    }
    break;
  case Tree_PostOperator:;
    {
      register Tree_yPostOperator *W_100 = &t->U_1.V_68.PostOperator;

      CheckTargetCode(W_100->Expr);
      return;
    }
    break;
  case Tree_Parents:;
    {
      register Tree_yParents *W_101 = &t->U_1.V_70.Parents;

      CheckTargetCode(W_101->Expr);
      return;
    }
    break;
  case Tree_Index:;
    {
      register Tree_yIndex *W_102 = &t->U_1.V_69.Index;

      CheckTargetCode(W_102->Expr);
      CheckTargetCode(W_102->Exprs);
      return;
    }
    break;
  case Tree_TargetExpr:;
    {
      register Tree_yTargetExpr *W_103 = &t->U_1.V_71.TargetExpr;

      ActNames = W_103->UsedNames;
      CheckTargetCode(W_103->Expr);
      Sets_ReleaseSet(&W_103->UsedNames);
      return;
    }
    break;
  case Tree_Ident:;
    {
      register Tree_yIdent *W_104 = &t->U_1.V_16.Ident;

      if (Sets_IsElement((LONGCARD)W_104->Attribute, &ActNames) && Semantics_IdentifyVar(Decls, W_104->Attribute) != Tree_NoTree) {
        Scanner_Error((STRING)"label not computed yet", 22L, W_104->Pos);
      }
      CheckTargetCode(W_104->Next);
      return;
    }
    break;
  case Tree_Any:;
    {
      register Tree_yAny *W_105 = &t->U_1.V_18.Any;

      CheckTargetCode(W_105->Next);
      return;
    }
    break;
  case Tree_Anys:;
    {
      register Tree_yAnys *W_106 = &t->U_1.V_19.Anys;

      CheckTargetCode(W_106->Next);
      return;
    }
    break;
  case Tree_Designator:;
    {
      register Tree_yDesignator *W_107 = &t->U_1.V_15.Designator;

      CheckTargetCode(W_107->Next);
      return;
    }
    break;
  default :
    break;
  }
}

void Semantics_RemoveTreeTypes
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
  if (t->U_1.V_1.Kind == Tree_Spec) {
    {
      register Tree_ySpec *W_108 = &t->U_1.V_26.Spec;

      Semantics_RemoveTreeTypes(W_108->TreeNames);
      return;
    }
  }
  if (t->U_1.V_1.Kind == Tree_TreeName) {
    {
      register struct S_13 *W_109 = &yyTempo.U_1.V_1.yyR2;

      {
        register Tree_yTreeName *W_110 = &t->U_1.V_29.TreeName;

        Strings_ArrayToString((STRING)"t", 1L, &W_109->String1);
        Idents_GetString(W_110->Name, &W_109->String2);
        Strings_Concatenate(&W_109->String1, &W_109->String2);
        W_109->i = Idents_MakeIdent(&W_109->String1);
        if (W_109->i <= Semantics_TypeCount) {
          Sets_Exclude(&Semantics_TypeNames, (LONGCARD)W_109->i);
        }
        Semantics_RemoveTreeTypes(W_110->Next);
        return;
      }
    }
  }
}

static BOOLEAN HasReject
# ifdef __STDC__
(Tree_tTree yyP1)
# else
(yyP1)
Tree_tTree yyP1;
# endif
{
  struct S_14 yyTempo;

  if (yyP1 == Tree_NoTree) {
    return FALSE;
  }
  if (yyP1->U_1.V_1.Kind == Tree_Reject) {
    return TRUE;
  }
  if (Tree_IsType(yyP1, Tree_Statement)) {
    for (;;) {
      {
        register Tree_yStatement *W_111 = &yyP1->U_1.V_75.Statement;

        if (!HasReject(W_111->Next)) {
          goto EXIT_3;
        }
        return TRUE;
      }
    } EXIT_3:;
  }
  return FALSE;
}

void Semantics_BeginSemantics
# ifdef __STDC__
()
# else
()
# endif
{
  dFormals = Tree_mDummyFormal((Tree_tTree)Tree_NoTree);
  dFormals->U_1.V_87.DummyFormal.Next = dFormals;
  nNoFormal = Tree_mNoFormal();
  Strings_ArrayToString((STRING)".", 1L, &String1);
}

void Semantics_CloseSemantics
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

void BEGIN_Semantics()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_Idents();
    BEGIN_Sets();
    BEGIN_Tree();
    BEGIN_System();
    BEGIN_IO();
    BEGIN_Tree();
    BEGIN_General();
    BEGIN_IO();
    BEGIN_DynArray();
    BEGIN_Strings();
    BEGIN_Idents();
    BEGIN_Texts();
    BEGIN_Scanner();
    BEGIN_Positions();
    BEGIN_Sets();
    BEGIN_Tree();

    Semantics_yyf = IO_StdOutput;
    Semantics_Exit = yyExit;
    Semantics_BeginSemantics();
  }
}
