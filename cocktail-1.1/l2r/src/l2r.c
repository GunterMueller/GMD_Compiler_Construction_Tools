# include <stdio.h>
# include "Scanner.h"
# include "Parser.h"
# include "StringBuf.h"

main ()
{
  InitStringMemory	();
  InitStringBuffer	();
  BeginScanner		();
  (void) Parser		();		/* parse input and copy GLOBAL section */
  CloseParser 		();
  (void) printf		("}\n");	/* close GLOBAL section */
  print_local		();
  print_macrodefs	();
  print_startconds	();
  WriteStringBuffer	();
  return 0;
}
