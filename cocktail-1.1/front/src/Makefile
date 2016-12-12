# $Id: Makefile,v 2.8 1992/09/09 12:26:36 grosch rel $
LIB	= $(HOME)/lib
BIN	= $(HOME)/bin
MLIB	= ../../reuse/src
MC	= MC
M2FLAGS	= -noindex -norange

DEFSMC	= Actions.md Character.md Checks.md Errors.md \
	  Limits.md Listing.md Oper.md Path.md Rules.md \
	  SysError.md TokenTab.md Tokens.md WriteTok.md

MODSMC	= Actions.mi Character.mi Checks.mi Errors.mi \
	  Limits.mi Listing.mi Oper.mi Pars.mi Path.mi Rules.mi \
	  SysError.mi TokenTab.mi Tokens.mi WriteTok.mi

DEFSM2C	= Actions.def Character.def Checks.def Errors.def \
	  Limits.def Listing.def Oper.def Path.def Rules.def \
	  SysError.def TokenTab.def Tokens.def WriteTok.def

MODSM2C	= Actions.mod Character.mod Checks.mod Errors.mod \
	  Limits.mod Listing.mod Oper.mod Pars.mod Path.mod Rules.mod \
	  SysError.mod TokenTab.mod Tokens.mod WriteTok.mod

Scanner.Tab:	$(MC)_boot

# compilation of the front-end with MOCKA (mc)

MC:	Scanner.md Scanner.mi Parser.md Parser.mi MC_boot

MC_boot:	$(DEFSMC) $(MODSMC)
	echo p Pars | mc $(M2FLAGS) -d $(MLIB)

# compilation of the front-end with SUN Modula compiler (m2c)

M2C:	Scanner.def Scanner.mod Parser.def Parser.mod M2C_boot

M2C_boot:	$(DEFSM2C) $(MODSM2C)
	make -f MakefileM2C LIB=$(MLIB)

Scanner.md Scanner.mi:	input.rex
	rex -d input.rex;

Parser.md Parser.mi:	input.lalr
	lalr -b -d input.lalr;

install:	Scanner.Tab Parser.Tab ErrorTab $(LIB)/lalr
	install -c -m 644 Scanner.Tab $(LIB)/lalr
	install -c -m 644 Parser.Tab $(LIB)/lalr
	install -c -m 644 ErrorTab $(LIB)/lalr

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

m2c:
	co RCS/*
	cp [EPS]*Tab ../m2c
	chmod u+w ../m2c/ErrorTab
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

# support for mkid

lalrId:	input.rex
	echo SCANNER lalrId | cat - input.rex | \
	sed 's/\(RETURN.*Ident\)/yyEcho; IO.WriteNl (IO.StdOutput); \1/' | \
	$(BIN).sparc.t/rex -sd;
	sed 's/@/lalrId/' < ../../front/src/Id.mi > lalrIdDrv.mi
	echo p lalrIdDrv | mc -d $(MLIB)
	mv lalrIdDrv lalrId

installId:	lalrId $(LIB)/Id
	echo exec $(LIB)/Id/lalrId -l$(LIB)/Id "2> /dev/null" > $(BIN)/lalrId
	chmod a+rx $(BIN)/lalrId
	install -c -m 644 lalrId.Tab $(LIB)/Id
	install -c -s -m 755 lalrId $(LIB)/Id

$(LIB)/Id:	$(LIB)
	sh -c "if test ! -d $(LIB)/Id; then mkdir $(LIB)/Id; else true; fi"

cleanId:
	rm -f lalrId*

clean:	cleanId
	rm -f core *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug Pars *.bak

.SUFFIXES:	.def .mod .md .mi

.md.def:
	ln $*.md $*.def

.mi.mod:
	ln $*.mi $*.mod
