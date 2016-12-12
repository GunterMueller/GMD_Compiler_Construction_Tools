SOURCES	= Scanner.md Scanner.mi Parser.md Parser.mi ParserDrv.mi

ParserDrv:	$(SOURCES)
	echo p ParserDrv | mc

Scanner.rpp Parser.lalr:	ada.pars
	cg -xzj ada.pars;

ada.rex:	ada.scan Scanner.rpp
	rpp < ada.scan > ada.rex;

Scanner.md Scanner.mi:	ada.rex
	rex -d ada.rex;

Parser.md Parser.mi ParserDrv.mi:	Parser.lalr
	lalr -d -p -cs Parser.lalr;

clean:
	rm -f Scanner.m? Parser.m? ParserDrv.mi Scanner.Tab Parser.Tab ParserDrv
	rm -f core *.[dimor] _Debug ada.rex Parser.lalr Scanner.rpp *.bak
