BIN	= $(HOME)/bin
LIB	= $(HOME)/lib

all:	rpp_boot

rpp:	Scanner.md Scanner.mi Scanner.Tab rpp_boot

rpp_boot:	rpp.mi
	echo p rpp | mc -d ../../reuse/src

Scanner.md Scanner.mi Scanner.Tab:	rpp.rex
	rex -d rpp.rex;

install:	rpp rpp.sh Scanner.Tab $(LIB)/rpp
	if test $(LIB) = $(BIN); then echo error: BIN = LIB; false; else true; fi
	sed 's;LIB;$(LIB);g' < rpp.sh > $(BIN)/rpp
	chmod a+rx $(BIN)/rpp
	install -c -s -m 755 rpp $(LIB)/rpp
	install -c -m 644 Scanner.Tab $(LIB)/rpp

# installation directories

$(LIB)/rpp:	$(LIB)
	sh -c "if test ! -d $(LIB)/rpp; then mkdir $(LIB)/rpp; else true; fi"

m2c:
	# co RCS/*
	make Scanner.mi
	cp *Tab ../m2c
	ln *.m[id] ../m2c
	cd ../m2c; make sources M2FLAGS="-c -d../../reuse/src"
	cd ../m2c; rm -f *.m[id]

clean:
	rm -f *.[dimor] rpp *.bak

CLEAN:	clean
	rm -f S*.m? Scanner.Tab
