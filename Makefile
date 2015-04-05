CC=clang
FLAGS= -g -O2 -Wall
LINK = -L$(shell pwd)/ -lhathstd -Wl,-rpath=$(shell pwd)/

LIB_SRC = hathstd.c
LIB_FLAGS = -fPIC

test: lib
	$(CC) $(FLAGS) $(LINK) tests.c -o test

test-run: test
	@./test

lib: 
	$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c -o lib.o;
	gcc -shared -Wl,-soname,libhathstd.so -o libhathstd.so lib.o;
	rm lib.o;

clean:
	rm *.o
	rm *.so
