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

M2FLAGS	= -c -d../../reuse/src


all	: cg

install:	cg cg.sh $(LIB)/cg
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);g" < cg.sh > $(BIN)/cg
	cp $(BIN)/cg $(BIN)/ag
	cp $(BIN)/cg $(BIN)/ast
	chmod a+rx $(BIN)/cg $(BIN)/ast $(BIN)/ag
	install gmdcpp -c $(BIN) gmdcpp
	install -c $(BIN) gmdupd
	install -c $(BIN) gmdrm
	install -c $(LIB)/cg cg
	install -c $(LIB)/cg Scanner.Tab
	install -c $(LIB)/cg Parser.Tab
	install -c $(LIB)/cg Typetab
	install TypeTab.m -c $(LIB)/cg

# installation directories

$(LIB)/cg:	$(LIB)
	sh -c "if test ! -d $(LIB)/cg; then mkdir $(LIB)/cg; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

# SYSTEM_	= SYSTEM_.o

lint:
	lint $(CFLAGS) *.c


# HEAD

sources	: Dialog.h
Dialog.h	: Tree.h

sources	: Dialog.c
Dialog.o	: Dialog.c Dialog.h
Dialog.o	: Tree.h
Dialog.o	: Order.h
Dialog.o	: Tree.h

sources	: Errors.h
Errors.h	: Positions.h

sources	: Errors.c
Errors.o	: Errors.c Errors.h
Errors.o	: Positions.h

sources	: EvalC.h
EvalC.h	: Tree.h

sources	: EvalC.c
EvalC.o	: EvalC.c EvalC.h
EvalC.o	: Tree.h
EvalC.o	: TreeC1.h
EvalC.o	: TreeC2.h
EvalC.o	: EvalC3.h
EvalC.o	: Tree.h

sources	: EvalC2.h
EvalC2.h	: Tree.h

sources	: EvalC2.c
EvalC2.o	: EvalC2.c EvalC2.h
EvalC2.o	: Tree.h
EvalC2.o	: TreeC2.h
EvalC2.o	: EvalC.h
EvalC2.o	: Tree.h

sources	: EvalC3.h
EvalC3.h	: Tree.h

sources	: EvalC3.c
EvalC3.o	: EvalC3.c EvalC3.h
EvalC3.o	: Tree.h
EvalC3.o	: TreeC1.h
EvalC3.o	: TreeC2.h
EvalC3.o	: EvalC.h
EvalC3.o	: EvalC.h
EvalC3.o	: Tree.h

sources	: EvalMod.h
EvalMod.h	: Tree.h

sources	: EvalMod.c
EvalMod.o	: EvalMod.c EvalMod.h
EvalMod.o	: Tree.h
EvalMod.o	: TreeMod1.h
EvalMod.o	: TreeMod2.h
EvalMod.o	: EvalMod3.h
EvalMod.o	: Tree.h

sources	: EvalMod2.h
EvalMod2.h	: Tree.h

sources	: EvalMod2.c
EvalMod2.o	: EvalMod2.c EvalMod2.h
EvalMod2.o	: Tree.h
EvalMod2.o	: TreeMod2.h
EvalMod2.o	: EvalMod.h
EvalMod2.o	: Tree.h

sources	: EvalMod3.h
EvalMod3.h	: Tree.h

sources	: EvalMod3.c
EvalMod3.o	: EvalMod3.c EvalMod3.h
EvalMod3.o	: Tree.h
EvalMod3.o	: TreeMod1.h
EvalMod3.o	: TreeMod2.h
EvalMod3.o	: EvalMod.h
EvalMod3.o	: EvalMod.h
EvalMod3.o	: Tree.h

sources	: GramC.h
GramC.h	: Tree.h

sources	: GramC.c
GramC.o	: GramC.c GramC.h
GramC.o	: Tree.h
GramC.o	: TreeC2.h
GramC.o	: Tree.h

sources	: GramMod.h
GramMod.h	: Tree.h

sources	: GramMod.c
GramMod.o	: GramMod.c GramMod.h
GramMod.o	: Tree.h
GramMod.o	: TreeMod2.h
GramMod.o	: Tree.h

sources	: GramYacc.h
GramYacc.h	: Tree.h

sources	: GramYacc.c
GramYacc.o	: GramYacc.c GramYacc.h
GramYacc.o	: Tree.h
GramYacc.o	: TreeC2.h
GramYacc.o	: Tree.h

sources	: Optimize.h
Optimize.h	: Tree.h

sources	: Optimize.c
Optimize.o	: Optimize.c Optimize.h
Optimize.o	: Tree.h
Optimize.o	: Tree.h
Optimize.o	: Order.h

