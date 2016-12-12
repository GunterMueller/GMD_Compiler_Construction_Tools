#include "SYSTEM_.h"

#ifndef DEFINITION_ArgCheck
#include "ArgCheck.h"
#endif

#ifndef DEFINITION_Automaton
#include "Automaton.h"
#endif

#ifndef DEFINITION_Check
#include "Check.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Gen
#include "Gen.h"
#endif

#ifndef DEFINITION_Infos
#include "Infos.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_Lookahead
#include "Lookahead.h"
#endif

#ifndef DEFINITION_LR
#include "LR.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Reduce
#include "Reduce.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
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

#ifndef DEFINITION_System
#include "System.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

static CHAR ErrorTab [] = "ErrorTab";
static INTEGER errors;
static INTEGER Status;
static BOOLEAN GoOn;


void BEGIN_MODULE()
{
  BEGIN_ArgCheck();
  BEGIN_Automaton();
  BEGIN_Check();
  BEGIN_Errors();
  BEGIN_Gen();
  BEGIN_Infos();
  BEGIN_IO();
  BEGIN_Lookahead();
  BEGIN_LR();
  BEGIN_Parser();
  BEGIN_Path();
  BEGIN_Reduce();
  BEGIN_Scanner();
  BEGIN_Strings();
  BEGIN_StringMem();
  BEGIN_Idents();
  BEGIN_System();
  BEGIN_TokenTab();
  BEGIN_WriteTok();

  (void)strncpy((char *)Errors_ErrorTable.A, (char *)ErrorTab, sizeof(Errors_ErrorTable.A));
  Path_InsertPath(Errors_ErrorTable.A, 256L);
  StringMem_InitStringMemory();
  Idents_InitIdents();
  Errors_BeginErrors();
  ArgCheck_ArgCheck();
  GoOn = ArgCheck_Generate;
  if (GoOn) {
    Gen_GenDefaultActions();
    TokenTab_InitTokenTable();
    Scanner_BeginScanner();
    errors = Parser_Parser();
    ArgCheck_GenerateSupport();
    GoOn = Errors_ErrorCount.A[Errors_eError] == 0;
  }
  if (GoOn) {
    Automaton_InitAutomaton();
    GoOn = Automaton_IsBnf;
  }
  if (GoOn) {
    Reduce_TestReduced();
    GoOn = Reduce_Reduced;
  }
  if (GoOn) {
    LR_ComputeLR();
  }
  if (GoOn) {
    Lookahead_ComputeLALR();
    GoOn = Lookahead_NoConflict;
  }
  if (GoOn) {
    Gen_GenCode(ArgCheck_Pars, ArgCheck_Def);
    Status = 0;
  } else {
    Status = 1;
  }
  Errors_CloseErrors();
  if (ArgCheck_TEST && GoOn) {
    Infos_WriteInfo((System_tFile)IO_StdOutput);
  }
  IO_CloseIO();
  Exit(Status);
}
