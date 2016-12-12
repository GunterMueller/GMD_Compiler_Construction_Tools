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

all	: ell

install:	ell ell.sh $(LIB)/ell
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);" < ell.sh > $(BIN)/ell
	chmod a+rx $(BIN)/ell
	install -c $(LIB)/ell ell
	install -c $(LIB)/ell ErrorTab
	install -c $(LIB)/ell Parser.Tab
	install -c $(LIB)/ell Scanner.Tab
	install -c $(LIB)/ell CodeC.tab
	install -c $(LIB)/ell CodeM2.tab
	install -c $(LIB)/ell Semantics.tab

# installation directories

$(LIB)/ell:	$(LIB)
	sh -c "if test ! -d $(LIB)/ell; then mkdir $(LIB)/ell; else true; fi"

# swap all byte pairs of the file Scanner.Tab
# reverse all BITSETs / INTEGERs of the files Parser.Tab CodeC.tab CodeM2.tab Semantics.tab

bin.conv:	convert
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab | convert > .Parser.Tab; mv .Parser.Tab Parser.Tab
	dd conv=swab < CodeC.tab | convert > .CodeC.tab; mv .CodeC.tab CodeC.tab
	dd conv=swab < CodeM2.tab | convert > .CodeM2.tab; mv .CodeM2.tab CodeM2.tab
	dd conv=swab < Semantics.tab | convert > .Semantics.tab; mv .Semantics.tab Semantics.tab

convert:	convert.c
	$(CC) -o convert convert.c

# SYSTEM_	= SYSTEM_.o

# HEAD

sources	: ArgCheck.h

sources	: ArgCheck.c
ArgCheck.o	: ArgCheck.c ArgCheck.h
ArgCheck.o	: Scanner.h

sources	: CodeC.h
CodeC.h	: Tree.h

sources	: CodeC.c
CodeC.o	: CodeC.c CodeC.h
CodeC.o	: Tree.h
CodeC.o	: ArgCheck.h
CodeC.o	: Codes.h
CodeC.o	: Scanner.h
CodeC.o	: Types.h
CodeC.o	: Tree.h

sources	: CodeM2.h
CodeM2.h	: Tree.h

sources	: CodeM2.c
CodeM2.o	: CodeM2.c CodeM2.h
CodeM2.o	: Tree.h
CodeM2.o	: ArgCheck.h
CodeM2.o	: Codes.h
CodeM2.o	: Scanner.h
CodeM2.o	: Types.h
CodeM2.o	: Tree.h

sources	: Codes.h

sources	: Codes.c
Codes.o	: Codes.c Codes.h
Codes.o	: Scanner.h

sources	: Derivable.h

sources	: Derivable.c
Derivable.o	: Derivable.c Derivable.h
Derivable.o	: Table.h
Derivable.o	: Tree.h
Derivable.o	: Types.h

sources	: First.h

sources	: First.c
First.o	: First.c First.h
First.o	: Derivable.h
First.o	: Scanner.h
First.o	: Table.h
First.o	: Types.h
First.o	: Tree.h

sources	: Follow.h

sources	: Follow.c
Follow.o	: Follow.c Follow.h
Follow.o	: Scanner.h
Follow.o	: Table.h
Follow.o	: Tree.h
Follow.o	: Types.h

sources	: Info.h

sources	: Info.c
Info.o	: Info.c Info.h

sources	: Nullable.h

sources	: Nullable.c
Nullable.o	: Nullable.c Nullable.h
Nullable.o	: Table.h
Nullable.o	: Tree.h
Nullable.o	: Types.h

sources	: Parser.h
Parser.h	: Tree.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Scanner.h
Parser.o	: Tree.h

sources	: Reachable.h

sources	: Reachable.c
Reachable.o	: Reachable.c Reachable.h
Reachable.o	: Table.h
Reachable.o	: Types.h

sources	: Scanner.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: ArgCheck.h

sources	: Semantics.h
Semantics.h	: Tree.h

sources	: Semantics.c
Semantics.o	: Semantics.c Semantics.h
Semantics.o	: Tree.h
Semantics.o	: ArgCheck.h
Semantics.o	: Codes.h
Semantics.o	: Derivable.h
Semantics.o	: First.h
Semantics.o	: Follow.h
Semantics.o	: Reachable.h
Semantics.o	: Scanner.h
Semantics.o	: Table.h
Semantics.o	: Tree.h
Semantics.o	: Types.h

sources	: SupC.h

sources	: SupC.c
SupC.o	: SupC.c SupC.h
SupC.o	: ArgCheck.h
SupC.o	: Tree.h

sources	: SupM2.h

sources	: SupM2.c
SupM2.o	: SupM2.c SupM2.h
SupM2.o	: ArgCheck.h
SupM2.o	: Tree.h

sources	: Table.h
Table.h	: Tree.h

sources	: Table.c
Table.o	: Table.c Table.h
Table.o	: Tree.h
Table.o	: Types.h

sources	: Tree.h

sources	: Tree.c
Tree.o	: Tree.c Tree.h
Tree.o	: Info.h

sources	: Types.h

sources	: Types.c
Types.o	: Types.c Types.h

sources	: ell.c
all	: ell
ell.o	: ell.c
ell.o	: ArgCheck.h
ell.o	: CodeC.h
ell.o	: CodeM2.h
ell.o	: Info.h
ell.o	: Parser.h
ell.o	: Scanner.h
ell.o	: Tree.h
ell.o	: Semantics.h
ell.o	: SupC.h
ell.o	: SupM2.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

ell	: $(SYSTEM)	\
	ell.o	\
	SupM2.o	\
	Tree.o	\
	Info.o	\
	ArgCheck.o	\
	Scanner.o	\
	SupC.o	\
	Semantics.o	\
	Types.o	\
	Table.o	\
	Reachable.o	\
	Follow.o	\
	First.o	\
	Derivable.o	\
	Codes.o	\
	Parser.o	\
	CodeM2.o	\
	CodeC.o	\
;	$(CC) $(CFLAGS) -o ell $(SYSTEM)	\
	ell.o	\
	SupM2.o	\
	Tree.o	\
	Info.o	\
	ArgCheck.o	\
	Scanner.o	\
	SupC.o	\
	Semantics.o	\
	Types.o	\
	Table.o	\
	Reachable.o	\
	Follow.o	\
	First.o	\
	Derivable.o	\
	Codes.o	\
	Parser.o	\
	CodeM2.o	\
	CodeC.o	\
	$(CLIBS)

# TAIL

clean	:
	rm -f core *.o convert

.SUFFIXES: .md .mi .h .c .o

.mi.c:
	mtc $(M2FLAGS) $*.mi;

.md.h:
	mtc $(M2FLAGS) $*.md;

.c.o:
	$(CC) $(CFLAGS) -c $*.c
