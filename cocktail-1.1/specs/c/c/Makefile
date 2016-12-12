LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR) -g
CC	= cc
OBJS	= ParserDrv.o Scanner.o Parser.o Positions.o Errors.o hash.o name-space.o

ParserDrv:	$(OBJS)
	$(CC) $(CFLAGS) -o ParserDrv $(OBJS) $(LIB)/libreuse.a

Scanner.rpp Parser.lalr:	c.pars
	cg -cxzj c.pars;

c.rex:	c.scan Scanner.rpp
	rpp < c.scan > c.rex;

Scanner.h Scanner.c:	c.rex
	rex -cd c.rex;

Parser.h Parser.c Errors.h Errors.c ParserDrv.c:	Parser.lalr
	lalr -c -d -e -p -cs Parser.lalr;

ParserDrv.o:	Parser.h Scanner.h
Parser.o:	Parser.h Scanner.h Errors.h
Scanner.o:	Scanner.h
Errors.o:	Errors.h Positions.h
Positions.o:	Positions.h

lint: Scanner.c Parser.c ParserDrv.c
	lint $(CFLAGS) -b -u *.c

clean:
	rm -f ParserDrv core *.o _Debug Parser.[hc] Scanner.[hc] Errors.[hc] \
		c.rex Parser.lalr Scanner.rpp ParserDrv.c

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
