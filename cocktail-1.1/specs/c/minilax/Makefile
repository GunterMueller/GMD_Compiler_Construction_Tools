LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

SOURCES	= Scanner.h Scanner.c Parser.h Parser.c Tree.h Tree.c \
	  Semantics.h Semantics.c Types.h Types.c Definitions.h Definitions.c \
	  ICode.h ICode.c ICodeInter.h ICodeInter.c minilax.c

OBJS	= minilax.o Scanner.o Parser.o Tree.o \
	  Types.o Definitions.o Semantics.o ICode.o ICodeInter.o

all:	minilax
	time minilax < in1
	time minilax < in5

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
	cg -cdimRDI0 minilax.cg;

Semantics.h Semantics.c:	minilax.cg
	cg -cDI0 minilax.cg;

Definitions.h Definitions.c Definitions.TS:	Definitions.cg
	cg -cdim4 Definitions.cg;

Tree.TS:	minilax.cg
	echo SELECT AbstractSyntax Output | cat - minilax.cg | cg -c4

Types.h Types.c:	Types.puma Tree.TS
	puma -cdipk Types.puma;

ICode.h ICode.c:	ICode.puma Tree.TS Definitions.TS
	puma -cdi ICode.puma;

Parser.o:	Parser.h Scanner.h Tree.h Types.h Definitions.h
Semantics.o:	Semantics.h Tree.h Definitions.h Types.h
Tree.o:		Tree.h
Definitions.o:	Definitions.h Tree.h
Types.o:	Tree.h Types.h
ICode.o:	Tree.h Types.h ICodeInter.h
minilax.o:	Scanner.h Parser.h Tree.h Semantics.h Definitions.h ICode.h ICodeInter.h Types.o

lint:	$(SOURCES)
	lint -I../../reuse/c -u *.c

test:	$(SOURCES)
	cg -cdimRDI09 minilax.cg;
	make minilax LIB=$(LIB)
	time minilax < in5
	wc Semantics.c
	size Semantics.o
	cg -cdimRDI9 minilax.cg;
	make minilax LIB=$(LIB)
	time minilax < in5
	wc Semantics.c
	size Semantics.o
	cg -cdimRDIL9 minilax.cg;
	make minilax LIB=$(LIB)
	time minilax < in5
	wc Semantics.c
	size Semantics.o

trace:	$(SOURCES)
	cg -cdimRwDI09	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI09T	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI09YZ	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI09X	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI09Y	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI09Z	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cdimRwDI9	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI9T	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI9YZ	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI9X	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI9Y	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cI9Z	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cdimRwDIL9	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cIL9T	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cIL9YZ	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cIL9X	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cIL9Y	minilax.cg; make minilax LIB=$(LIB); minilax < in1
	cg -cIL9Z	minilax.cg; make minilax LIB=$(LIB); minilax < in1

clean:
	rm -f Scanner.? Parser.? Tree.? Semantics.? Definitions.? Types.? ICode.? *.TS
	rm -f core _Debug minilax *Tab minilax.rex Parser.lalr Scanner.rpp yy*.w *.o

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
