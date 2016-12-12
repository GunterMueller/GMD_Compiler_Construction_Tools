SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi \
	  Tree.md Tree.mi Semantics.md Semantics.mi \
	  Types.md Types.mi Definitions.md Definitions.mi \
	  ICode.md ICode.mi ICodeInter.md ICodeInter.mi minilax.mi

all:	minilax Scanner.Tab Parser.Tab
	time minilax < in1
	time minilax < in5

minilax:	$(SOURCES)
	echo p minilax | mc -d ../../reuse/src

Scanner.rpp Parser.lalr:	minilax.pars
	cg -xzj minilax.pars;

minilax.rex:	minilax.scan Scanner.rpp
	rpp < minilax.scan > minilax.rex;

Scanner.md Scanner.mi Scanner.Tab:	minilax.rex
	rex -d minilax.rex;

Parser.md Parser.mi Parser.Tab:	Parser.lalr
	lalr -d Parser.lalr;

Tree.md Tree.mi:	minilax.cg
	cg -dimRDI0 minilax.cg;

Semantics.md Semantics.mi:	minilax.cg
	cg -DI0 minilax.cg;

Definitions.md Definitions.mi Definitions.TS:	Definitions.cg
	cg -dim4 Definitions.cg;

Tree.TS:	minilax.cg
	echo SELECT AbstractSyntax Output | cat - minilax.cg | cg -4

Types.md Types.mi:	Types.puma Tree.TS
	puma -dipk Types.puma;

ICode.md ICode.mi:	ICode.puma Tree.TS Definitions.TS
	puma -di ICode.puma;

test:	$(SOURCES) Scanner.Tab Parser.Tab
	cg -dimRDI09 minilax.cg;
	make minilax
	time minilax < in5
	wc Semantics.mi
	size Semantics.o
	cg -dimRDI9 minilax.cg;
	make minilax
	time minilax < in5
	wc Semantics.mi
	size Semantics.o
	cg -dimRDIL9 minilax.cg;
	make minilax
	time minilax < in5
	wc Semantics.mi
	size Semantics.o

trace:	$(SOURCES) Scanner.Tab Parser.Tab
	cg -dimRwDI09	minilax.cg; make minilax; minilax < in1
	cg -I09T	minilax.cg; make minilax; minilax < in1
	cg -I09YZ	minilax.cg; make minilax; minilax < in1
	cg -I09X	minilax.cg; make minilax; minilax < in1
	cg -I09Y	minilax.cg; make minilax; minilax < in1
	cg -I09Z	minilax.cg; make minilax; minilax < in1
	cg -dimRwDI9	minilax.cg; make minilax; minilax < in1
	cg -I9T		minilax.cg; make minilax; minilax < in1
	cg -I9YZ	minilax.cg; make minilax; minilax < in1
	cg -I9X		minilax.cg; make minilax; minilax < in1
	cg -I9Y		minilax.cg; make minilax; minilax < in1
	cg -I9Z		minilax.cg; make minilax; minilax < in1
	cg -dimRwDIL9	minilax.cg; make minilax; minilax < in1
	cg -IL9T	minilax.cg; make minilax; minilax < in1
	cg -IL9YZ	minilax.cg; make minilax; minilax < in1
	cg -IL9X	minilax.cg; make minilax; minilax < in1
	cg -IL9Y	minilax.cg; make minilax; minilax < in1
	cg -IL9Z	minilax.cg; make minilax; minilax < in1

clean:
	rm -f Scanner.m? Parser.m? Tree.m? Semantics.m? Definitions.m? Types.m? ICode.m?
	rm -f core *.TS *.bak *.[dimor] _Debug minilax *Tab minilax.rex Parser.lalr Scanner.rpp
