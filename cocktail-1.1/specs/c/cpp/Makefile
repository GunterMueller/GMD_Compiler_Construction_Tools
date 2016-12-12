LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

all:	ParserDrv cParserDrv

ParserDrv:	ParserDrv.o Scanner.o Parser.o
	$(CC) $(CFLAGS) ParserDrv.o Scanner.o Parser.o $(LIB)/libreuse.a -o ParserDrv

Scanner.rpp Parser.lalr:	cpp.pars
	cg -cxzj cpp.pars;

cpp.rex:	cpp.scan Scanner.rpp
	rpp < cpp.scan > cpp.rex;

Scanner.h Scanner.c:	cpp.rex
	rex -cd cpp.rex;

Parser.h Parser.c ParserDrv.c:	Parser.lalr
	lalr -c -d -p -cs 300 Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h
Scanner.o:	Scanner.h

cParserDrv:	cParserDrv.o cScannerSource.o cScanner.o cParser.o
	$(CC) $(CFLAGS) cParserDrv.o cScannerSource.o cScanner.o cParser.o $(LIB)/libreuse.a -o cParserDrv

cScanner.rpp cParser.lalr:	c.pars
	cg -cxzj c.pars;

c.rex:	cpp.scan cScanner.rpp
	(echo SCANNER cScanner; rpp cScanner.rpp < cpp.scan) | \
	sed -e 's/ Attribute/ cScanner_Attribute/'	\
	    -e 's/TokenPtr/cScanner_TokenPtr/'	\
	    -e 's/GetWord/cScanner_GetWord/'	> c.rex;

cScanner.h cScanner.c cScannerSource.h cScannerSource.c:	c.rex
	rex -csd c.rex;

cParser.h cParser.c cParserDrv.c:	cParser.lalr
	lalr -c -d -p -cs cParser.lalr;

cParserDrv.o:	cParser.h cScanner.h
cParser.o:	cParser.h cScanner.h
cScanner.o:	cScanner.h cScannerSource.h

lint: Scanner.c Parser.c ParserDrv.c cScannerSource.c cScanner.c cParser.c cParserDrv.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f core *.[hco] _Debug cParserDrv ParserDrv c.rex cpp.rex \
		cParser.lalr Parser.lalr cScanner.rpp Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
