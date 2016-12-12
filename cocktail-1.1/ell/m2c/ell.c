#include "SYSTEM_.h"

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_CodeC
#include "CodeC.h"
#endif

#ifndef DEFINITION_CodeM2
#include "CodeM2.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Info
#include "Info.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_SupC
#include "SupC.h"
#endif

#ifndef DEFINITION_SupM2
#include "SupM2.h"
#endif

static INTEGER Errors;


void BEGIN_MODULE()
{
  BEGIN_System();
  BEGIN_ArgCheck();
  BEGIN_CodeC();
  BEGIN_CodeM2();
  BEGIN_Errors();
  BEGIN_Info();
  BEGIN_IO();
  BEGIN_Parser();
  BEGIN_Path();
  BEGIN_Scanner();
  BEGIN_Tree();
  BEGIN_Semantics();
  BEGIN_SupC();
  BEGIN_SupM2();

  Errors_SaveProc = Info_SaveInfo;
  Errors_WriteProc = Info_WriteInfo;
  Path_InsertPath(Errors_ErrorTable.A, 256L);
  Path_InsertPath(Scanner_ScanTabName.A, 128L);
  Path_InsertPath(Parser_ParsTabName.A, 129L);
  Path_InsertPath(Semantics_SemanticsTabName.A, 128L);
  Path_InsertPath(CodeC_CodeCTabName.A, 128L);
  Path_InsertPath(CodeM2_CodeM2TabName.A, 128L);
  Errors_BeginErrors();
  ArgCheck_CheckArgs();
  if (ArgCheck_DEF || ArgCheck_IMP) {
    Errors = Parser_Parser();
    Parser_CloseParser();
    Semantics_BeginSemantics();
    Semantics_DoSemantics(Tree_TreeRoot);
    Semantics_CloseSemantics();
  }
  if (Errors_InError) {
    Errors_CloseErrors();
    IO_CloseIO();
    Exit(1L);
  }
  switch (ArgCheck_LANGUAGE) {
  case ArgCheck_C:;
    if (ArgCheck_DEF || ArgCheck_IMP) {
      CodeC_BeginCodeC();
      CodeC_DoCodeC(Tree_TreeRoot);
      CodeC_CloseCodeC();
    }
    if (ArgCheck_ERR) {
      SupC_ErrC();
    }
    if (ArgCheck_SCA) {
      SupC_ScaC();
    }
    if (ArgCheck_PAR) {
      SupC_ParC();
    }
    break;
  case ArgCheck_MODULA2:;
    if (ArgCheck_DEF || ArgCheck_IMP) {
      CodeM2_BeginCodeM2();
      CodeM2_DoCodeM2(Tree_TreeRoot);
      CodeM2_CloseCodeM2();
    }
    if (ArgCheck_ERR) {
      SupM2_ErrM2();
    }
    if (ArgCheck_SCA) {
      SupM2_ScaM2();
    }
    if (ArgCheck_PAR) {
      SupM2_ParM2();
    }
    break;
  }
  Errors_CloseErrors();
  IO_CloseIO();
}
