/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <time.h>
#include <stdio.h>
#include "fixtures.h"
#include "../src/trees/rbtree.h"

void rbnode_tojson_r(rbnode* node);

struct data {
	char* name;
	char* addr;
};

int my_comparator(void* ptr,void* ptr2) {
	int key1 = *(int*)ptr;
	int key2 = *(int*)ptr2;

	return key1-key2;
}

void rbnode_tojson(rbnode* node) {
	if (node != NULL) {
		printf("{ \"key\": %d, \"left\": ", *((int*)node->key));
		rbnode_tojson(node->link[0]);
		printf(" \"right\": ");
		rbnode_tojson_r(node->link[1]);
		printf("}, ");
	} else {
		printf("\"NULL\",");
	}
}

void rbnode_tojson_r(rbnode* node) {
	if (node != NULL) {
		printf("{ \"key\": %d, \"left\": ", *((int*)node->key));
		rbnode_tojson(node->link[0]);
		printf(" \"right\": ");
		rbnode_tojson_r(node->link[1]);
		printf("} ");
	} else {
		printf("\"NULL\"");
	}
}

int main (int argc, char**argv) {

	rbtree* tree = rbtree_new(my_comparator);
//
//	int key1 = 5;
//	int key2 = 4;
//	int key3 = 3;
//	int key4 = 6;
//	int key5 = 1;
//
//	struct data one = { .name="Rob", .addr="123 Some Street" };
//	struct data two = { .name="Joe", .addr="23462 Lakeshore" };
//	struct data three = { .name="Blah", .addr="xxx" };
//	struct data four = { .name="sdfasd", .addr="sdfasd" };

	int size = 10000;
	test_entry* test_entries = get_test_data(size);



	print_divider();

	printf("Red Black Tree[%d]\n", 5);
	clock_t start = clock(), diff;
	int i;
	for(i=0; i<size; i++) {
		rbtree_insert(tree, test_entries[i].key, &test_entries[i].data);
	}
	diff = clock() - start;
	printf("PUT: \t\t%fs\n", (double)diff/(double)CLOCKS_PER_SEC);
	for(i=0; i<size; i++) {
		test_entry* entry = rbtree_find(tree, test_entries[i].key);
		if (entry == NULL)
			puts("FAIL");
	}
	diff = clock() - diff;
	printf("GET: \t\t%fs\n", (double)diff/(double)CLOCKS_PER_SEC);

	print_divider();

	return 0;
}
