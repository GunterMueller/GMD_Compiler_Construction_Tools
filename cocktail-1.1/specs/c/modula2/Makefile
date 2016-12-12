LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

ParserDrv:	ParserDrv.o Scanner.o Parser.o
	$(CC) $(CFLAGS) ParserDrv.o Scanner.o Parser.o $(LIB)/libreuse.a -o ParserDrv

Scanner.rpp Parser.lalr:	modula.pars
	cg -cxzj modula.pars;

modula.rex:	modula.scan Scanner.rpp
	rpp < modula.scan > modula.rex;

Scanner.h Scanner.c:	modula.rex
	rex -cd modula.rex;

Parser.h Parser.c ParserDrv.c:	Parser.lalr
	lalr -c -d -p Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h
Scanner.o:	Scanner.h

lint:	ParserDrv.c Parser.c Scanner.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f core *.[hco] _Debug ParserDrv modula.rex Parser.lalr Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
