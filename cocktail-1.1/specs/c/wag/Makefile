LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

SOURCES	= Scanner.h Scanner.c Parser.h Parser.c Tree.h Tree.c Semantics.h Semantics.c \
	  Types.h Types.c ICode.h ICode.c ICodeInter.h ICodeInter.c minilax.c

OBJS	= minilax.o Scanner.o Parser.o Tree.o Types.o Semantics.o ICode.o ICodeInter.o

all:	minilax
	time minilax < in1
	time minilax < in5

test:	minilax
	time minilax < in5
	wc Semantics.c
	size Semantics.o

minilax:	$(OBJS)
	$(CC) $(CFLAGS) -o minilax $(OBJS) $(LIB)/libreuse.a -lm

Scanner.rpp Parser.lalr:	minilax.pars
	cg -cxzj minilax.pars;

minilax.rex:	minilax.scan Scanner.rpp
	rpp < minilax.scan > minilax.rex;

Scanner.h Scanner.c:	minilax.rex
	rex -cd minilax.rex;

Parser.h Parser.c:	Parser.lalr
	lalr -c -d Parser.lalr;

Tree.h Tree.c:	minilax.cg
	cg -cdimRDIL9 minilax.cg;

Semantics.h Semantics.c:	minilax.cg
	cg -cDIL9 minilax.cg;

Tree.TS:	minilax.cg
	echo SELECT AbstractSyntax Output | cat - minilax.cg | cg -c4

Types.h Types.c:	Types.puma Tree.TS
	puma -cdipk Types.puma;

ICode.h ICode.c:	ICode.puma Tree.TS
	puma -cdi ICode.puma;

Scanner.o:	Scanner.h
Parser.o:	Parser.h Tree.h Types.h Scanner.h
Semantics.o:	Semantics.h Tree.h Types.h ICodeInter.h
Tree.o:		Tree.h Types.h
Types.o:	Types.h Tree.h
ICode.o:	ICode.h Tree.h Types.h ICodeInter.h
minilax.o:	Parser.h Tree.h Semantics.h Types.h ICode.h ICodeInter.h

lint:	$(SOURCES)
	lint $(CFLAGS) -u *.c

clean:
	rm -f Scanner.? Parser.? Tree.? Semantics.? Types.? ICode.? *.TS yy*.w *.o
	rm -f core _Debug minilax *Tab minilax.rex Parser.lalr Scanner.rpp

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
