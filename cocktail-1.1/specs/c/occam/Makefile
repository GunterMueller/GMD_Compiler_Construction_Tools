LIB	= $(HOME)/lib
INCDIR	= $(LIB)/include
CC	= cc
#
#	Makefile for occam recogniser - pjmp @ hrc 22/7/86
#

#
# This work is in the public domain.
# It was written by Peter Polkinghorne in 1986 & 1989 at
# GEC Hirst Research Centre, Wembley, England.
# No liability is accepted or warranty given by the Author,
# still less my employers.
#

CFLAGS=-O -I$(INCDIR)
LFLAGS=-c -b -d

all:		occam2 occam

occam:		occam.o occamlex.o
		$(CC) $(CFLAGS) occam.o occamlex.o $(LIB)/libreuse.a -o occam

occam.c:        occam.lalr
		lalr $(LFLAGS) occam.lalr;
		awk -f lex.awk < occam.lalr > lex.h
		mv Parser.c occam.c

occam2:		occam2.o occam2lex.o
		$(CC) $(CFLAGS) occam2.o occam2lex.o $(LIB)/libreuse.a -o occam2

occam2.c:       occam2.lalr
		lalr $(LFLAGS) occam2.lalr;
		awk -f lex.awk < occam2.lalr > lex2.h
		mv Parser.c occam2.c

try:		occam
		time occam < test1
		time occam < test2
		time occam < test3
		time occam < test4

clean:
	rm -f *.o occam2.c occam.c lex2.h lex.h Parser.h occam occam2

.SUFFIXES:	.c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c
