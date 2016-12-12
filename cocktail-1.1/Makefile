# *************************************************************************
# *                                                                       *
# *  Makefile for                                                         *
# *                                                                       *
# *  Compiler Construction Tool Box                                       *
# *  ==============================                                       *
# *                                                                       *
# *  Copyright (c) 1989, 1990, 1991, 1992 by                              *
# *                                                                       *
# *  Gesellschaft fuer Mathematik und Datenverarbeitung                   *
# *  (German National Research Center for Computer Science)               *
# *  Forschungsstelle fuer Programmstrukturen                             *
# *  an der Universitaet Karlsruhe                                        *
# *                                                                       *
# *  All rights reserved. GMD assumes no responsibility for the use       *
# *  or reliability of its software.                                      *
# *                                                                       *
# *************************************************************************

# Choose a suitable C compiler
CC	= cc

# Choose optimizer flags for the C compiler
OPT	= -Ae

# Choose a suitable Modula compiler
# MC or M2C
MC	= M2C     # was MC - Ade

# BSD needs this
MAKE	= make

ME=/opt/cocktail
# The place to install the binaries
BIN	= $(ME)/bin

# The libraries go there
LIB	= $(ME)/lib

# Directory for man pages
MANDIR	= $(ME)/man

# Where to put include files for reuse
INCDIR	= $(LIB)/include

# The following targets are legal:
# PCS10
# PCS20
# SUN (also valid for DECstations and VAX)
TARGET	= SUN

# For PCS10 you must define
# OPT = "-DPCS10"

# Choose the source language:
LANGUAGE = c
# LANGUAGE = modula

# ****************************************************************
# *	DON'T CHANGE ANYTHING BELOW THIS LINE !
# ****************************************************************

MFLAGS	= BIN=$(BIN) LIB=$(LIB) CC=$(CC) OPT=$(OPT) MC=$(MC)

CTARGETS = \
	reuselib \
	c_reuse \
	c_common \
	c_rex \
	c_front \
	c_bnf \
	c_ell \
	c_lalr \
	c_l2r \
	c_y2l \
	c_r2l \
	c_rpp \
	c_cg \
	c_puma \
	c_estra

MTARGETS = \
	reuselib \
	m_reuse \
	m_common \
	m_rex \
	m_front \
	m_bnf \
	m_ell \
	m_lalr \
	c_l2r \
	c_y2l \
	m_r2l \
	m_rpp \
	m_cg \
	m_puma \
	m_mpp \
	m_estra

all:	$(LANGUAGE)

install:	install$(LANGUAGE)

reuselib:
	@echo; echo "Making public reuse library"
	cd reuse/c; $(MAKE) $(MFLAGS) TARGET=$(TARGET)

c:	$(CTARGETS)

c_reuse:
	@echo; echo "Making local reuse library"
	cd reuse/m2c; $(MAKE) $(MFLAGS)
c_common:
	@echo; echo "Making common"
	cd common/m2c; $(MAKE) $(MFLAGS)
c_rex:
	@echo; echo "Making rex"
	cd rex/m2c; $(MAKE) $(MFLAGS)
c_front:
	@echo; echo "Making front"
	cd front/m2c; $(MAKE) $(MFLAGS)
c_bnf:
	@echo; echo "Making bnf"
	cd bnf/m2c; $(MAKE) $(MFLAGS)
c_ell:
	@echo; echo "Making ell"
	cd ell/m2c; $(MAKE) $(MFLAGS)
c_lalr:
	@echo; echo "Making lalr"
	cd lalr/m2c; $(MAKE) $(MFLAGS)
c_l2r:
	@echo; echo "Making l2r"
	cd l2r/src; $(MAKE) $(MFLAGS)
c_y2l:
	@echo; echo "Making y2l"
	cd y2l/src; $(MAKE) $(MFLAGS)
c_r2l:
	@echo; echo "Making r2l"
	cd r2l/m2c; $(MAKE) $(MFLAGS)
c_rpp:
	@echo; echo "Making rpp"
	cd rpp/m2c; $(MAKE) $(MFLAGS)
c_cg:
	@echo; echo "Making cg"
	cd cg/m2c; $(MAKE) $(MFLAGS)
c_puma:
	@echo; echo "Making puma"
	cd puma/m2c; $(MAKE) $(MFLAGS)
c_estra:
	@echo; echo "Making estra"
	cd estra/m2c; $(MAKE) $(MFLAGS)

