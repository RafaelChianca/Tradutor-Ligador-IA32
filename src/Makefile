############################# Makefile ##########################
IDIR =../includes
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR =../lib

LIBS=-lm

_DEPS = analyzer.h convert.h list.h mount.h read.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = tradutor.o analyzer.o convert.o list.o mount.o read.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: clean tradutor

tradutor: $(OBJ)
	gcc -std=c99  -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ tradutor
