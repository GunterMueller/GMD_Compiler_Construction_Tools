LIB	= $(HOME)/lib
OPT	= -O
CC	= cc

                # C library (reuse)
REUSE	= ../../reuse/m2c

                # C libraries
CLIBS	= $(REUSE)/libreuse.a

                # options for C compiler
CFLAGS	= -w -I$(REUSE) $(OPT)

M2FLAGS	= -c

OBJS	= Actions.o Character.o Checks.o Errors.o Limits.o \
	  Listing.o Oper.o Pars.o Parser.o Path.o Rules.o Scanner.o \
	  SysError.o TokenTab.o Tokens.o WriteTok.o

libfront.a	: $(OBJS)
	ar uc libfront.a $(OBJS)
	ranlib libfront.a

install:	Scanner.Tab Parser.Tab ErrorTab libfront.a $(LIB)/lalr
	cp Scanner.Tab Parser.Tab ErrorTab $(LIB)/lalr
	chmod a+r $(LIB)/lalr/*Tab

# installation directories

$(LIB)/lalr:	$(LIB)
	sh -c "if test ! -d $(LIB)/lalr; then mkdir $(LIB)/lalr; else true; fi"

# swap all byte pairs of the files Scanner.Tab and Parser.Tab

bin.conv:
	dd conv=swab < Scanner.Tab > .Scanner.Tab; mv .Scanner.Tab Scanner.Tab
	dd conv=swab < Parser.Tab > .Parser.Tab; mv .Parser.Tab Parser.Tab


# HEAD

sources	: Actions.h
Actions.h	: TokenTab.h

sources	: Actions.c
Actions.o	: Actions.c Actions.h
Actions.o	: TokenTab.h
Actions.o	: WriteTok.h

sources	: Character.h

sources	: Character.c
Character.o	: Character.c Character.h

sources	: Checks.h

sources	: Checks.c
Checks.o	: Checks.c Checks.h
Checks.o	: SysError.h
Checks.o	: Errors.h

sources	: Errors.h

sources	: Errors.c
Errors.o	: Errors.c Errors.h
Errors.o	: Listing.h
Errors.o	: SysError.h
Errors.o	: TokenTab.h

sources	: Limits.h

sources	: Limits.c
Limits.o	: Limits.c Limits.h

sources	: Listing.h

sources	: Listing.c
Listing.o	: Listing.c Listing.h

sources	: Oper.h
Oper.h	: TokenTab.h

sources	: Oper.c
Oper.o	: Oper.c Oper.h
Oper.o	: TokenTab.h
Oper.o	: Errors.h

sources	: Pars.c
all	: Pars
Pars.o	: Pars.c
Pars.o	: WriteTok.h
Pars.o	: Character.h
Pars.o	: Path.h
Pars.o	: Checks.h
Pars.o	: Errors.h
Pars.o	: Parser.h
Pars.o	: Scanner.h
Pars.o	: TokenTab.h

sources	: Parser.h

sources	: Parser.c
Parser.o	: Parser.c Parser.h
Parser.o	: Scanner.h
Parser.o	: Errors.h
Parser.o	: Actions.h
Parser.o	: Errors.h
Parser.o	: Oper.h
Parser.o	: Scanner.h
Parser.o	: TokenTab.h
Parser.o	: Tokens.h
Parser.o	: Rules.h

sources	: Path.h

sources	: Path.c
Path.o	: Path.c Path.h

sources	: Rules.h
Rules.h	: TokenTab.h

sources	: Rules.c
Rules.o	: Rules.c Rules.h
Rules.o	: TokenTab.h
Rules.o	: Errors.h

sources	: Scanner.h
Scanner.h	: Rules.h

sources	: Scanner.c
Scanner.o	: Scanner.c Scanner.h
Scanner.o	: Checks.h
Scanner.o	: Limits.h
Scanner.o	: WriteTok.h
Scanner.o	: Errors.h

sources	: SysError.h

sources	: SysError.c
SysError.o	: SysError.c SysError.h
SysError.o	: Errors.h

sources	: TokenTab.h

sources	: TokenTab.c
TokenTab.o	: TokenTab.c TokenTab.h
TokenTab.o	: Errors.h

sources	: Tokens.h
Tokens.h	: TokenTab.h

sources	: Tokens.c
Tokens.o	: Tokens.c Tokens.h
Tokens.o	: TokenTab.h
Tokens.o	: TokenTab.h
Tokens.o	: Errors.h

sources	: WriteTok.h

sources	: WriteTok.c
WriteTok.o	: WriteTok.c WriteTok.h
WriteTok.o	: TokenTab.h

SYSTEM_.o	: SYSTEM_.c SYSTEM_.h

Pars	: $(SYSTEM)	\
	Pars.o	\
	TokenTab.o	\
	Errors.o	\
	SysError.o	\
	Listing.o	\
	Scanner.o	\
	WriteTok.o	\
	Limits.o	\
	Checks.o	\
	Rules.o	\
	Parser.o	\
	Tokens.o	\
	Oper.o	\
	Actions.o	\
	Path.o	\
	Character.o	\
;	$(CC) $(CFLAGS) -o Pars $(SYSTEM)	\
	Pars.o	\
	TokenTab.o	\
	Errors.o	\
	SysError.o	\
	Listing.o	\
	Scanner.o	\
	WriteTok.o	\
	Limits.o	\
	Checks.o	\
	Rules.o	\
	Parser.o	\
	Tokens.o	\
	Oper.o	\
	Actions.o	\
	Path.o	\
	Character.o	\
	$(CLIBS)

# TAIL

clean	:
	rm -f core *.o

CLEAN	:
	rm -f core *.o libfront.a

.SUFFIXES: .md .mi .h .c .o

.mi.c:
	mtc $(M2FLAGS) $*.mi;

.md.h:
	mtc $(M2FLAGS) $*.md;

.c.o:
	$(CC) $(CFLAGS) -c $*.c
