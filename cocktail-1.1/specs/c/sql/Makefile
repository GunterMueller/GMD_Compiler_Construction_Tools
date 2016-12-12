LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

ParserDrv:	ParserDrv.o Scanner.o Parser.o
	$(CC) $(CFLAGS) ParserDrv.o Scanner.o Parser.o $(LIB)/libreuse.a -o ParserDrv

Scanner.rpp Parser.lalr:	sql.pars
	cg -cxzj sql.pars;

sql.rex:	sql.scan Scanner.rpp
	rpp < sql.scan > sql.rex;

Scanner.h Scanner.c:	sql.rex
	rex -cd sql.rex;

Parser.h Parser.c ParserDrv.c:	Parser.lalr
	lalr -c -d -p -cs Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h
Scanner.o:	Scanner.h

lint: Scanner.c Parser.c ParserDrv.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f ParserDrv core *.[hco] _Debug sql.rex Parser.lalr Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
