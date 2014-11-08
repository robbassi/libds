# Tests

test: test_hashmap

test_hashmap: hashmap
	gcc -o test_hashmap test_hashmap.c hashmap.o
	./test_hashmap
	rm test_hashmap

# Core

all: hashmap

hashmap:
	gcc -c -o hashmap.o hashmap.c
	
clean:
	rm *.o

