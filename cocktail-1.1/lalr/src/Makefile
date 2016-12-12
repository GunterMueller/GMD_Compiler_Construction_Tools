# $Id: Makefile,v 2.6 1992/09/24 13:14:46 grosch rel $
LIB	= $(HOME)/lib
BIN	= $(HOME)/bin
MC	= MC
MLIB	= ../../reuse/src
FRONT	= ../../front/src
M2FLAGS	= -noindex -norange

DEFSMC	= ArgCheck.md Automaton.md Check.md Compress.md Continue.md \
	  Debug.md Default.md Final.md Gen.md GenLang.md \
	  Infos.md Lookahead.md LR.md Reduce.md

MODSMC	= ArgCheck.mi Automaton.mi Check.mi Compress.mi Continue.mi \
	  Debug.mi Default.mi Final.mi Gen.mi lalr.mi GenLang.mi \
	  Infos.mi Lookahead.mi LR.mi Reduce.mi

DEFSM2C	= ArgCheck.def Automaton.def Check.def Compress.def Continue.def \
	  Debug.def Default.def Final.def Gen.def GenLang.def \
	  Infos.def Lookahead.def LR.def Reduce.def

MODSM2C	= ArgCheck.mod Automaton.mod Check.mod Compress.mod Continue.mod \
	  Debug.mod Default.mod Final.mod Gen.mod lalr.mod GenLang.mod \
	  Infos.mod Lookahead.mod LR.mod Reduce.mod

PLIB	= ParserDrv.mi Parser.md Parser.mi Errors.md Errors.mi Scanner.md Scanner.mi \
	  ParserDrv.c Parser.c Parser.h Errors.c Errors.h Scanner.c Scanner.h

lalr:	$(MC)

# compilation of lalr with MOCKA (mc)

MC:	$(DEFSMC) $(MODSMC)
	echo p lalr | mc $(M2FLAGS) -d $(FRONT) -d $(MLIB)

# compilation of lalr with SUN Modula compiler (m2c)

M2C:	$(DEFSM2C) $(MODSM2C)
	make -f MakefileM2C LIB=$(MLIB) FRONT=$(FRONT)

install:	lalr lalr.sh $(LIB)/lalr
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);' < lalr.sh > $(BIN)/lalr
	chmod a+rx $(BIN)/lalr
	install -c -s -m 755 lalr $(LIB)/lalr
	cd ../lib; cp $(PLIB) $(LIB)/lalr
	cd $(LIB)/lalr; chmod a+r $(PLIB)

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"

m2c:
	co RCS/*
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../front/src -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f core *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug *.bak

.SUFFIXES:	.def .mod .md .mi

.md.def:
	ln $*.md $*.def

.mi.mod:
	ln $*.mi $*.mod
