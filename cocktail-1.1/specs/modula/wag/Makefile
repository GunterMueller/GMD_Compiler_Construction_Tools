SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi \
	  Tree.md Tree.mi Semantics.md Semantics.mi \
	  Types.md Types.mi ICode.md ICode.mi ICodeInter.md ICodeInter.mi minilax.mi

all:	minilax Scanner.Tab Parser.Tab
	time minilax < in1
	time minilax < in5

test:	minilax Scanner.Tab Parser.Tab
	time minilax < in5
	wc Semantics.mi
	size Semantics.o

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
	cg -dimRDIL9 minilax.cg;

Semantics.md Semantics.mi:	minilax.cg
	cg -DIL9 minilax.cg;

Tree.TS:	minilax.cg
	echo SELECT AbstractSyntax Output | cat - minilax.cg | cg -4

Types.md Types.mi:	Types.puma Tree.TS
	puma -dipk Types.puma;

ICode.md ICode.mi:	ICode.puma Tree.TS
	puma -di ICode.puma;

clean:
	rm -f Scanner.m? Parser.m? Tree.m? Semantics.m? Types.m? ICode.m? *.TS *.bak
	rm -f core *.[dimor] _Debug minilax *Tab minilax.rex Parser.lalr Scanner.rpp
