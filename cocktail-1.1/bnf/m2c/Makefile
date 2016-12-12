BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
OPT	= -O
CC	= cc

                # C library (reuse)
REUSE	= ../../reuse/m2c

                # C library (front)
FRONT	= ../../front/m2c

                # C libraries
CLIBS	= $(FRONT)/libfront.a $(REUSE)/libreuse.a

                # options for C compiler
CFLAGS	= -I$(FRONT) -I$(REUSE) $(OPT)

M2FLAGS	= -c

all	: bnf

install:	bnf bnf.sh $(LIB)/lalr
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	install -c $(LIB)/lalr bnf
	sed "s;LIB;$(LIB);" < bnf.sh > $(BIN)/bnf
	chmod a+rx $(BIN)/bnf

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"


# HEAD

sources	: ArgCheck.h

sources	: ArgCheck.c
ArgCheck.o	: ArgCheck.c ArgCheck.h

sources	: MakeBNF.h

sources	: MakeBNF.c
MakeBNF.o	: MakeBNF.c MakeBNF.h
MakeBNF.o	: ArgCheck.h

sources	: bnf.c
all	: bnf
bnf.o	: bnf.c
bnf.o	: ArgCheck.h
bnf.o	: MakeBNF.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

bnf	: $(SYSTEM)	\
	bnf.o	\
	MakeBNF.o	\
	ArgCheck.o	\
;	$(CC) $(CFLAGS) -o bnf $(SYSTEM)	\
	bnf.o	\
	MakeBNF.o	\
	ArgCheck.o	\
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
