#include "SYSTEM_.h"

#ifndef DEFINITION_DynArray
#include "DynArray.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Sets
#include "Sets.h"
#endif

#ifndef DEFINITION_Types
#include "Types.h"
#endif


#define NoCode	-1
static struct S_1 {
    Types_tType A[10000 + 1];
} *TypeArray;
static struct S_2 {
    INTEGER A[10000 + 1];
} *CodeArray;
static INTEGER vMaxClassCode;
static Sets_tSet allNodes;
static Sets_tSet allClasses;
static Sets_tSet EssentialClasses;


void Types_MakeTransformation
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  if (name == Scanner_NoIdent) {
    return;
  }
  TypeArray->A[name] = Types_cTransformation;
}

void Types_MakeFunction
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  if (name == Scanner_NoIdent) {
    return;
  }
  TypeArray->A[name] = Types_cFunction;
}

void Types_MakeClass
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  if (name == Scanner_NoIdent) {
    return;
  }
  TypeArray->A[name] = Types_cClass;
  INC(vMaxClassCode);
  CodeArray->A[name] = vMaxClassCode;
  Sets_Include(&allClasses, (LONGCARD)name);
}

void Types_MakeNode
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  if (name == Scanner_NoIdent) {
    return;
  }
  TypeArray->A[name] = Types_cNode;
  Sets_Include(&allNodes, (LONGCARD)name);
}

void Types_MakeNodeId
# ifdef __STDC__
(Idents_tIdent ident)
# else
(ident)
Idents_tIdent ident;
# endif
{
  if (ident == Scanner_NoIdent) {
    return;
  }
  TypeArray->A[ident] = Types_cNodeId;
}

Types_tType Types_Type
# ifdef __STDC__
(Idents_tIdent id)
# else
(id)
Idents_tIdent id;
# endif
{
  return TypeArray->A[id];
}

void Types_BeginTypes
# ifdef __STDC__
()
# else
()
# endif
{
  LONGINT size;
  Idents_tIdent id;

  size = Scanner_MaxIdent + 1;
  DynArray_MakeArray((ADDRESS *)&TypeArray, &size, (LONGINT)sizeof(Types_tType));
  DynArray_MakeArray((ADDRESS *)&CodeArray, &size, (LONGINT)sizeof(INTEGER));
  {
    SHORTCARD B_1 = 0, B_2 = Scanner_MaxIdent;

    if (B_1 <= B_2)
      for (id = B_1;; id += 1) {
        TypeArray->A[id] = Types_cNoType;
        CodeArray->A[id] = NoCode;
        if (id >= B_2) break;
      }
  }
  Sets_MakeSet(&allNodes, (LONGCARD)Scanner_MaxIdent);
  Sets_MakeSet(&allClasses, (LONGCARD)Scanner_MaxIdent);
  Sets_MakeSet(&EssentialClasses, (LONGCARD)Scanner_MaxIdent);
}

void Types_AllNodes
# ifdef __STDC__
(Sets_tSet *nodes)
# else
(nodes)
Sets_tSet *nodes;
# endif
{
  Sets_Assign(nodes, allNodes);
}

void Types_AllClasses
# ifdef __STDC__
(Sets_tSet *classes)
# else
(classes)
Sets_tSet *classes;
# endif
{
  Sets_Assign(classes, allClasses);
}

void Types_SetEssential
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  Sets_Include(&EssentialClasses, (LONGCARD)name);
}

void Types_UnionEssential
# ifdef __STDC__
(Sets_tSet set)
# else
(set)
Sets_tSet set;
# endif
{
  Sets_Union(&EssentialClasses, set);
}

BOOLEAN Types_Essential
# ifdef __STDC__
(Idents_tIdent name)
# else
(name)
Idents_tIdent name;
# endif
{
  return Sets_IsElement((LONGCARD)name, &EssentialClasses);
}

INTEGER Types_ClassCode
# ifdef __STDC__
(Idents_tIdent class)
# else
(class)
Idents_tIdent class;
# endif
{
  return CodeArray->A[class];
}

INTEGER Types_MaxClassCode
# ifdef __STDC__
()
# else
()
# endif
{
  return vMaxClassCode;
}

void BEGIN_Types()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;

    BEGIN_Idents();
    BEGIN_Sets();
    BEGIN_DynArray();
    BEGIN_Idents();
    BEGIN_Scanner();
    BEGIN_Sets();

    vMaxClassCode = -1;
  }
}
