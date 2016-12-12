BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
MLIB	= ../../reuse/src
MC	= MC

DEFSMC	= Classes.md DefTable.md Dfa.md Errors.md Nfa.md GenTabs.md \
	  ScanGen.md ScanTabs.md Traces.md Tree.md

MODSMC	= Classes.mi DefTable.mi Dfa.mi Errors.mi Nfa.mi GenTabs.mi \
	  ScanTabs.mi Traces.mi Tree.mi rex.mi

DEFSM2C	= Classes.def DefTable.def Dfa.def Errors.def Nfa.def GenTabs.def \
	  ScanGen.def ScanTabs.def Traces.def Tree.def

MODSM2C	= Classes.mod DefTable.mod Dfa.mod Errors.mod Nfa.mod GenTabs.mod \
	  ScanTabs.mod Traces.mod Tree.mod rex.mod

rex:	$(MC)_boot

# compilation of Rex with MOCKA (mc)

MC:	Scanner.md Scanner.mi Scanner.Tab Parser.md Parser.mi Parser.Tab \
	Tree0.md Tree0.mi Eval.md Eval.mi MC_boot

MC_boot:	$(DEFSMC) $(MODSMC)
	echo p rex | mc -d $(MLIB)

Scanner.mi Scanner.md Scanner.Tab:	rex.rex
	$(BIN)/rex -di rex.rex;

# compilation of Rex with SUN Modula compiler (m2c)

M2C:	Scanner.def Scanner.mod Parser.def Parser.mod Tree0.def Tree0.mod Eval.def Eval.mod M2C_boot

M2C_boot:	$(DEFSM2C) $(MODSM2C)
	ln Scanner.md Scanner.def
	ln Scanner.mi Scanner.mod
	ln Parser.md Parser.def
	ln Parser.mi Parser.mod
	make -f MakefileM2C LIB=$(MLIB)

Scanner.mod Scanner.def:	rex.rex
	$(BIN)/rex -di rex.rex;

# generation of the parser using 'lalr'

Parser.mi Parser.md Parser.Tab:	rex.lalr
	lalr -b -d rex.lalr;

Parser.mod Parser.def:	rex.lalr
	lalr -b -d rex.lalr;
	ln Parser.mi Parser.mod
	ln Parser.md Parser.def

Tree0.md Tree0.mi:	rex.cg
	cg -dimtwFDI rex.cg;

Eval.md Eval.mi:	rex.cg
	cg -DI rex.cg;

install:	rex rex.sh $(LIB)/rex
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);g" < rex.sh > $(BIN)/rex
	chmod a+rx $(BIN)/rex
	install -c -s -m 755 rex $(LIB)/rex
	install -c -m 644 Scanner.Tab $(LIB)/rex
	install -c -m 644 Parser.Tab $(LIB)/rex
	cp ../lib/S* $(LIB)/rex
	chmod a+r $(LIB)/rex/S*

# installation directories

$(LIB)/rex:	$(LIB)
	sh -c "if test ! -d $(LIB)/rex; then mkdir $(LIB)/rex; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

m2c:
	co RCS/*
	cp [SP]*Tab ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

# support for mkid

rexId:	rex.rex
	echo SCANNER rexId | cat - rex.rex | \
	sed 's/\(RETURN.*Ident\)/yyEcho; IO.WriteNl (IO.StdOutput); \1/' | \
	$(BIN).t/rex -sdi;
	sed 's/@/rexId/' < ../../front/src/Id.mi > rexIdDrv.mi
	echo p rexIdDrv | mc -d $(MLIB)
	mv rexIdDrv rexId

installId:	rexId $(LIB)/Id
	echo exec $(LIB)/Id/rexId -l$(LIB)/Id "2> /dev/null" > $(BIN)/rexId
	chmod a+rx $(BIN)/rexId
	install -c -m 644 rexId.Tab $(LIB)/Id
	install -c -s -m 755 rexId $(LIB)/Id

$(LIB)/Id:	$(LIB)
	sh -c "if test ! -d $(LIB)/Id; then mkdir $(LIB)/Id; else true; fi"

cleanId:
	rm -f rexId*

clean:	cleanId
	rm -f core *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug rex *.bak

.SUFFIXES:	.def .mod .md .mi

.md.def:
	ln $*.md $*.def

.mi.mod:
	ln $*.mi $*.mod
