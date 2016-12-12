BIN	= $(HOME)/bin
OPT	= -O
CC	= cc
REUSE	= ../../reuse/c
CFLAGS	= -w -I$(REUSE) $(OPT)
OBJS	= y2l.o Parser.o Scanner.o Tables.o

# targets

y2l:	$(OBJS)
	$(CC) -o y2l $(CFLAGS) $(OBJS) $(REUSE)/libreuse.a

Scanner.c Scanner.h:	yacc.rex
	rex -cd yacc.rex;

Parser.c Parser.h:	yacc.lalr
	lalr -b -c -d yacc.lalr;

install:	y2l
	install -c $(BIN) y2l

lint:	y2l.c Parser.c Scanner.c Tables.c
	lint -I$(REUSE) -b -u *.c

clean:
	rm -f core *.o y2l

CLEAN:	clean
	rm -f Scanner.* Parser.*

# dependencies

y2l.o:		y2l.c Scanner.h Parser.h Tables.h
Parser.o:	Parser.c Parser.h Scanner.h Tables.h
Scanner.o:	Scanner.c Scanner.h Tables.h
Tables.o:	Tables.c Tables.h

# print manual page

man:
	nroff -man y2l.1

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
