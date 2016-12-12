LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CFLAGS	= -I$(INCDIR)
CC	= cc

test:	Main
	time Main

Main:	Main.o Tree.o
	$(CC) -o Main Main.o Tree.o $(LIB)/libreuse.a

Main.o:	Tree.h

Tree.h Tree.c: g.cg
	cg -ca g.cg;

lint:	Tree.c Main.c
	lint $(CFLAGS) -u Main.c Tree.c

clean:
	rm -f Main Tree.* Main.o yyTree.w a aa aaa b bb core

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
