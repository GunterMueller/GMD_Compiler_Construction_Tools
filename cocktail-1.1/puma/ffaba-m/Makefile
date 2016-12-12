all:	main
	time main

main:	main.mi Compiler.md Compiler.mi ProTest.md ProTest.mi
	echo p main | mc

ProTest.md ProTest.mi ProTest.TS: ffaba.ast
	cg -di4 ffaba.ast

Compiler.md Compiler.mi: ffaba.puma ProTest.TS
	puma -dip ffaba.puma

clean:
	rm -f core Compiler.* ProTest.* main.[mor] main
