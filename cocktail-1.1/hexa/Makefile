hexa:	btoh
	btoh < ../rex/src/Scanner.Tab > RAScanner.Tab
	btoh < ../rex/src/Parser.Tab > RAParser.Tab
	btoh < ../front/src/Scanner.Tab > PAScanner.Tab
	btoh < ../front/src/Parser.Tab > PAParser.Tab

btoh:	btoh.mi
	echo p btoh | mc -d ../reuse/src

endian:	endian.c
	cc endian.c -o endian

clean:
	rm -f core btoh htob *.[dimor] *Tab *.bak endian
