############################# Makefile ##########################
IDIR =../includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR =../lib

LIBS=-lm

_DEPS = analyzer.h convert.h list.h mount.h read.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

T_OBJ = tradutor.o analyzer.o convert.o list.o mount.o read.o
L_OBJ = ligador_ia32.o analyzer.o convert.o list.o mount.o read.o

TOBJ = $(patsubst %,$(ODIR)/%,$(T_OBJ))
LOBJ = $(patsubst %,$(ODIR)/%,$(L_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean tradutor ligador

tradutor: $(TOBJ)
	gcc -std=c99  -o $@ $^ $(CFLAGS) $(LIBS)

ligador: $(LOBJ)
	gcc -std=c99  -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ tradutor
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ ligador
