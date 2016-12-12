# include "StringBuf.h"
# include "DynArray.h"

# define InitialMemorySize	1024 * 16

static	char *	MemoryPtr;
static	unsigned long	MemorySize;
static	long	MemorySpaceLeft;
static	long	MemoryFreePtr;

void BufString (string)
   tString	string;
   {
      register	tString	stringReg1;
      register	tString	stringReg2	= string;
      register	cardinal lengthReg	= 0;
      register	long	NeededSpace;

      while (string[lengthReg++]);
      NeededSpace = lengthReg;
      while (MemorySpaceLeft < NeededSpace) {
	 long	OldMemorySize = MemorySize;

	 ExtendArray ((char * *) & MemoryPtr, & MemorySize, sizeof (char));
	 MemorySpaceLeft += MemorySize - OldMemorySize;
      };
      stringReg1 = & MemoryPtr [MemoryFreePtr];
      while (lengthReg -- > 0) {
	 * stringReg1 ++ = * stringReg2 ++;
      };
      MemorySpaceLeft -= NeededSpace;
      MemoryFreePtr   += NeededSpace;
   };


void WriteStringBuffer ()
   {
      long	StringPtr = 0;

      while (StringPtr < MemoryFreePtr) {
	 (void) printf ("%s", &MemoryPtr[StringPtr]);
	 while (MemoryPtr[StringPtr++]);
      };
   };

void InitStringBuffer ()
   {
      MemorySize	= InitialMemorySize;
      MakeArray ((char * *) & MemoryPtr, & MemorySize, sizeof (char));
      MemorySpaceLeft	= MemorySize;
      MemoryFreePtr 	= 0;
   };
