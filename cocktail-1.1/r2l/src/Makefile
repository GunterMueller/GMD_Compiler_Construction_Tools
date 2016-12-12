BIN	= $(HOME)/bin
LIB	= $(HOME)/lib

DEFS	= DefTable.md Errors.md 
MODS	= DefTable.mi Errors.mi r2l.mi

all:	r2l_boot

r2l:	Scanner.md Scanner.mi Parser.md Parser.mi r2l_boot

r2l_boot:	$(DEFS) $(MODS)
	echo p r2l | mc -d ../../reuse/src

Scanner.mi Scanner.md:	r2l.rex
	rex -d r2l.rex;

Parser.mi Parser.md:	r2l.lalr
	lalr -b -d r2l.lalr;

install:	r2l r2l.sh $(LIB)/r2l
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed "s;LIB;$(LIB);g" < r2l.sh > $(BIN)/r2l
	chmod a+rx $(BIN)/r2l
	install r2l -c $(LIB)/r2l
	install Scanner.Tab -c $(LIB)/r2l
	install Parser.Tab -c $(LIB)/r2l

# installation directories

$(LIB)/r2l:	$(LIB)
	sh -c "if test ! -d $(LIB)/r2l; then mkdir $(LIB)/r2l; else true; fi"

m2c:
	# co RCS/*
	make Scanner.mi Parser.mi
	cp *Tab ../m2c
	ln *.m[id] ../m2c
	rm -f ../m2c/*.[hc]
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f core *.[dimor] ERRORS LISTING _Debug r2l

CLEAN:	clean
	rm -f Scanner.m? Parser.m? *.Tab
