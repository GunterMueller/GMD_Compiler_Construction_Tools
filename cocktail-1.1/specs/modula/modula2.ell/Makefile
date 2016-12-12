SOURCES = Parser.md Parser.mi ParserDrv.mi Scanner.md Scanner.mi ScannerDrv.mi 

ParserDrv ScannerDrv:	$(SOURCES)
	echo p ScannerDrv | mc
	echo p ParserDrv  | mc

Scanner.md Scanner.mi ScannerDrv.mi Scanner.Tab:	modula.rex
	rex -sd modula.rex;

Parser.md Parser.mi ParserDrv.mi Parser.Tab:	modula.ell
	ell -dip modula.ell;

clean:
	rm -f *Drv *Tab *.m? *.[dimor] _Debug core *.bak
