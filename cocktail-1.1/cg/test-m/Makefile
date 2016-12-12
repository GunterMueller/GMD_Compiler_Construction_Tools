test:	Main
	Main

Main:	Main.mi Tree.md Tree.mi
	echo p Main | mc -d ../../reuse/src

Tree.md Tree.mi: g.cg
	cg -a g.cg;

clean:
	rm -f Main Tree.* Main.[dimor] a aa aaa b bb core *.bak
