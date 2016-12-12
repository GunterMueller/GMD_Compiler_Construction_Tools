/* Timer.c */
/* Bertram Vielsack, 07.03.88 */

#include "Timer.h"

long PrevTime = 0;


long CpuTime ()
{
tms  b;

times (&b);
return (b.uTime + b.sTime) * 20;
}


long StepTime ()
{
  long	ActTime;
  long	DeltaTime;

  ActTime = CpuTime ();
  DeltaTime = ActTime - PrevTime;
  PrevTime = ActTime;
  return DeltaTime;
}


void WriteStepTime (Text)
char Text[];
{
  printf ("%s%d\n",Text,StepTime());
}
