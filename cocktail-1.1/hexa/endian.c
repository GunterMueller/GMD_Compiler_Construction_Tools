main ()
{
   union { int i; char a [4] } u;

   u.i = 0x0815;
   if (u.a [0] == 21 && u.a [1] == 8 && u.a [2] == 0 && u.a [3] == 0)
      (void) printf ("this machine is little-endian\n");
   else if (u.a [0] == 0 && u.a [1] == 0 && u.a [2] == 8 && u.a [3] == 21)
      (void) printf ("this machine is big-endian\n");
   else
      (void) printf ("cannot determine whether this machine is little- or big-endian\n");
   return 0;
}
