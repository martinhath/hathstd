CC=clang
FLAGS= -g  -Wall
LINK = -L$(shell pwd)/ -lhathstd -Wl,-rpath=$(shell pwd)/

DIRS = containers utils
LIB_SRC = $(shell find $(DIRS) -name "*.c" -not -name "tests.c") 
LIB_FLAGS = -fPIC

lib: 
	$(CC) $(FLAGS) $(LIB_FLAGS) $(LIB_SRC) -c
	gcc -shared -Wl,-soname,libhathstd.so -o libhathstd.so *.o

lib-debug:
	$(CC) $(FLAGS) $(LIB_FLAGS) -DDEBUG $(LIB_SRC) -c
	gcc -shared -Wl,-soname,libhathstd.so -o libhathstd.so *.o

test: lib-debug
	$(CC) $(FLAGS) $(LINK) -DDEBUG $(shell find . -name "tests.c") -o test

test-run: test
	@echo -e "\n############\n# Running: #\n############\n"
	@./test

install: lib
	sudo cp libhathstd.so /usr/lib/
	sudo cp hathstd.h /usr/include/

clean:
	rm *.o *.so test
