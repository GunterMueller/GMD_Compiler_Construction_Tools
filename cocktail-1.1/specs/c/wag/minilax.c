# include <stdio.h>
# ifdef __cplusplus
extern "C" {
# include "Memory.h"
# include "Errors.h"
}
# else
# include "Memory.h"
# include "Errors.h"
# endif
# include "Parser.h"
# include "Tree.h"
# include "Semantics.h"
# include "Types.h"
# include "ICode.h"
# include "ICodeInter.h"

main()
{
   int ErrorCount;

   StoreMessages (true);
   ErrorCount = Parser ();

   (void) fprintf (stderr, "Memory%8d", MemoryUsed);
   (void) fprintf (stderr, "  Tree%8d\n", Tree_HeapUsed);

   BeginTypes ();
   BeginSemantics ();
   Semantics (TreeRoot);

   (void) fprintf (stderr, "Memory%8d", MemoryUsed);
   (void) fprintf (stderr, "  Tree%8d\n", Tree_HeapUsed);

   if (ErrorCount == 0) {
      Code (TreeRoot);
      ResolveLabels ();
/*    WriteCode (); */
      Interpret ();
   }
   WriteMessages (stderr);
   return 0;
}
