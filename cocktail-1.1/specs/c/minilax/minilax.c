#include <stdio.h>
# ifdef __cplusplus
extern "C" {
# include "Memory.h"
# include "Errors.h"
}
# else
# include "Memory.h"
# include "Errors.h"
# endif
#include "Parser.h"
#include "Tree.h"
#include "Semantics.h"
#include "Types.h"
#include "Definitions.h"
#include "ICode.h"
#include "ICodeInter.h"

main()
{
   int ErrorCount;

   StoreMessages (true);
   ErrorCount = Parser ();

   (void) fprintf (stderr, "Memory%8d", MemoryUsed);
   (void) fprintf (stderr, "  Tree%8d", Tree_HeapUsed);
   (void) fprintf (stderr, "  Defs%8d\n", Definitions_HeapUsed);

   BeginTypes ();
   BeginDefinitions ();
   BeginSemantics ();
   Semantics (TreeRoot);

   (void) fprintf (stderr, "Memory%8d", MemoryUsed);
   (void) fprintf (stderr, "  Tree%8d", Tree_HeapUsed);
   (void) fprintf (stderr, "  Defs%8d\n", Definitions_HeapUsed);

   if (ErrorCount == 0) {
      Code (TreeRoot);
/*    WriteCode (); */
      Interpret ();
   }
   WriteMessages (stderr);
   return 0;
}
