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

PLIB	= ParserDrv.mi Parser.md Parser.mi Errors.md Errors.mi Scanner.md Scanner.mi \
	  ParserDrv.c Parser.c Parser.h Errors.c Errors.h Scanner.c Scanner.h

all	: lalr

install:	lalr lalr.sh $(LIB)/lalr
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	install -c $(LIB)/lalr lalr
	sed "s;LIB;$(LIB);" < lalr.sh > $(BIN)/lalr
	chmod a+rx $(BIN)/lalr
	cd ../lib; cp $(PLIB) $(LIB)/lalr
	cd $(LIB)/lalr; chmod a+r $(PLIB)

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"


# HEAD

sources	: ArgCheck.h

sources	: ArgCheck.c
ArgCheck.o	: ArgCheck.c ArgCheck.h
ArgCheck.o	: Check.h
ArgCheck.o	: Debug.h
ArgCheck.o	: Default.h
ArgCheck.o	: Gen.h

sources	: Automaton.h

sources	: Automaton.c
Automaton.o	: Automaton.c Automaton.h
Automaton.o	: Continue.h

sources	: Check.h

sources	: Check.c
Check.o	: Check.c Check.h
Check.o	: Automaton.h
Check.o	: Debug.h

sources	: Compress.h
Compress.h	: Automaton.h
Compress.h	: Gen.h

sources	: Compress.c
Compress.o	: Compress.c Compress.h
Compress.o	: Automaton.h
Compress.o	: Gen.h

sources	: Continue.h
Continue.h	: Automaton.h

sources	: Continue.c
Continue.o	: Continue.c Continue.h
Continue.o	: Automaton.h
Continue.o	: Gen.h

sources	: Debug.h
Debug.h	: Automaton.h

sources	: Debug.c
Debug.o	: Debug.c Debug.h
Debug.o	: Automaton.h
Debug.o	: Continue.h

sources	: Default.h
Default.h	: Automaton.h
Default.h	: Gen.h

sources	: Default.c
Default.o	: Default.c Default.h
Default.o	: Automaton.h
Default.o	: Gen.h

sources	: Final.h

sources	: Final.c
Final.o	: Final.c Final.h
Final.o	: Automaton.h
Final.o	: Gen.h

sources	: Gen.h
Gen.h	: Automaton.h

sources	: Gen.c
Gen.o	: Gen.c Gen.h
Gen.o	: ArgCheck.h
Gen.o	: Automaton.h
Gen.o	: Compress.h
Gen.o	: Continue.h
Gen.o	: Default.h
Gen.o	: Final.h
Gen.o	: GenLang.h

sources	: GenLang.h

sources	: GenLang.c
GenLang.o	: GenLang.c GenLang.h
GenLang.o	: Automaton.h
GenLang.o	: Compress.h
GenLang.o	: ArgCheck.h
GenLang.o	: Gen.h

sources	: Infos.h

sources	: Infos.c
Infos.o	: Infos.c Infos.h
Infos.o	: Automaton.h
Infos.o	: Compress.h
Infos.o	: Gen.h

sources	: LR.h

sources	: LR.c
LR.o	: LR.c LR.h
LR.o	: Automaton.h

sources	: Lookahead.h

sources	: Lookahead.c
Lookahead.o	: Lookahead.c Lookahead.h
Lookahead.o	: Automaton.h
Lookahead.o	: Check.h

sources	: Reduce.h

sources	: Reduce.c
Reduce.o	: Reduce.c Reduce.h
Reduce.o	: Automaton.h

sources	: lalr.c
all	: lalr
lalr.o	: lalr.c
lalr.o	: ArgCheck.h
lalr.o	: Automaton.h
lalr.o	: Check.h
lalr.o	: Gen.h
lalr.o	: Infos.h
lalr.o	: Lookahead.h
lalr.o	: LR.h
lalr.o	: Reduce.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

lalr	: $(SYSTEM)	\
	lalr.o	\
	Reduce.o	\
	Automaton.o	\
	Continue.o	\
	Gen.o	\
	GenLang.o	\
	ArgCheck.o	\
	Default.o	\
	Debug.o	\
	Check.o	\
	Compress.o	\
	Final.o	\
	LR.o	\
	Lookahead.o	\
	Infos.o	\
;	$(CC) $(CFLAGS) -o lalr $(SYSTEM)	\
	lalr.o	\
	Reduce.o	\
	Automaton.o	\
	Continue.o	\
	Gen.o	\
	GenLang.o	\
	ArgCheck.o	\
	Default.o	\
	Debug.o	\
	Check.o	\
	Compress.o	\
	Final.o	\
	LR.o	\
	Lookahead.o	\
	Infos.o	\
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
