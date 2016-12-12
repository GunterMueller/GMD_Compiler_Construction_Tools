#define DEFINITION_Mod

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

extern IO_tFile Mod_yyf;
extern PROC Mod_Exit;
extern void Mod_DefMod ARGS((Tree_tTree t));
extern void Mod_ImplMod ARGS((Tree_tTree t));
extern void Mod_MacroMod ARGS((Tree_tTree t));
extern void Mod_BeginMod ARGS(());
extern void Mod_CloseMod ARGS(());
extern void BEGIN_Mod();
