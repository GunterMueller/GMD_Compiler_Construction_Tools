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

#ifndef DEFINITION_Types
#include "Types.h"
#endif

#ifndef DEFINITION_Reachable
#include "Reachable.h"
#endif


static Sets_tSet vReachable;


void Reachable_WindThrough
# ifdef __STDC__
(Idents_tIdent start)
# else
(start)
Idents_tIdent start;
# endif
{
  Sets_tSet todo, leafs, done;
  Idents_tIdent id;

  Sets_MakeSet(&vReachable, (LONGCARD)Idents_MaxIdent());
  Sets_MakeSet(&todo, (LONGCARD)Idents_MaxIdent());
  Sets_MakeSet(&leafs, (LONGCARD)Idents_MaxIdent());
  Sets_Include(&todo, (LONGCARD)start);
  do {
    start = Sets_Extract(&todo);
    Sets_Include(&vReachable, (LONGCARD)start);
    if (Types_IsNonterm(start)) {
      Table_Leafs(start, &leafs);
      Sets_Difference(&leafs, vReachable);
      Sets_Union(&todo, leafs);
    }
  } while (!Sets_IsEmpty(todo));
  Sets_ReleaseSet(&todo);
  Sets_ReleaseSet(&leafs);
}

BOOLEAN Reachable_IsReachable
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((LONGCARD)id, &vReachable);
}

void BEGIN_Reachable()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Idents();
    BEGIN_Idents();
    BEGIN_Sets();
    BEGIN_Table();
    BEGIN_Types();

  }
}
