SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi \
	  ParserDrv.mi

ParserDrv:	$(SOURCES)
	echo p ParserDrv | mc

Scanner.rpp Parser.lalr:	modula3.pars
	cg -xzj modula3.pars;

modula3.rex:	modula3.scan Scanner.rpp
	rpp < modula3.scan > modula3.rex;

Scanner.md Scanner.mi:	modula3.rex
	rex -d modula3.rex;

Parser.md Parser.mi ParserDrv.mi:	Parser.lalr
	lalr -d -p Parser.lalr;

clean:
	rm -f Scanner.m? Parser.m? ParserDrv.mi *.bak
	rm -f core *.[dimor] _Debug ParserDrv *Tab modula3.rex Parser.lalr Scanner.rpp
