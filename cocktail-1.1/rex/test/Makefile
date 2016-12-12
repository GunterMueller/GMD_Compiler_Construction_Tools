LIB	= $(HOME)/lib
MLIB	= ../../reuse/src
CFLAGS	= -I../../reuse/c
CC	= cc

# target language C

C:
	make clean ScannerDrv test LIB=$(LIB) CFLAGS="$(CFLAGS)" CC="$(CC)"

ScannerDrv:	ScannerDrv.o Scanner.o Source.o 
	$(CC) ScannerDrv.o Scanner.o Source.o -o ScannerDrv $(LIB)/libreuse.a

ScannerDrv.o:	Scanner.h 
Scanner.o:	Scanner.h Source.h 
Source.o:	Source.h

ScannerDrv.c Scanner.h Scanner.c Source.h Source.c:	modula.c
	rex -sdc1 modula.c;

# target language Modula using MOCKA (mc)

MC:	ScannerDrv.mi Scanner.md Scanner.mi Source.md Source.mi
	echo p ScannerDrv | mc -noindex -norange -d $(MLIB)
	make test

ScannerDrv.mi Scanner.md Scanner.mi Source.md Source.mi:	modula.m
	rex -sdm1 modula.m;

# target language Modula using SUN modula compiler (m2c)

M2C:	ScannerDrv.mod Scanner.def Scanner.mod Source.def Source.mod
	make -f MakefileM2C LIB=$(MLIB)
	make test

ScannerDrv.mod Scanner.def Scanner.mod Source.def Source.mod:	modula.m
	rex -sdm1 modula.m;

test:
	time ScannerDrv < in
	time ScannerDrv < in
	time ScannerDrv < in
	time ScannerDrv < in
	time ScannerDrv < in

lint:	ScannerDrv.c Scanner.c Source.c
	lint $(CFLAGS) -u ScannerDrv.c Scanner.c Source.c

clean:
	rm -f Scan* Source* core

.c.o:
	$(CC) $(CFLAGS) -c $*.c;
