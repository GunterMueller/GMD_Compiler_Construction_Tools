LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

ParserDrv:	ParserDrv.o Scanner.o Parser.o
	$(CC) $(CFLAGS) ParserDrv.o Scanner.o Parser.o $(LIB)/libreuse.a -o ParserDrv

Scanner.rpp Parser.lalr:	oberon2.pars
	cg -cxzj oberon2.pars;

oberon2.rex:	oberon2.scan Scanner.rpp
	rpp < oberon2.scan > oberon2.rex;

Scanner.h Scanner.c:	oberon2.rex
	rex -cd oberon2.rex;

Parser.h Parser.c ParserDrv.c:	Parser.lalr
	lalr -c -d -p Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h
Scanner.o:	Scanner.h

lint: Scanner.c Parser.c ParserDrv.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f ParserDrv core *.[hco] _Debug oberon2.rex Parser.lalr Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
