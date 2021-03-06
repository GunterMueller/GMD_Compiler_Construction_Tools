BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
MC	= MC

SED	= sed -e 's/!!$$/WriteNl (f);/' \
	      -e 's/!\([^!]*\)!$$/WriteS (f, "\1"); WriteNl (f);/' \
	      -e 's/!\([^!]*\)!/WriteS (f, "\1");/g' \
	      -e "s/@\([^@]*\)@$$/WriteS (f, '\1'); WriteNl (f);/" \
	      -e "s/@\([^@]*\)@/WriteS (f, '\1');/g"

SOURCES	= Scanner.mi Scanner.md Parser.md Parser.mi Tree.md Tree.mi Tree2.md Tree2.mi \
	  Semantics.md Semantics.mi Optimize.md Optimize.mi Mod.md Mod.mi C.md C.mi puma.mi

all:	puma_boot

puma:	$(SOURCES) Scanner.Tab Parser.Tab puma_boot

puma_boot:
	echo p puma | mc -d ../../reuse/src

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

Scanner.rpp Parser.lalr:	puma.pars
	cg -xzj puma.pars;

puma.rex:	puma.scan Scanner.rpp
	rpp < puma.scan > puma.rex;

Scanner.md Scanner.mi Scanner.Tab:	puma.rex
	rex -d puma.rex;

Parser.md:	Parser.lalr
	lalr -d -v Parser.lalr;

Parser.mi Parser.Tab:	Parser.lalr
	lalr -v Parser.lalr;

Tree.md:	puma.cg
	echo SELECT AstIn Ast Common PumaIn Puma | cat - puma.cg | cg -dimRyq

Tree.mi:	puma.cg
	echo SELECT AstIn Ast Common PumaIn Puma | cat - puma.cg | cg -imRyq

Tree2.md:	puma.cg
	echo SUBUNIT Tree2 SELECT AstIn Ast | cat - puma.cg | cg -dig

Tree2.mi:	puma.cg
	echo SUBUNIT Tree2 SELECT AstIn Ast | cat - puma.cg | cg -ig

Tree.TS:	puma.cg
	echo SELECT PumaIn Puma | cat - puma.cg | cg -4

Semantics.md Semantics.mi:	sem.puma Tree.TS
	puma -dinw sem.puma;

Optimize.md Optimize.mi:	opt.puma Tree.TS
	puma -diwk opt.puma;

Mod.md Mod.mi:	mod.puma Tree.TS
	$(SED) < mod.puma | puma -dinw;

C.md C.mi:	c.puma Tree.TS
	$(SED) < c.puma | puma -dinw;

puma.mi:	puma.sed
	$(SED) < puma.sed > puma.mi

install:	puma puma.sh $(LIB)/puma
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < puma.sh > $(BIN)/puma
	chmod a+rx $(BIN)/puma
	install -c -s -m 755 puma $(LIB)/puma
	install -c -m 644 Scanner.Tab $(LIB)/puma
	install -c -m 644 Parser.Tab $(LIB)/puma
	install -c -m 644 TypeTab.c $(LIB)/puma
	install -c -m 644 TypeTab.m $(LIB)/puma

# installation directories

$(LIB)/puma:	$(LIB)
	sh -c "if test ! -d $(LIB)/puma; then mkdir $(LIB)/puma; else true; fi"

m2c:
	# co RCS/*
	rm -f ../m2c/*.[hc]
	cp [SP]*Tab TypeTab.[mc] ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

# support for mkid

pumaId:	puma.rex
	echo SCANNER pumaId | cat - puma.rex | \
	sed 's/\(RETURN 1	\)/yyEcho; IO.WriteNl (IO.StdOutput); \1/' | \
	$(BIN).t/rex -sd;
	sed 's/@/pumaId/' < ../../front/src/Id.mi > pumaIdDrv.mi
	echo p pumaIdDrv | mc -d ../../reuse/src
	mv pumaIdDrv pumaId

installId:	pumaId $(LIB)/Id
	echo exec $(LIB)/Id/pumaId -l$(LIB)/Id "2> /dev/null" > $(BIN)/pumaId
	chmod a+rx $(BIN)/pumaId
	install -c -m 644 pumaId.Tab $(LIB)/Id
	install -c -s -m 755 pumaId $(LIB)/Id

$(LIB)/Id:	$(LIB)
	sh -c "if test ! -d $(LIB)/Id; then mkdir $(LIB)/Id; else true; fi"

cleanId:
	rm -f pumaId*

clean:	cleanId
	rm -f _Debug core *.[dior] [A-SU-Za-z]*.m Tree*.m *.bak
