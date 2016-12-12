#include "SYSTEM_.h"

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Table
#include "Table.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Nullable
#include "Nullable.h"
#endif


static Sets_tSet vNullables;
static BOOLEAN YetNullable ARGS((Tree_tTree t));


void Nullable_TestNullable
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_tSet todo, done;
  Idents_tIdent nt;
  BOOLEAN success;

  Sets_MakeSet(&vNullables, (LONGCARD)Idents_MaxIdent());
  Sets_MakeSet(&todo, (LONGCARD)Idents_MaxIdent());
  Types_Nonterminals(&todo);
  nt = Sets_Maximum(&todo);
  success = TRUE;
  for (;;) {
    if (Sets_IsEmpty(todo)) {
      goto EXIT_1;
    }
    if (nt >= Sets_Maximum(&todo)) {
      if (!success) {
        goto EXIT_1;
      } else {
        nt = Sets_Minimum(&todo);
        success = FALSE;
      }
    } else {
      do {
        INC(nt);
      } while (!Sets_IsElement((LONGCARD)nt, &todo));
    }
    if (YetNullable(Table_Expr(nt))) {
      Sets_Include(&vNullables, (LONGCARD)nt);
      Sets_Exclude(&todo, (LONGCARD)nt);
      success = TRUE;
    }
  } EXIT_1:;
  Sets_ReleaseSet(&todo);
}

static BOOLEAN YetNullable
# ifdef __STDC__
(Tree_tTree t)
# else
(t)
Tree_tTree t;
# endif
{
  switch (t->U_1.V_1.Kind) {
  case Tree_Option:;
    return TRUE;
    break;
  case Tree_Times:;
    return TRUE;
    break;
  case Tree_Plus:;
    return YetNullable(t->U_1.V_35.Plus.expr);
    break;
  case Tree_List:;
    return YetNullable(t->U_1.V_36.List.body);
    break;
  case Tree_Action:;
    return TRUE;
    break;
  case Tree_Leaf:;
    return Sets_IsElement((LONGCARD)t->U_1.V_38.Leaf.id->U_1.V_23.Id.ident, &vNullables);
    break;
  case Tree_Alternative0:;
    return FALSE;
    break;
  case Tree_Alternative:;
    return YetNullable(t->U_1.V_41.Alternative.alternative) || YetNullable(t->U_1.V_41.Alternative.expr);
    break;
  case Tree_Sequence0:;
    return TRUE;
    break;
  case Tree_Sequence:;
    return YetNullable(t->U_1.V_44.Sequence.sequence) && YetNullable(t->U_1.V_44.Sequence.expr);
    break;
  }
}

BOOLEAN Nullable_IsNullable
# ifdef __STDC__
(Idents_tIdent Nonterm)
# else
(Nonterm)
Idents_tIdent Nonterm;
# endif
{
  return Sets_IsElement((LONGCARD)Nonterm, &vNullables);
}

void BEGIN_Nullable()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Idents();
    BEGIN_Idents();
    BEGIN_Sets();
    BEGIN_Table();
    BEGIN_Tree();
    BEGIN_Types();

  }
}
