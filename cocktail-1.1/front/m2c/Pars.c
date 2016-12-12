#include "SYSTEM_.h"

#ifndef DEFINITION_WriteTok
#include "WriteTok.h"
#endif

#ifndef DEFINITION_Character
#include "Character.h"
#endif

#ifndef DEFINITION_Path
#include "Path.h"
#endif

#ifndef DEFINITION_Checks
#include "Checks.h"
#endif

#ifndef DEFINITION_Errors
#include "Errors.h"
#endif

#ifndef DEFINITION_Parser
#include "Parser.h"
#endif

#ifndef DEFINITION_Idents
#include "Idents.h"
#endif

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_StringMem
#include "StringMem.h"
#endif

#ifndef DEFINITION_TokenTab
#include "TokenTab.h"
#endif

static CARDINAL errors;


void BEGIN_MODULE()
{
  BEGIN_WriteTok();
  BEGIN_Character();
  BEGIN_Path();
  BEGIN_Checks();
  BEGIN_Errors();
  BEGIN_Parser();
  BEGIN_Idents();
  BEGIN_Scanner();
  BEGIN_StringMem();
  BEGIN_TokenTab();

  StringMem_InitStringMemory();
  Idents_InitIdents();
  Errors_BeginErrors();
  Scanner_BeginScanner();
  TokenTab_InitTokenTable();
  errors = Parser_Parser();
  Errors_CloseErrors();
}
