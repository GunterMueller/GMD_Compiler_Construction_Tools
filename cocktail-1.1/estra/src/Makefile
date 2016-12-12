#	$Id: Makefile,v 2.24 1992/09/24 13:16:41 grosch rel $

BIN	= $(HOME)/bin
LIB	= $(HOME)/lib

DEFS	= ArgCheck.md Automaton.md CodeM2.md Complete.md	\
	  Environs.md Grammar.md Info.md Match.md Patterns.md	\
	  Reduced.md Semantics.md Test.md Types.md
IMPS	= ArgCheck.mi Automaton.mi CodeM2.mi Complete.mi	\
	  Environs.mi Grammar.mi Info.mi Match.mi Patterns.mi	\
	  Reduced.mi Semantics.mi Test.mi Types.mi
GENDEFS	= Parser.md Scanner.md Tree.md 
GENIMPS	= Parser.mi Scanner.mi Tree.mi 


all:	estra_boot

estra:	$(GENDEFS) $(GENIMPS) estra_boot

estra_boot:	$(DEFS) $(IMPS) estra.mi
	rm -f estra
	echo p estra | mc -noindex -norange -d ../../common/src -d ../../reuse/src

Tree.md Tree.mi:	Tree.ast
	cg -deiwmR Tree.ast;

Parser.md Parser.mi Parser.Tab:	Estral.lalr
	lalr -d Estral.lalr;

Scanner.md Scanner.mi Scanner.Tab:	Estral.rex
	rex -d Estral.rex;

install:	estra estra.sh $(LIB)/estra
	sed 's;LIB;$(LIB);' < estra.sh > $(BIN)/estra
	chmod a+rx $(BIN)/estra
	install -c -s -m 755 estra $(LIB)/estra
	install -c -m 644 Scanner.Tab $(LIB)/estra
	install -c -m 644 Parser.Tab $(LIB)/estra
	install -c -m 644 ErrorTab $(LIB)/estra

# installation directories

$(LIB)/estra:	$(LIB)
	sh -c "if test ! -d $(LIB)/estra; then mkdir $(LIB)/estra; else true; fi"

m2c:
	co RCS/*
	make $(GENDEFS) $(GENIMPS) $(DEFS) $(IMPS) estra.mi
	chmod u+w ErrorTab
	cp *Tab ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../common/src -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f core *.[dimor] ERRORS LISTING _Debug *.bak

CLEAN:	clean
	rm -f CodeM2.mi Parser.m[di] Parser.Tab Scanner.m[di] Scanner.Tab Tree.m[di] estra

.SUFFIXES: .MD .md .MI .mi

.MD.mi:; mpp < $*.MD > $*.md

.MI.mi:; mpp < $*.MI > $*.mi
