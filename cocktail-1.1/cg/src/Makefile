BIN	= $(HOME)/bin
LIB	= $(HOME)/lib
MC	= MC

SED	= sed -e 's/!!$$/WriteNl (f);/' \
	      -e 's/!\([^!]*\)!$$/WriteS (f, "\1"); WriteNl (f);/' \
	      -e 's/!\([^!]*\)!/WriteS (f, "\1");/g' \
	      -e "s/@\([^@]*\)@$$/WriteS (f, '\1'); WriteNl (f);/" \
	      -e "s/@\([^@]*\)@/WriteS (f, '\1');/g"

SOURCES	= Scanner.mi Scanner.md Errors.md Errors.mi \
	  Parser.md Parser.mi Tree.md Tree.mi Tree2.md Tree2.mi GramMod.md \
	  GramMod.mi Semantics.mi Order.mi Optimize.mi Dialog.mi \
	  TreeMod1.mi TreeMod2.mi EvalMod.mi EvalMod2.mi EvalMod3.mi \
	  GramC.md GramC.mi TreeC1.mi TreeC2.mi EvalC.mi EvalC2.mi EvalC3.mi cg.mi \
	  GramYacc.md GramYacc.mi

all:	cg_boot

cg:	$(SOURCES) cg_boot

cg_boot:
	echo p cg | mc -d ../../reuse/src

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab

Scanner.md Scanner.mi:	cg.rex
	rex -d cg.rex;

Parser.md:	cg.lalr
	lalr -b -d cg.lalr;

Parser.mi:	cg.lalr
	lalr -b -v cg.lalr;

Errors.mi:	Errors.0 \
	/tmp/cg/consts1 /tmp/cg/writes1 /tmp/cg/consts2 /tmp/cg/writes2
	/lib/cpp -P Errors.0 Errors.mi

Tree.md:	cg.cg
	echo SELECT AstIn Ast Common Cg Ag | cat - cg.cg | cg -diqmR

Tree.mi:	cg.cg
	echo SELECT AstIn Ast Common Cg Ag | cat - cg.cg | cg -iqmR

Tree2.md:	cg.cg
	echo SUBUNIT Tree2 SELECT AstIn Ast | cat - cg.cg | cg -dip

Tree2.mi:	cg.cg
	echo SUBUNIT Tree2 SELECT AstIn Ast | cat - cg.cg | cg -ip

Tree.TS:	cg.cg
	echo SELECT AstIn Ast Common Cg Ag | cat - cg.cg | cg -4

GramMod.md GramMod.mi:	mod0.puma Tree.TS
	$(SED) < mod0.puma | puma -dinw;

GramC.md GramC.mi:	c0.puma Tree.TS
	$(SED) < c0.puma | puma -dinw;

GramYacc.md GramYacc.mi:	y0.puma Tree.TS
	$(SED) < y0.puma | puma -dinw;

Semantics.md Semantics.mi /tmp/cg/consts1 /tmp/cg/writes1:	sem.puma Tree.TS /tmp/cg
	awk -f cg.awk1 < sem.puma > /tmp/cg/sem
	/lib/cpp -P < /tmp/cg/sem | puma -dinw;
	sed -f cg.sed2 < /tmp/cg/writes01 > /tmp/cg/writes1

Order.md Order.mi /tmp/cg/consts2 /tmp/cg/writes2:	oag.puma Tree.TS /tmp/cg
	awk -f cg.awk2 < oag.puma > /tmp/cg/oag
	/lib/cpp -P < /tmp/cg/oag | puma -dinw;
	sed -f cg.sed2 < /tmp/cg/writes02 > /tmp/cg/writes2

Optimize.md Optimize.mi:	opt.puma Tree.TS
	/lib/cpp -P < opt.puma | puma -dinw;

Dialog.mi:	Dialog.sed
	$(SED) < Dialog.sed > Dialog.mi

TreeMod1.md TreeMod1.mi:	mod1.puma Tree.TS
	$(SED) < mod1.puma | puma -dinw;

TreeMod2.md TreeMod2.mi:	mod2.puma Tree.TS
	$(SED) < mod2.puma | puma -dinw;

EvalMod.md EvalMod.mi:	mod3.puma Tree.TS
	$(SED) < mod3.puma | puma -dinw;

EvalMod2.md EvalMod2.mi:	mod4.puma Tree.TS
	$(SED) < mod4.puma | puma -dinw;

EvalMod3.md EvalMod3.mi:	mod5.puma Tree.TS
	$(SED) < mod5.puma | puma -dinw;

TreeC1.md TreeC1.mi:	c1.puma Tree.TS
	$(SED) < c1.puma | puma -dinw;

TreeC2.md TreeC2.mi:	c2.puma Tree.TS
	$(SED) < c2.puma | puma -dinw;

EvalC.md EvalC.mi:	c3.puma Tree.TS
	$(SED) < c3.puma | puma -dinw;

EvalC2.md EvalC2.mi:	c4.puma Tree.TS
	$(SED) < c4.puma | puma -dinw;

EvalC3.md EvalC3.mi:	c5.puma Tree.TS
	$(SED) < c5.puma | puma -dinw;

cg.mi:	cg.sed
	$(SED) < cg.sed > cg.mi

install:	cg cg.sh $(LIB)/cg
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < cg.sh > $(BIN)/cg
	cp $(BIN)/cg $(BIN)/ag
	cp $(BIN)/cg $(BIN)/ast
	chmod a+rx $(BIN)/cg $(BIN)/ast $(BIN)/ag
	install -c -m 755 gmdcpp $(BIN)
	install -c -m 755 gmdupd $(BIN)
	install -c -m 755 gmdrm $(BIN)
	install -c -s -m 755 cg $(LIB)/cg
	install -c -m 644 Scanner.Tab $(LIB)/cg
	install -c -m 644 Parser.Tab $(LIB)/cg
	install -c -m 644 TypeTab.c $(LIB)/cg
	install -c -m 644 TypeTab.m $(LIB)/cg

# installation directories

$(LIB)/cg:	$(LIB)
	sh -c "if test ! -d $(LIB)/cg; then mkdir $(LIB)/cg; else true; fi"

/tmp/cg:	/tmp
	sh -c "if test ! -d /tmp/cg; then mkdir /tmp/cg; else true; fi"

m2c:
	# co RCS/*
	make $(SOURCES)
	rm -f ../m2c/*.[hc]
	cp [SP]*Tab TypeTab.[mc] gmd* ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

# support for mkid

cgId:	cg.rex
	echo SCANNER cgId | cat - cg.rex | \
	sed 's/\(RETURN.*Ident\)/yyEcho; IO.WriteNl (IO.StdOutput); \1/' | \
	$(BIN).t/rex -sd;
	sed 's/@/cgId/' < ../../front/src/Id.mi > cgIdDrv.mi
	echo p cgIdDrv | mc -d ../../reuse/src
	mv cgIdDrv cgId

installId:	cgId $(LIB)/Id
	echo exec $(LIB)/Id/cgId -l$(LIB)/Id "2> /dev/null" > $(BIN)/cgId
	chmod a+rx $(BIN)/cgId
	install -c -m 644 cgId.Tab $(LIB)/Id
	install -c -s -m 755 cgId $(LIB)/Id

$(LIB)/Id:	$(LIB)
	sh -c "if test ! -d $(LIB)/Id; then mkdir $(LIB)/Id; else true; fi"

cleanId:
	rm -f cgId*

clean:	cleanId
	rm -f _Debug core *.[dior] [A-SU-Za-z]*.m *.bak
