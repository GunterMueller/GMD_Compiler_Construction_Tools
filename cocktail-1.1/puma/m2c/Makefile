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

M2FLAGS	= -c -d$(HOME)/reuse/src


all	: puma

install:	puma puma.sh $(LIB)/puma
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < puma.sh > $(BIN)/puma
	chmod a+rx $(BIN)/puma
	install puma -c $(LIB)/puma puma
	install Scanner.Tab -c $(LIB)/puma Scanner.Tab
	install Parser.Tab -c $(LIB)/puma Parser.Tab
	install TypeTab.c -c $(LIB)/puma TypeTab.c
	install TypeTab.m -c $(LIB)/puma TypeTab.m

# installation directories

$(LIB)/puma:	$(LIB)
	sh -c "if test ! -d $(LIB)/puma; then mkdir $(LIB)/puma; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

# SYSTEM_	= SYSTEM_.o

lint:
	lint $(CFLAGS) *.c


# HEAD

sources	: C.h
C.h	: Tree.h

sources	: C.c
C.o	: C.c C.h
C.o	: Tree.h
C.o	: Semantics.h
C.o	: Optimize.h
C.o	: Tree.h

sources	: Mod.h
Mod.h	: Tree.h

sources	: Mod.c
Mod.o	: Mod.c Mod.h
Mod.o	: Tree.h
Mod.o	: Semantics.h
Mod.o	: Optimize.h
Mod.o	: Tree.h

sources	: Optimize.h
Optimize.h	: Tree.h

sources	: Optimize.c
Optimize.o	: Optimize.c Optimize.h
Optimize.o	: Tree.h
Optimize.o	: Mod.h
Optimize.o	: Tree.h
Optimize.o	: Scanner.h

sources	: Parser.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Scanner.h
Parser.o	: Tree.h

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: Tree.h

sources	: Semantics.h
Semantics.h	: Tree.h
Semantics.h	: Tree.h

sources	: Semantics.c
Semantics.o	: Semantics.c Semantics.h
Semantics.o	: Tree.h
Semantics.o	: Scanner.h
Semantics.o	: Tree.h

sources	: Tree.h

sources	: Tree.c
Tree.o	: Tree.c Tree.h

sources	: Tree2.h
Tree2.h	: Tree.h

sources	: Tree2.c
Tree2.o	: Tree2.c Tree2.h
Tree2.o	: Tree.h

sources	: puma.c
all	: puma
puma.o	: puma.c
puma.o	: Scanner.h
puma.o	: Parser.h
puma.o	: Tree.h
puma.o	: Tree2.h
puma.o	: Semantics.h
puma.o	: Optimize.h
puma.o	: Mod.h
puma.o	: C.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

puma	: $(SYSTEM)	\
	puma.o	\
	C.o	\
	Tree.o	\
	Optimize.o	\
	Scanner.o	\
	Mod.o	\
	Semantics.o	\
	Tree2.o	\
	Parser.o	\
;	$(CC) $(CFLAGS) -o puma $(SYSTEM)	\
	puma.o	\
	C.o	\
	Tree.o	\
	Optimize.o	\
	Scanner.o	\
	Mod.o	\
	Semantics.o	\
	Tree2.o	\
	Parser.o	\
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
