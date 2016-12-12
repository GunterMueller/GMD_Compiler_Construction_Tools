#include "SYSTEM_.h"

#ifndef DEFINITION_Scanner
#include "Scanner.h"
#endif

#ifndef DEFINITION_IO
#include "IO.h"
#endif

#ifndef DEFINITION_System
#include "System.h"
#endif

static INTEGER Token;


void BEGIN_MODULE()
{
  BEGIN_Scanner();
  BEGIN_IO();
  BEGIN_System();

  Scanner_BeginScanner();
  do {
    Token = Scanner_GetToken();
  } while (!(Token == Scanner_EofToken));
  Scanner_CloseScanner();
  IO_CloseIO();
  Exit(0L);
}
