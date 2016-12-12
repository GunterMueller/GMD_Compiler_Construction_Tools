LIB	= $(HOME)/lib
BIN	= $(HOME)/bin
MC	= MC
MLIB	= ../../reuse/src
FRONT	= ../../front/src
M2FLAGS	= -noindex -norange

DEFSMC	= ArgCheck.md MakeBNF.md
MODSMC	= ArgCheck.mi bnf.mi MakeBNF.mi
DEFSM2C	= ArgCheck.def MakeBNF.def
MODSM2C	= ArgCheck.mod bnf.mod MakeBNF.mod

bnf:	$(MC)

# compilation of bnf with MOCKA (mc)

MC:	$(DEFSMC) $(MODSMC)
	echo p bnf | mc $(M2FLAGS) -d $(FRONT) -d $(MLIB)

# compilation of bnf with SUN Modula compiler (m2c)

M2C:	$(DEFSM2C) $(MODSM2C)
	make -f MakefileM2C LIB=$(MLIB) FRONT=$(FRONT)

install:	bnf bnf.sh $(LIB)/lalr
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);' < bnf.sh > $(BIN)/bnf
	chmod a+rx $(BIN)/bnf
	install -c -s -m 755 bnf $(LIB)/lalr

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
