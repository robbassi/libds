/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <time.h>
#include <stdio.h>
#include "fixtures.h"
#include "../src/rbtree.h"

struct data {
	char* name;
	char* addr;
};

int my_comparator(void* ptr,void* ptr2) {
	int key1 = *(int*)ptr;
	int key2 = *(int*)ptr2;

	return key1-key2;
}

int main (int argc, char**argv) {
	rbtree* tree = rbtree_new(my_comparator);

	int size = 10000;
	test_entry* test_entries = get_test_data(size);
	int i;

	print_divider();

	printf("Red Black Tree[%d]\n", size);
	clock_t start = clock(), diff;
	for(i=0; i<size; i++) {
		rbtree_insert(tree, test_entries[i].key, &test_entries[i].data);
	}
	diff = clock() - start;
	printf("PUT: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		rbtree_find(tree, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("GET: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	print_divider();

	return 0;
}
