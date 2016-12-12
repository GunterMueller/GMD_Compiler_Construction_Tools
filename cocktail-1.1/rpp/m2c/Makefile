BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
OPT	= -O
CC	= cc

                # C library (reuse)
REUSE	= ../../reuse/m2c

                # C libraries
CLIBS	= $(REUSE)/libreuse.a

                # options for C compiler
CFLAGS	= -w -I$(REUSE) $(OPT)

M2FLAGS	= -c

all:	rpp

install:	rpp rpp.sh $(LIB)/rpp
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < rpp.sh > $(BIN)/rpp
	chmod a+rx $(BIN)/rpp
	install -c $(LIB)/rpp rpp
	install -c $(LIB)/rpp Scanner.Tab

#	installation directories

$(LIB)/rpp:	$(LIB)
	sh -c "if test ! -d $(LIB)/rpp; then mkdir $(LIB)/rpp; else true; fi"

# swap all byte pairs of the file Scanner.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab


# HEAD

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h

sources	: rpp.c
all	: rpp
rpp.o	: rpp.c
rpp.o	: Scanner.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

rpp	: $(SYSTEM)	\
	rpp.o	\
	Scanner.o	\
;	$(CC) $(CFLAGS) -o rpp $(SYSTEM)	\
	rpp.o	\
	Scanner.o	\
	$(CLIBS)

# TAIL

clean	:
	rm -f core *.o

.SUFFIXES: .md .mi .h .c .o

.mi.c:
	mtc $(M2FLAGS) $*.mi;

.md.h:
	mtc $(M2FLAGS) $*.md;

.c.o:
	$(CC) $(CFLAGS) -c $*.c
