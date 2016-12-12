SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi ParserDrv.mi

try:	ParserDrv
	ParserDrv < Parser.mi

ParserDrv:	$(SOURCES)
	echo p ParserDrv | mc

Scanner.rpp Parser.lalr:	modula.pars
	cg -xzj modula.pars;

modula.rex:	modula.scan Scanner.rpp
	rpp < modula.scan > modula.rex;

Scanner.md Scanner.mi:	modula.rex
	rex -d modula.rex;

Parser.md Parser.mi ParserDrv.mi:	Parser.lalr
	lalr -d -p Parser.lalr;

clean:
	rm -f Scanner.m? Parser.m? ParserDrv.mi *.bak
	rm -f core *.[dimor] _Debug ParserDrv *Tab modula.rex Parser.lalr Scanner.rpp
