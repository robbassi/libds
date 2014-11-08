# Tests

test: test_hashmap test_rbtree

test_hashmap: hashmap
	gcc -o test_hashmap test_hashmap.c hashmap.o
	./test_hashmap
	rm test_hashmap
	
test_rbtree: rbtree
	gcc -o test_rbtree test_rbtree.c rbtree.o
	./test_rbtree
	rm test_rbtree

# Core

all: hashmap rbtree

hashmap:
	gcc -c -o hashmap.o hashmap.c
	
rbtree:
	gcc -c -o rbtree.o rbtree.c
	
clean:
	rm *.o

