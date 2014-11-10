# Tests

test: test_hashmap test_rbtree test_hashhashmap test_oa_hashmap

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

gnuplot: libs/gnuplot_i.c libs/gnuplot_i.h
	$(CC) $(CFLAGS) -c -o gnuplot_i.o libs/gnuplot_i.c

test_oa_hashmap: oa_hashmap gnuplot
	gcc -o test_oa_hashmap tests/test_oa_hashmap.c oa_hashmap.o gnuplot_i.o
	./test_oa_hashmap
	rm test_oa_hashmap
	
# Core

all: hashmap rbtree hashhashmap oa_hashmap
	
hashmap:
	gcc -c -o hashmap.o src/hashmap.c

rbtree:
	gcc -c -o rbtree.o src/rbtree.c	

hashhashmap:
	gcc -c -o hashhashmap.o src/hashhashmap.c

oa_hashmap:
	gcc -c -o oa_hashmap.o src/hashmaps/open_address.c
	
clean:
	rm *.o
