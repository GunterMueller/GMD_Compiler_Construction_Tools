# include "Tree.h"
# include "Eval.h"

main ()
{
   tTree t;
   int i;

   do {
      (void) scanf ("%d", & i);
      t = mR (mP1 (), i);
      Eval (t);
      (void) printf ("%d\n", t->R.r);
   } while (t->R.n != 0);
   return 0;
}
