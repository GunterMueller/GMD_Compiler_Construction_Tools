BIN	= $(HOME)/bin
OPT	= -O
CC	= cc
REUSE	= ../../reuse/c
CFLAGS	= -w -I$(REUSE) $(OPT)
OBJS	= l2r.o Parser.o Scanner.o Errors.o StringBuf.o

# targets

l2r:	$(OBJS)
	$(CC) -o l2r $(CFLAGS) $(OBJS) $(REUSE)/libreuse.a

Scanner.c Scanner.h:	lex.rex
	rex -cd lex.rex;

Parser.c Parser.h:	lex.lalr
	lalr -b -c -d lex.lalr;

install:	l2r
	install -c $(BIN) l2r

lint:	l2r.c Parser.c Scanner.c Errors.c StringBuf.c
	lint -I$(REUSE) -b -u *.c

clean:
	rm -f core l2r *.o

CLEAN:	clean
	rm -f Pars* Scan*

# dependencies

l2r.o:		l2r.c Scanner.h Parser.h StringBuf.h
Errors.o:	Errors.c Errors.h Parser.h Scanner.h
Parser.o:	Parser.c Parser.h Scanner.h StringBuf.h
Scanner.o:	Scanner.c Scanner.h StringBuf.h
StringBuf.o:	StringBuf.c StringBuf.h

# print manual page

man:
	nroff -man l2r.1

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
