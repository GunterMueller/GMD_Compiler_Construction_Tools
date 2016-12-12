LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

ParserDrv:	ParserDrv.o Scanner.o Parser.o
	$(CC) $(CFLAGS) ParserDrv.o Scanner.o Parser.o $(LIB)/libreuse.a -o ParserDrv

Scanner.rpp Parser.lalr:	sather.pars
	cg -cxzj sather.pars;

sather.rex:	sather.scan Scanner.rpp
	rpp < sather.scan > sather.rex;

Scanner.h Scanner.c:	sather.rex
	rex -cd sather.rex;

Parser.h Parser.c ParserDrv.c:	Parser.lalr
	lalr -c -d -p Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h
Scanner.o:	Scanner.h

lint:	ParserDrv.c Parser.c Scanner.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f core *.[hco] _Debug ParserDrv sather.rex Parser.lalr Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