installc:	c_reuse c_common
	sh -c "if test ! -d $(BIN); then mkdir -p $(BIN); else true; fi"
	sh -c "if test ! -d $(LIB); then mkdir -p $(LIB); else true; fi"
	sh -c "if test ! -d $(MANDIR); then mkdir -p $(MANDIR); else true; fi"
	sh -c "if test ! -d $(INCDIR); then mkdir -p $(INCDIR); else true; fi"
	cd reuse/c	; $(MAKE) install $(MFLAGS) TARGET=$(TARGET) INCDIR=$(INCDIR)
	cd rex/m2c	; $(MAKE) install $(MFLAGS)
	cd front/m2c	; $(MAKE) install $(MFLAGS)
	cd bnf/m2c	; $(MAKE) install $(MFLAGS)
	cd ell/m2c	; $(MAKE) install $(MFLAGS)
	cd lalr/m2c	; $(MAKE) install $(MFLAGS)
	cd front/doc	; $(MAKE) install $(MFLAGS)
	cd l2r/src	; $(MAKE) install $(MFLAGS)
	cd y2l/src	; $(MAKE) install $(MFLAGS)
	cd r2l/m2c	; $(MAKE) install $(MFLAGS)
	cd rpp/m2c	; $(MAKE) install $(MFLAGS)
	cd cg/m2c	; $(MAKE) install $(MFLAGS)
	cd puma/m2c	; $(MAKE) install $(MFLAGS)
	cd estra/m2c	; $(MAKE) install $(MFLAGS)
	cd man; cp * $(MANDIR); chmod a+r $(MANDIR)/*.1


modula:	$(MTARGETS)

m_reuse:
	@echo; echo "Making local reuse library"
	cd reuse/src; $(MAKE) $(MFLAGS)
m_common:
	@echo; echo "Making common"
	cd common/src; $(MAKE) $(MFLAGS)
m_rex:
	@echo; echo "Making rex"
	cd rex/src; $(MAKE) $(MFLAGS)
m_front:
	@echo; echo "Making front"
	cd front/src; $(MAKE) $(MFLAGS)
m_bnf:
	@echo; echo "Making bnf"
	cd bnf/src; $(MAKE) $(MFLAGS)
m_ell:
	@echo; echo "Making ell"
	cd ell/src; $(MAKE) $(MFLAGS)
m_lalr:
	@echo; echo "Making lalr"
	cd lalr/src; $(MAKE) $(MFLAGS)
m_r2l:
	@echo; echo "Making r2l"
	cd r2l/src; $(MAKE) $(MFLAGS)
m_rpp:
	@echo; echo "Making rpp"
	cd rpp/src; $(MAKE) $(MFLAGS)
m_cg:
	@echo; echo "Making cg"
	cd cg/src; $(MAKE) $(MFLAGS)
m_puma:
	@echo; echo "Making puma"
	cd puma/src; $(MAKE) $(MFLAGS)
m_mpp:
	@echo; echo "Making mpp"
	cd mpp/src; $(MAKE) $(MFLAGS)
m_estra:
	@echo; echo "Making estra"
	cd estra/src; $(MAKE) $(MFLAGS)

installmodula:	m_reuse m_common
	sh -c "if test ! -d $(BIN); then mkdir $(BIN); else true; fi"
	sh -c "if test ! -d $(LIB); then mkdir $(LIB); else true; fi"
	sh -c "if test ! -d $(MANDIR); then mkdir $(MANDIR); else true; fi"
	sh -c "if test ! -d $(INCDIR); then mkdir $(INCDIR); else true; fi"
	cd reuse/c	; $(MAKE) install $(MFLAGS) TARGET=$(TARGET) INCDIR=$(INCDIR)
	cd rex/src	; $(MAKE) install $(MFLAGS)
	cd front/src	; $(MAKE) install $(MFLAGS)
	cd bnf/src	; $(MAKE) install $(MFLAGS)
	cd ell/src	; $(MAKE) install $(MFLAGS)
	cd lalr/src	; $(MAKE) install $(MFLAGS)
	cd front/doc	; $(MAKE) install $(MFLAGS)
	cd l2r/src	; $(MAKE) install $(MFLAGS)
	cd y2l/src	; $(MAKE) install $(MFLAGS)
	cd r2l/src	; $(MAKE) install $(MFLAGS)
	cd rpp/src	; $(MAKE) install $(MFLAGS)
	cd cg/src	; $(MAKE) install $(MFLAGS)
	cd puma/src	; $(MAKE) install $(MFLAGS)
	cd mpp/src	; $(MAKE) install $(MFLAGS)
	cd estra/src	; $(MAKE) install $(MFLAGS)
	cd man; cp * $(MANDIR); chmod a+r $(MANDIR)/*.1

endian:
	cd hexa		; $(MAKE) endian; endian

bin.conv:
	-cd cg/m2c	; $(MAKE) bin.conv
	-cd cg/src	; $(MAKE) bin.conv
	-cd ell/m2c	; $(MAKE) bin.conv
	-cd ell/src	; $(MAKE) bin.conv
	-cd estra/m2c	; $(MAKE) bin.conv
	-cd front/m2c	; $(MAKE) bin.conv
	-cd front/src	; $(MAKE) bin.conv
	-cd puma/m2c	; $(MAKE) bin.conv
	-cd puma/src	; $(MAKE) bin.conv
	-cd r2l/m2c	; $(MAKE) bin.conv
	-cd rex/m2c	; $(MAKE) bin.conv
	-cd rex/src	; $(MAKE) bin.conv
	-cd rpp/m2c	; $(MAKE) bin.conv

test:
	-cd specs/c/ada			; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/c			; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/c++			; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/modula2		; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/modula2.ell		; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/sather		; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/sql			; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/oberon2		; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR)
	-cd specs/c/minilax		; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR) minilax
	-cd specs/c/wag			; $(MAKE) -i LIB=$(LIB) INCDIR=$(INCDIR) minilax
	-cd specs/modula/ada		; $(MAKE) -i
	-cd specs/modula/modula2	; $(MAKE) -i
	-cd specs/modula/modula2.ell	; $(MAKE) -i
	-cd specs/modula/modula3	; $(MAKE) -i
	-cd specs/modula/oberon		; $(MAKE) -i
	-cd specs/modula/pascal		; $(MAKE) -i
	-cd specs/modula/minilax	; $(MAKE) -i minilax
	-cd specs/modula/wag		; $(MAKE) -i minilax

clean:
	-cd reuse/c		; rm -f *.o *Drv
	-cd reuse/src		; rm -f *Drv.[dimor] *Drv.sym *Drv Main.[dimor] Main t *.bak
	-cd common/src		; rm -f *.[dimor]
	-cd rex/src		; rm -f rexId* *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug rex
	-cd rex/test		; rm -f Scan* Source*
	-cd front/src		; rm -f lalrId* *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug Pars
	-cd bnf/src		; rm -f core *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug
	-cd lalr/src		; rm -f core *.[dimor] *.def *.mod *.sym ERRORS LISTING _Debug
	-cd ell/src		; rm -f core ERRORS LISTING *.[dimor] ell convert
	-cd l2r/src		; rm -f core l2r *.o
	-cd y2l/src		; rm -f core *.o y2l
	-cd r2l/src		; rm -f core *.[dimor] ERRORS LISTING _Debug r2
	-cd rpp/src		; rm -f *.[dimor] rpp
	-cd cg/src		; rm -f cgId* _Debug core *.[dior] [A-SU-Za-z]*.m
	-cd puma/src		; rm -f pumaId* _Debug core *.[dior] [A-SU-Za-z]*.m Tree*.m
	-cd mpp/src		; rm -f *.[dimor] mpp
	-cd estra/src		; rm -f core *.[dimor] ERRORS LISTING _Debug
	-cd reuse/m2c		; rm -f core *.o
	-cd common/m2c		; rm -f core *.o
	-cd rex/m2c		; rm -f core *.o
	-cd front/m2c		; rm -f core *.o
	-cd bnf/m2c		; rm -f core *.o
	-cd lalr/m2c		; rm -f core *.o
	-cd ell/m2c		; rm -f core *.o convert
	-cd r2l/m2c		; rm -f core *.o
	-cd rpp/m2c		; rm -f core *.o
	-cd cg/m2c		; rm -f core *.o
	-cd puma/m2c		; rm -f core *.o
	-cd estra/m2c		; rm -f core *.o
	-cd specs/c/ada		; rm -f core *.
	-cd specs/c/c		; rm -f core *.
	-cd specs/c/c++		; rm -f core *.
	-cd specs/c/modula2	; rm -f core *.
	-cd specs/c/modula2.ell	; rm -f core *.
	-cd specs/c/sather	; rm -f core *.
	-cd specs/c/sql		; rm -f core *.
	-cd specs/c/oberon2	; rm -f core *.
	-cd specs/c/minilax	; rm -f core *.
	-cd specs/c/wag		; rm -f core *.
	-cd specs/modula/ada	; rm -f core *.
	-cd specs/modula/modula2; rm -f core *.
	-cd specs/modula/modula2.ell	; rm -f core *.
	-cd specs/modula/modula3; rm -f core *.
	-cd specs/modula/oberon	; rm -f core *.
	-cd specs/modula/pascal	; rm -f core *.
	-cd specs/modula/minilax; rm -f core *.
	-cd specs/modula/wag	; rm -f core *.
#
