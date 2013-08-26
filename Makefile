CC=gcc
CFLAGS=-g -O0 -Wall -I/usr/local/include
LDFLAGS=-L/usr/local/lib -o
LIBS=-lm

## Output programs
LIBRARY=build/libcobra.a
ALL_PROGRAMS=$(LIBRARY)

## Output .o files
LIBRARY_OBS=\
src/benchmark.o\
src/cobra.o\
src/output.o

all: $(ALL_PROGRAMS)

$(LIBRARY): $(LIBRARY_OBS)
	ar rcs $@ $^

install:
	cp include/cobra.h /usr/local/include/cobra.h; cp build/libcobra.a /usr/local/lib/libcobra.a

clean:
	rm -f $(LIBRARY_OBS) $(ALL_PROGRAMS)

