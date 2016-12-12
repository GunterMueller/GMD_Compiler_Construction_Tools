#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
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

#ifndef DEFINITION_Match
#include "Match.h"
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

#ifndef DEFINITION_Semantics
#include "Semantics.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_Test
#include "Test.h"
#endif

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Grammar
#include "Grammar.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Test
#include "Test.h"
#endif

#ifndef DEFINITION_Tree
#include "Tree.h"
#endif

static INTEGER errors;


void BEGIN_MODULE()
{
  BEGIN_ArgCheck();
  BEGIN_CodeM2();
  BEGIN_Errors();
  BEGIN_Info();
  BEGIN_IO();
  BEGIN_Match();
  BEGIN_Parser();
  BEGIN_Path();
  BEGIN_Scanner();
  BEGIN_Semantics();
  BEGIN_System();
  BEGIN_Test();
  BEGIN_ArgCheck();
  BEGIN_Grammar();
  BEGIN_Parser();
  BEGIN_Test();
  BEGIN_Tree();

  Errors_SaveProc = Info_SaveInfo;
  Errors_WriteProc = Info_WriteInfo;
  Path_InsertPath(Errors_ErrorTable.A, 256L);
  Path_InsertPath(Parser_ParsTabName.A, 129L);
  Path_InsertPath(Scanner_ScanTabName.A, 128L);
  Errors_BeginErrors();
  ArgCheck_CheckArgs();
  Test_WriteStepTime((STRING)"initialize", 10L);
  errors = Parser_Parser();
  Parser_CloseParser();
  Test_WriteStepTime((STRING)"Parser", 6L);
  Semantics_Semantic();
  Test_WriteStepTime((STRING)"Semantics", 9L);
  if (Semantics_Correct) {
    Match_MakeTables();
    Test_WriteStepTime((STRING)"MakeTables", 10L);
    CodeM2_MakeCodeM2();
    Test_WriteStepTime((STRING)"MakeCodeM2", 10L);
  }
  Errors_CloseErrors();
  if (ArgCheck_TREE) {
    Tree_WriteTree((System_tFile)IO_StdOutput, Parser_AST);
  }
  if (ArgCheck_GRAM) {
    Grammar_WriteGrammar((System_tFile)IO_StdOutput);
  }
  if (ArgCheck_TEST) {
    Test_WriteTest();
  }
  IO_CloseIO();
  if (Errors_InError) {
    Exit(1L);
  } else {
    Exit(0L);
  }
}
