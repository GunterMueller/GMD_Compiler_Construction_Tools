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

all:	r2l

install:	r2l r2l.sh $(LIB)/r2l
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < r2l.sh > $(BIN)/r2l
	chmod a+rx $(BIN)/r2l
	install -c $(LIB)/r2l r2l
	install -c $(LIB)/r2l Scanner.Tab
	install -c $(LIB)/r2l Parser.Tab

# installation directories

$(LIB)/r2l:	$(LIB)
	sh -c "if test ! -d $(LIB)/r2l; then mkdir $(LIB)/r2l; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

# SYSTEM_	= SYSTEM_.o

# HEAD

sources	: DefTable.h

sources	: DefTable.c
DefTable.o	: DefTable.c DefTable.h

sources	: Errors.h

sources	: Errors.c
Errors.o	: Errors.c Errors.h

sources	: Parser.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Errors.h
Parser.o	: Errors.h
Parser.o	: DefTable.h

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: Errors.h

sources	: r2l.c
all	: r2l
r2l.o	: r2l.c
r2l.o	: Scanner.h
r2l.o	: Parser.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

r2l	: $(SYSTEM)	\
	r2l.o	\
	Parser.o	\
	DefTable.o	\
	Errors.o	\
	Scanner.o	\
;	$(CC) $(CFLAGS) -o r2l $(SYSTEM)	\
	r2l.o	\
	Parser.o	\
	DefTable.o	\
	Errors.o	\
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
