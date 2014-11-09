# Tests

test: test_hashmap test_hashhashmap

test_hashmap: hashmap
	gcc -o test_hashmap tests/test_hashmap.c hashmap.o
	./test_hashmap
	rm test_hashmap

test_hashhashmap: hashhashmap
	gcc -o test_hashhashmap tests/test_hashhashmap.c hashhashmap.o
	./test_hashhashmap
	rm test_hashhashmap
	
# Core

all: hashmap hashhashmap

hashhashmap:
	gcc -c -o hashhashmap.o src/hashhashmap.c
	
hashmap:
	gcc -c -o hashmap.o src/hashmap.c
	
clean:
	rm *.o

