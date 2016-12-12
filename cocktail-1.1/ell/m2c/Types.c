#include "SYSTEM_.h"

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif


static Sets_tSet vDefined, vTerms, vNonterms;


void Types_BeginTypes
# ifdef __STDC__
()
# else
()
# endif
{
  Sets_MakeSet(&vDefined, (LONGCARD)Idents_MaxIdent());
  Sets_MakeSet(&vTerms, (LONGCARD)Idents_MaxIdent());
  Sets_MakeSet(&vNonterms, (LONGCARD)Idents_MaxIdent());
}

void Types_MakeTerm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  Sets_Include(&vDefined, (LONGCARD)id);
  Sets_Include(&vTerms, (LONGCARD)id);
}

void Types_MakeNonterm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  Sets_Include(&vDefined, (LONGCARD)id);
  Sets_Include(&vNonterms, (LONGCARD)id);
}

BOOLEAN Types_IsDeclared
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((LONGCARD)id, &vDefined);
}

BOOLEAN Types_IsTerm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((LONGCARD)id, &vTerms);
}

BOOLEAN Types_IsNonterm
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return Sets_IsElement((LONGCARD)id, &vNonterms);
}

void Types_Terminals
# ifdef __STDC__
(Sets_tSet *set)
# else
(set)
Sets_tSet *set;
# endif
{
  Sets_Assign(set, vTerms);
}

void Types_Nonterminals
# ifdef __STDC__
(Sets_tSet *set)
# else
(set)
Sets_tSet *set;
# endif
{
  Sets_Assign(set, vNonterms);
}

void BEGIN_Types()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Idents();
    BEGIN_Sets();
    BEGIN_Idents();
    BEGIN_Sets();

  }
}
