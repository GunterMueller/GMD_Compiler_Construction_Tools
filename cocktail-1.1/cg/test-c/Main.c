# include "Tree.h"
# include <stdio.h>
# include "Memory.h"
# include "StringMem.h"
# include "Idents.h"

void ErrorCheck (s, n)
   char * s;
   int n;
{  if (n < 0) (void) printf ("Error: %s, Code: %d\n", s, n); }

void PrintMark (t)
   tTree t;
{  (void) printf ("%d ", t->Node.Mark); }

main ()
{
   tTree n, n1, n2, n3, n4, n5, Root1, Root2, Root3;
   FILE * f;
   int i;

   InitMemory		();
   InitStringMemory	();
   InitIdents		();
   BeginTree		();

   n1 = nNode2 ();
   n2 = nNode2 ();
   n3 = nNode1 ();
   n4 = nNode1 ();
   n5 = nNode1 ();

   n1->Node.Mark = 1;
   n2->Node.Mark = 2;
   n3->Node.Mark = 3;
   n4->Node.Mark = 4;
   n5->Node.Mark = 5;

   n1->Node.Ident = MakeIdent ((tString ) "1", 1);
   n2->Node.Ident = MakeIdent ((tString ) "2", 1);
   n3->Node.Ident = MakeIdent ((tString ) "3", 1);
   n4->Node.Ident = MakeIdent ((tString ) "4", 1);
   n5->Node.Ident = MakeIdent ((tString ) "5", 1);

   n1->Node.Hex = 1;
   n2->Node.Hex = 2;
   n3->Node.Hex = 3;
   n4->Node.Hex = 4;
   n5->Node.Hex = 5;

   n = n1;
   n1->Node2.Child1 = n2;
   n1->Node2.Child2 = n2;
   n2->Node2.Child1 = n3;
   n2->Node2.Child2 = n5;
   n3->Node1.Child1 = n4;
   n4->Node1.Child1 = n3;
   n5->Node1.Child1 = n5;

   f = fopen		("a", "w");
   ErrorCheck		("fopen (a, w)", (int) f);
   (void) printf	("fopen (a, w)\n");
   WriteTree		(f, n);
   (void) fclose	(f);

   f = fopen		("a", "r");
   ErrorCheck		("fopen (a, r)", (int) f);
   (void) printf	("fopen (a, r)\n");
   Root1 = ReadTree	(f);
   (void) fclose	(f);

   f = fopen		("b", "w");
   ErrorCheck		("fopen (b, w)", (int) f);
   (void) printf	("fopen (b, w)\n");
   PutTree		(f, Root1);
   (void) fclose	(f);

   f = fopen		("b", "r");
   ErrorCheck		("fopen (b, r)", (int) f);
   (void) printf	("fopen (b, r)\n");
   Root2 = GetTree	(f);
   (void) fclose	(f);

   f = fopen		("aa", "w");
   ErrorCheck		("fopen (aa, w)", (int) f);
   (void) printf	("fopen (aa, w)\n");
   WriteTree		(f, Root2);
   (void) fclose	(f);

   f = fopen		("bb", "w");
   ErrorCheck		("fopen (bb, w)", (int) f);
   (void) printf	("fopen (bb, w)\n");
   PutTree		(f, Root2);
   (void) fclose	(f);

   Root3 = CopyTree	(Root2);
   f = fopen		("aaa", "w");
   ErrorCheck		("fopen (aaa, w)", (int) f);
   (void) printf	("fopen (aaa, w)\n");
   WriteTree		(f, Root3);
   (void) fclose	(f);

   i = system		("set -x; cmp a aa; cmp b bb; cmp a aaa");
   ErrorCheck		("system", i);

   (void) printf	("should print:\n1 2 3 4 5 4 3 5 2 1 \n");
   TraverseTreeTD	(Root2, PrintMark);
   TraverseTreeBU	(Root2, PrintMark);
   (void) printf	("\n");

   (void) CheckTree	(Root3);

   (void) printf	("should print:\n4 3 5 2 1 \n");
   ReleaseTree		(Root3);
   (void) printf	("\n");
   ReleaseTreeModule	();
   CloseTree		();

   return 0;
}
