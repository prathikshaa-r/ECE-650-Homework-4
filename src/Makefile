CC=g++
CFLAGS=-O3 -Wall -pedantic
EXTRAFLAGS=-lpqxx -lpq

all: test

test: main.cpp exerciser.h exerciser.cpp query_funcs.h query_funcs.cpp database_setup.h database_setup.cpp
	$(CC) $(CFLAGS) -o test main.cpp exerciser.cpp query_funcs.cpp database_setup.cpp $(EXTRAFLAGS)

clean:
	rm -f *~ *.o test

clobber:
	rm -f *~ *.o
