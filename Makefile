# Tests

test: test_hashmap test_rbtree test_hashhashmap

test_hashmap: hashmap
	gcc -o test_hashmap tests/test_hashmap.c hashmap.o
	./test_hashmap
	rm test_hashmap

test_rbtree: rbtree
	gcc -o test_rbtree tests/test_rbtree.c rbtree.o
	./test_rbtree
	rm test_rbtree
	
test_hashhashmap: hashhashmap
	gcc -o test_hashhashmap tests/test_hashhashmap.c hashhashmap.o
	./test_hashhashmap
	rm test_hashhashmap
	
# Core

all: hashmap rbtree hashhashmap
	
hashmap:
	gcc -c -o hashmap.o src/hashmap.c

rbtree:
	gcc -c -o rbtree.o src/rbtree.c	

hashhashmap:
	gcc -c -o hashhashmap.o src/hashhashmap.c
	
clean:
	rm *.o