# $Id: Makefile,v 1.18 1992/08/11 13:28:33 grosch rel $

DEFS	= Parser.md Scanner.md Table.md
IMPS	= Parser.mi Scanner.mi Table.mi
LIB	= $(HOME)/lib
BIN	= $(HOME)/bin


all:	mpp_boot

mpp:	Parser.md Parser.mi mpp_boot

mpp_boot:	Scanner.md Scanner.mi Table.md Table.mi mpp.mi
	echo p mpp | mc -d ../../common/src -d ../../reuse/src

Parser.mi Parser.md Parser.Tab:	mpp.ell
	ell -di mpp.ell;

install:	mpp mpp.sh Parser.Tab $(LIB)/mpp
	sed 's;LIB;$(LIB);' < mpp.sh > $(BIN)/mpp
	chmod a+rx $(BIN)/mpp
	install -c -s -m 755 mpp $(LIB)/mpp
	install -c -m 644 Parser.Tab $(LIB)/mpp

# installation directories

$(LIB)/mpp:	$(LIB)
	sh -c "if test ! -d $(LIB)/mpp; then mkdir $(LIB)/mpp; else true; fi"

clean:
	rm -f *.[dimor] mpp *.bak

CLEAN:	clean
	rm -f Parser.m[di] Parser.Tab