sources	: Order.h
Order.h	: Tree.h

sources	: Order.c
Order.o	: Order.c Order.h
Order.o	: Tree.h
Order.o	: Queue.h
Order.o	: Tree.h
Order.o	: Optimize.h
Order.o	: Queue.h
Order.o	: Errors.h

sources	: Parser.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Positions.h
Parser.o	: Errors.h
Parser.o	: Scanner.h
Parser.o	: Positions.h
Parser.o	: Tree.h

sources	: Positions.h

sources	: Positions.c
Positions.o	: Positions.c Positions.h

sources	: Queue.h

sources	: Queue.c
Queue.o	: Queue.c Queue.h

sources	: Scanner.h
Scanner.h	: Positions.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: Tree.h
Scanner.o	: Positions.h
Scanner.o	: Errors.h

sources	: Semantics.h
Semantics.h	: Tree.h

sources	: Semantics.c
Semantics.o	: Semantics.c Semantics.h
Semantics.o	: Tree.h
Semantics.o	: Positions.h
Semantics.o	: Tree.h
Semantics.o	: Errors.h

sources	: Tree.h
Tree.h	: Positions.h

sources	: Tree.c
Tree.o	: Tree.c Tree.h
Tree.o	: Positions.h
Tree.o	: Positions.h
Tree.o	: Errors.h

sources	: Tree2.h
Tree2.h	: Tree.h

sources	: Tree2.c
Tree2.o	: Tree2.c Tree2.h
Tree2.o	: Positions.h
Tree2.o	: Tree.h

sources	: TreeC1.h
TreeC1.h	: Tree.h

sources	: TreeC1.c
TreeC1.o	: TreeC1.c TreeC1.h
TreeC1.o	: Tree.h
TreeC1.o	: TreeC2.h
TreeC1.o	: Tree.h

sources	: TreeC2.h
TreeC2.h	: Tree.h

sources	: TreeC2.c
TreeC2.o	: TreeC2.c TreeC2.h
TreeC2.o	: Tree.h
TreeC2.o	: Tree.h

sources	: TreeMod1.h
TreeMod1.h	: Tree.h

sources	: TreeMod1.c
TreeMod1.o	: TreeMod1.c TreeMod1.h
TreeMod1.o	: Tree.h
TreeMod1.o	: TreeMod2.h
TreeMod1.o	: Tree.h

sources	: TreeMod2.h
TreeMod2.h	: Tree.h

sources	: TreeMod2.c
TreeMod2.o	: TreeMod2.c TreeMod2.h
TreeMod2.o	: Tree.h
TreeMod2.o	: Tree.h

sources	: cg.c
all	: cg
cg.o	: cg.c
cg.o	: Errors.h
cg.o	: Scanner.h
cg.o	: Parser.h
cg.o	: Tree.h
cg.o	: Tree2.h
cg.o	: Semantics.h
cg.o	: Order.h
cg.o	: Dialog.h
cg.o	: GramMod.h
cg.o	: TreeMod1.h
cg.o	: EvalMod.h
cg.o	: EvalMod2.h
cg.o	: EvalMod3.h
cg.o	: GramC.h
cg.o	: GramYacc.h
cg.o	: TreeC1.h
cg.o	: EvalC.h
cg.o	: EvalC2.h
cg.o	: EvalC3.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

cg	: $(SYSTEM)	\
	cg.o	\
	EvalC3.o	\
	Tree.o	\
	Errors.o	\
	Positions.o	\
	EvalC.o	\
	TreeC2.o	\
	TreeC1.o	\
	EvalC2.o	\
	GramYacc.o	\
	GramC.o	\
	EvalMod3.o	\
	EvalMod.o	\
	TreeMod2.o	\
	TreeMod1.o	\
	EvalMod2.o	\
	GramMod.o	\
	Dialog.o	\
	Order.o	\
	Queue.o	\
	Optimize.o	\
	Semantics.o	\
	Tree2.o	\
	Parser.o	\
	Scanner.o	\
;	$(CC) $(CFLAGS) -o cg $(SYSTEM)	\
	cg.o	\
	EvalC3.o	\
	Tree.o	\
	Errors.o	\
	Positions.o	\
	EvalC.o	\
	TreeC2.o	\
	TreeC1.o	\
	EvalC2.o	\
	GramYacc.o	\
	GramC.o	\
	EvalMod3.o	\
	EvalMod.o	\
	TreeMod2.o	\
	TreeMod1.o	\
	EvalMod2.o	\
	GramMod.o	\
	Dialog.o	\
	Order.o	\
	Queue.o	\
	Optimize.o	\
	Semantics.o	\
	Tree2.o	\
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
