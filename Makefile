# Tests

test: test_hashmap test_rbtree

test_hashmap: hashmap
	gcc -o test_hashmap tests/test_hashmap.c hashmap.o
	./test_hashmap
	rm test_hashmap

test_rbtree: rbtree
	gcc -o test_rbtree tests/test_rbtree.c rbtree.o
	./test_rbtree
	rm test_rbtree

gnuplot: libs/gnuplot_i.c libs/gnuplot_i.h
	$(CC) $(CFLAGS) -c -o gnuplot_i.o libs/gnuplot_i.c
	
# Core

all: hashmap rbtree
	
hashmap:
	gcc -c -o hashmap.o src/hashmaps/hashmap.c

rbtree:
	gcc -c -o rbtree.o src/trees/rbtree.c	

clean:
	rm *.o
