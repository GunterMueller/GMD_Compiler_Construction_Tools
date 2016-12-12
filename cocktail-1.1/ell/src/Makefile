#
#	ell2 - a redesign of ell
#
#	$RCSfile: Makefile,v $
#	
#	purpose:	make and install ell
#
#	$Author: grosch $
#	$Date: 1992/09/24 13:15:06 $
#

LIB	= $(HOME)/lib
BIN	= $(HOME)/bin
ESTRA	= -dibW

DEFS	= ArgCheck.md Codes.md Derivable.md First.md Follow.md Info.md \
	  Reachable.md SupC.md SupM2.md Table.md 
IMPS	= ArgCheck.mi Codes.mi Derivable.mi First.mi Follow.mi Info.mi \
	  Reachable.mi SupC.mi SupM2.mi Table.mi 
GENDEFS	= CodeC.md CodeM2.md Parser.md Scanner.md Semantics.md Tree.md
GENIMPS	= CodeC.mi CodeM2.mi Parser.mi Scanner.mi Semantics.mi Tree.mi

all:	ell_boot

ell:	$(GENDEFS) $(GENIMPS) ell_boot

ell_boot:	$(DEFS) $(IMPS) ell.mi
	rm -f ell
	echo p ell | mc -d ../../common/src -d ../../reuse/src

install:	ell ell.sh Scanner.Tab ErrorTab Parser.Tab Semantics.tab CodeC.tab CodeM2.tab $(LIB)/ell
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);" < ell.sh > $(BIN)/ell
	chmod a+rx $(BIN)/ell
	chmod u+w ErrorTab
	install -c -s -m 755 ell $(LIB)/ell
	install -c -m 644 Scanner.Tab $(LIB)/ell
	install -c -m 644 Parser.Tab $(LIB)/ell
	install -c -m 644 ErrorTab $(LIB)/ell
	install -c -m 644 Semantics.tab $(LIB)/ell
	install -c -m 644 CodeC.tab $(LIB)/ell
	install -c -m 644 CodeM2.tab $(LIB)/ell

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

Scanner.mi Scanner.md Scanner.Tab:	ell.rex
	rex -d ell.rex;

Parser.mi Parser.md Parser.Tab:	ell.ell
	ell -di ell.ell;

Tree.mi Tree.md:	ell.ast
	cg -dimR ell.ast;

Semantics.md Semantics.mi Semantics.tab:	Sem.estra
	estra $(ESTRA) Sem.estra;

CodeC.md CodeC.mi CodeC.tab:	CodeC.ESTRA
	mpp < CodeC.ESTRA | estra $(ESTRA);

CodeM2.md CodeM2.mi CodeM2.tab:	CodeM2.ESTRA
	mpp < CodeM2.ESTRA | estra $(ESTRA);

m2c:
	co RCS/*
	make $(GENDEFS) $(GENIMPS) $(DEFS) $(IMPS) ell.mi
	chmod u+w ErrorTab
	cp *[Tt]ab ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../common/src -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f core ERRORS LISTING *.[dimor] ell convert *.bak

CLEAN:	clean
	rm -f ArgCheck.mi			\
	Scanner.m[di] Scanner.Tab		\
	Parser.m[di] Parser.Tab			\
	Tree.m[di]				\
	Semantics.m[di] Semantics.tab		\
	CodeM2.m[di] CodeM2.tab			\
	CodeC.m[di] CodeC.tab			\
	SupM2.mi SupC.mi

.SUFFIXES:	.MI .mi

.MI.mi:;	mpp < $*.MI > $*.mi;
