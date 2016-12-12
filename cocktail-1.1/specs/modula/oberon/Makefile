SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi \
	  ParserDrv.mi

ParserDrv:	$(SOURCES)
	echo p ParserDrv | mc

Scanner.rpp Parser.lalr:	oberon.pars
	cg -xzj oberon.pars;

oberon.rex:	oberon.scan Scanner.rpp
	rpp < oberon.scan > oberon.rex;

Scanner.md Scanner.mi:	oberon.rex
	rex -d oberon.rex;

Parser.md Parser.mi ParserDrv.mi:	Parser.lalr
	lalr -d -p Parser.lalr;

clean:
	rm -f Scanner.m? Parser.m? ParserDrv.mi Scanner.Tab Parser.Tab ParserDrv
	rm -f core *.[dimor] _Debug oberon.rex Parser.lalr Scanner.rpp *.bak
