BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
OPT	= -O
CC	= cc

                # C library (reuse)
REUSE	= ../../reuse/m2c

                # C library (common)
COMMON	= ../../common/m2c

                # C libraries
CLIBS	= $(COMMON)/libcommon.a $(REUSE)/libreuse.a

                # options for C compiler
CFLAGS	= -w -I$(COMMON) -I$(REUSE) $(OPT)

M2FLAGS	= -c

all	: estra

install:	estra estra.sh $(LIB)/estra
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);" < estra.sh > $(BIN)/estra
	chmod a+rx $(BIN)/estra
	install estra $(LIB)/estra estra
	install Scanner.Tab $(LIB)/estra Scanner.Tab
	install Parser.Tab $(LIB)/estra Parser.Tab
	install ErrorTab $(LIB)/estra ErrorTab

# installation directories

$(LIB)/estra:	$(LIB)
	sh -c "if test ! -d $(LIB)/estra; then mkdir $(LIB)/estra; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab


# HEAD

sources	: ArgCheck.h

sources	: ArgCheck.c
ArgCheck.o	: ArgCheck.c ArgCheck.h
ArgCheck.o	: Scanner.h

sources	: Automaton.h

sources	: Automaton.c
Automaton.o	: Automaton.c Automaton.h
Automaton.o	: Info.h

sources	: CodeM2.h

sources	: CodeM2.c
CodeM2.o	: CodeM2.c CodeM2.h
CodeM2.o	: ArgCheck.h
CodeM2.o	: Automaton.h
CodeM2.o	: Environs.h
CodeM2.o	: Grammar.h
CodeM2.o	: Match.h
CodeM2.o	: Parser.h
CodeM2.o	: Scanner.h
CodeM2.o	: Tree.h
CodeM2.o	: Types.h
CodeM2.o	: ArgCheck.h

sources	: Complete.h
Complete.h	: Environs.h

sources	: Complete.c
Complete.o	: Complete.c Complete.h
Complete.o	: Environs.h
Complete.o	: Patterns.h

sources	: Environs.h
Environs.h	: Patterns.h

sources	: Environs.c
Environs.o	: Environs.c Environs.h
Environs.o	: Grammar.h
Environs.o	: Patterns.h
Environs.o	: Scanner.h
Environs.o	: Types.h

sources	: Grammar.h

sources	: Grammar.c
Grammar.o	: Grammar.c Grammar.h
Grammar.o	: Scanner.h
Grammar.o	: Types.h
Grammar.o	: Info.h

sources	: Info.h

sources	: Info.c
Info.o	: Info.c Info.h
Info.o	: Patterns.h

sources	: Match.h

sources	: Match.c
Match.o	: Match.c Match.h
Match.o	: ArgCheck.h
Match.o	: Automaton.h
Match.o	: Environs.h
Match.o	: Grammar.h
Match.o	: Parser.h
Match.o	: Patterns.h
Match.o	: Scanner.h
Match.o	: Types.h
Match.o	: Patterns.h
Match.o	: ArgCheck.h
Match.o	: Automaton.h
Match.o	: Patterns.h

sources	: Parser.h
Parser.h	: Tree.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Scanner.h
Parser.o	: Tree.h
Parser.o	: Tree.h

sources	: Patterns.h

sources	: Patterns.c
Patterns.o	: Patterns.c Patterns.h
Patterns.o	: Grammar.h
Patterns.o	: Scanner.h
Patterns.o	: Types.h
Patterns.o	: Scanner.h

sources	: Reduced.h

sources	: Reduced.c
Reduced.o	: Reduced.c Reduced.h
Reduced.o	: Grammar.h
Reduced.o	: Scanner.h
Reduced.o	: Types.h

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h

sources	: Semantics.h

sources	: Semantics.c
Semantics.o	: Semantics.c Semantics.h
Semantics.o	: Complete.h
Semantics.o	: Environs.h
Semantics.o	: Grammar.h
Semantics.o	: Parser.h
Semantics.o	: Patterns.h
Semantics.o	: Reduced.h
Semantics.o	: Scanner.h
Semantics.o	: Tree.h
Semantics.o	: Types.h

sources	: Test.h

sources	: Test.c
Test.o	: Test.c Test.h
Test.o	: ArgCheck.h

sources	: Tree.h
Tree.h	: Environs.h
Tree.h	: Patterns.h

sources	: Tree.c
Tree.o	: Tree.c Tree.h

sources	: Types.h

sources	: Types.c
Types.o	: Types.c Types.h
Types.o	: Scanner.h

sources	: estra.c
all	: estra
estra.o	: estra.c
estra.o	: ArgCheck.h
estra.o	: CodeM2.h
estra.o	: Info.h
estra.o	: Match.h
estra.o	: Parser.h
estra.o	: Scanner.h
estra.o	: Semantics.h
estra.o	: Test.h
estra.o	: ArgCheck.h
estra.o	: Grammar.h
estra.o	: Parser.h
estra.o	: Test.h
estra.o	: Tree.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

estra	: $(SYSTEM)	\
	estra.o	\
	Tree.o	\
	Patterns.o	\
	Scanner.o	\
	Types.o	\
	Grammar.o	\
	Info.o	\
	Environs.o	\
	Test.o	\
	ArgCheck.o	\
	Parser.o	\
	Semantics.o	\
	Reduced.o	\
	Complete.o	\
	Match.o	\
	Automaton.o	\
	CodeM2.o	\
;	$(CC) $(CFLAGS) -o estra $(SYSTEM)	\
	estra.o	\
	Tree.o	\
	Patterns.o	\
	Scanner.o	\
	Types.o	\
	Grammar.o	\
	Info.o	\
	Environs.o	\
	Test.o	\
	ArgCheck.o	\
	Parser.o	\
	Semantics.o	\
	Reduced.o	\
	Complete.o	\
	Match.o	\
	Automaton.o	\
	CodeM2.o	\
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
