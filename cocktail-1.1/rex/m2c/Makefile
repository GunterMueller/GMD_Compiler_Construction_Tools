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

all	: rex

install:	rex rex.sh $(LIB)/rex
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);g" < rex.sh > $(BIN)/rex
	chmod a+rx $(BIN)/rex
	install -c $(LIB)/rex rex
	install -c $(LIB)/rex Scanner.Tab
	install -c $(LIB)/rex Parser.Tab
	cp ../lib/S* $(LIB)/rex
	chmod a+r $(LIB)/rex/S*

# installation directories

$(LIB)/rex:	$(LIB)
	sh -c "if test ! -d $(LIB)/rex; then mkdir $(LIB)/rex; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab


# HEAD

sources	: Classes.h

sources	: Classes.c
Classes.o	: Classes.c Classes.h
Classes.o	: Tree0.h
Classes.o	: Dfa.h

sources	: DefTable.h
DefTable.h	: Tree.h

sources	: DefTable.c
DefTable.o	: DefTable.c DefTable.h
DefTable.o	: Tree.h

sources	: Dfa.h

sources	: Dfa.c
Dfa.o	: Dfa.c Dfa.h
Dfa.o	: GenTabs.h
Dfa.o	: Classes.h

sources	: Errors.h

sources	: Errors.c
Errors.o	: Errors.c Errors.h

sources	: Eval.h
Eval.h	: Tree0.h

sources	: Eval.c
Eval.o	: Eval.c Eval.h
Eval.o	: Tree0.h
Eval.o	: Classes.h
Eval.o	: Dfa.h
Eval.o	: Tree.h

sources	: GenTabs.h
GenTabs.h	: Tree.h

sources	: GenTabs.c
GenTabs.o	: GenTabs.c GenTabs.h
GenTabs.o	: DefTable.h
GenTabs.o	: Tree.h
GenTabs.o	: Nfa.h
GenTabs.o	: Dfa.h
GenTabs.o	: Traces.h
GenTabs.o	: ScanTabs.h
GenTabs.o	: ScanGen.h
GenTabs.o	: Classes.h

sources	: Nfa.h
Nfa.h	: ScanTabs.h

sources	: Nfa.c
Nfa.o	: Nfa.c Nfa.h
Nfa.o	: ScanTabs.h
Nfa.o	: GenTabs.h

sources	: Parser.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Errors.h
Parser.o	: Errors.h
Parser.o	: Tree0.h
Parser.o	: Tree.h
Parser.o	: DefTable.h
Parser.o	: GenTabs.h
Parser.o	: Dfa.h
Parser.o	: ScanGen.h

sources	: ScanGen.h

sources	: ScanGen.c
ScanGen.o	: ScanGen.c ScanGen.h
ScanGen.o	: Errors.h
ScanGen.o	: DefTable.h
ScanGen.o	: Dfa.h
ScanGen.o	: ScanTabs.h
ScanGen.o	: GenTabs.h

sources	: ScanTabs.h

sources	: ScanTabs.c
ScanTabs.o	: ScanTabs.c ScanTabs.h
ScanTabs.o	: Dfa.h
ScanTabs.o	: GenTabs.h
ScanTabs.o	: Classes.h
ScanTabs.o	: ScanGen.h

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: Errors.h
Scanner.o	: ScanGen.h

sources	: Traces.h
Traces.h	: Dfa.h

sources	: Traces.c
Traces.o	: Traces.c Traces.h
Traces.o	: Dfa.h
Traces.o	: GenTabs.h

sources	: Tree.h

sources	: Tree.c
Tree.o	: Tree.c Tree.h

sources	: Tree0.h
Tree0.h	: Tree.h

sources	: Tree0.c
Tree0.o	: Tree0.c Tree0.h

sources	: rex.c
all	: rex
rex.o	: rex.c
rex.o	: Scanner.h
rex.o	: Parser.h
rex.o	: Classes.h
rex.o	: Eval.h
rex.o	: Tree.h
rex.o	: Tree0.h
rex.o	: Dfa.h
rex.o	: GenTabs.h
rex.o	: ScanGen.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

rex	: $(SYSTEM)	\
	rex.o	\
	ScanGen.o	\
	GenTabs.o	\
	Classes.o	\
	Dfa.o	\
	Tree0.o	\
	Tree.o	\
	ScanTabs.o	\
	Traces.o	\
	Nfa.o	\
	DefTable.o	\
	Errors.o	\
	Eval.o	\
	Parser.o	\
	Scanner.o	\
;	$(CC) $(CFLAGS) -o rex $(SYSTEM)	\
	rex.o	\
	ScanGen.o	\
	GenTabs.o	\
	Classes.o	\
	Dfa.o	\
	Tree0.o	\
	Tree.o	\
	ScanTabs.o	\
	Traces.o	\
	Nfa.o	\
	DefTable.o	\
	Errors.o	\
	Eval.o	\
	Parser.o	\
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
