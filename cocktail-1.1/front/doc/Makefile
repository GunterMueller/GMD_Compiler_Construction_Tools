# $Id: Makefile,v 2.5 1992/02/04 13:53:34 grosch rel $

LIB	= $(HOME)/lib

install:	bnf.cat lalr.cat bnf.syn lalr.syn $(LIB)/lalr
	install -c $(LIB)/lalr bnf.cat
	install -c $(LIB)/lalr lalr.cat
	install -c $(LIB)/lalr bnf.syn
	install -c $(LIB)/lalr lalr.syn

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"

bnf.cat:	bnf.1
	nroff -man < bnf.1 | col > bnf.cat

lalr.cat:	lalr.1
	nroff -man < lalr.1 | col > lalr.cat

print:
	troff -man bnf.1
	troff -man lalr.1

clean:
	rm -f bnf.cat lalr.cat
