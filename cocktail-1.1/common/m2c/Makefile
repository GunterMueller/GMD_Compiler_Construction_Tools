OPT	= -O
CC	= cc

                # C library (reuse)
REUSE	= ../../reuse/m2c

                # C libraries
CLIBS	= $(REUSE)/libreuse.a

                # options for C compiler
CFLAGS	= -I$(REUSE) $(OPT)

M2FLAGS	= -c

OBJS	= Character.o Checks.o Convert.o Errors.o Listing.o Path.o Queues.o \
	  Stack.o SysError.o


libcommon.a	: $(OBJS)
	ar uc libcommon.a $(OBJS)
	ranlib libcommon.a


# HEAD

sources	: Character.h

sources	: Character.c
Character.o	: Character.c Character.h

sources	: Checks.h

sources	: Checks.c
Checks.o	: Checks.c Checks.h
Checks.o	: SysError.h
Checks.o	: Errors.h

sources	: Convert.h

sources	: Convert.c
Convert.o	: Convert.c Convert.h

sources	: Errors.h

sources	: Errors.c
Errors.o	: Errors.c Errors.h
Errors.o	: Listing.h
Errors.o	: SysError.h

sources	: Listing.h

sources	: Listing.c
Listing.o	: Listing.c Listing.h

sources	: Main.c
all	: Main
Main.o	: Main.c
Main.o	: Convert.h
Main.o	: Character.h
Main.o	: Checks.h
Main.o	: Errors.h
Main.o	: Listing.h
Main.o	: Path.h
Main.o	: Queues.h
Main.o	: Stack.h
Main.o	: SysError.h

sources	: Path.h

sources	: Path.c
Path.o	: Path.c Path.h
Path.o	: Character.h

sources	: Queues.h

sources	: Queues.c
Queues.o	: Queues.c Queues.h
Queues.o	: Errors.h

sources	: Stack.h

sources	: Stack.c
Stack.o	: Stack.c Stack.h
Stack.o	: Errors.h

sources	: SysError.h

sources	: SysError.c
SysError.o	: SysError.c SysError.h
SysError.o	: Errors.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

Main	: $(SYSTEM)	\
	Main.o	\
	SysError.o	\
	Errors.o	\
	Listing.o	\
	Stack.o	\
	Queues.o	\
	Path.o	\
	Character.o	\
	Checks.o	\
	Convert.o	\
;	$(CC) $(CFLAGS) -o Main $(SYSTEM)	\
	Main.o	\
	SysError.o	\
	Errors.o	\
	Listing.o	\
	Stack.o	\
	Queues.o	\
	Path.o	\
	Character.o	\
	Checks.o	\
	Convert.o	\
	$(CLIBS)

# TAIL

clean	:
	rm -f core *.o

CLEAN	: clean
	rm -f libcommon.a

.SUFFIXES: .md .mi .h .c .o

.mi.c:
	mtc $(M2FLAGS) $*.mi;

.md.h:
	mtc $(M2FLAGS) $*.md;

.c.o:
	$(CC) $(CFLAGS) -c $*.c
