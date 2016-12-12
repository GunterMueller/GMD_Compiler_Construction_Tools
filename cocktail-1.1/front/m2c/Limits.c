#include "SYSTEM_.h"

#ifndef DEFINITION_Limits
#include "Limits.h"
#endif




void BEGIN_Limits()
{
  static BOOLEAN has_been_called = FALSE;

  if (!has_been_called) {
    has_been_called = TRUE;


  }
}
