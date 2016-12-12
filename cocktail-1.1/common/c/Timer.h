/* Timer.h */
/* Bertram Vielsack, 07.03.88 */

typedef  struct  TMS
  {
    long  uTime,
          sTime,
          cuTime,
          csTime;
  };

#define tms  struct TMS

long	CpuTime ();
long	StepTime ();
void	WriteTime ();
