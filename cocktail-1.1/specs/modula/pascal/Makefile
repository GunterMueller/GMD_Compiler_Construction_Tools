SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi \
	  ParserDrv.mi

ParserDrv:	$(SOURCES)
	echo p ParserDrv | mc

Scanner.rpp Parser.lalr:	pascal.pars
	cg -xzj pascal.pars;

pascal.rex:	pascal.scan Scanner.rpp
	rpp < pascal.scan > pascal.rex;

Scanner.md Scanner.mi:	pascal.rex
	rex -d pascal.rex;

Parser.md Parser.mi ParserDrv.mi:	Parser.lalr
	lalr -d -p Parser.lalr;

clean:
	rm -f Scanner.m? Parser.m? ParserDrv.mi Scanner.Tab Parser.Tab ParserDrv
	rm -f core *.[dimor] _Debug pascal.rex Parser.lalr Scanner.rpp *.bak
