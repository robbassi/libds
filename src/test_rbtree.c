/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "rbtree.h"

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

	int key1 = 5;
	int key2 = 4;
	int key3 = 3;
	int key4 = 6;
	int key5 = 1;

	struct data one = { .name="Rob", .addr="123 Some Street" };
	struct data two = { .name="Joe", .addr="23462 Lakeshore" };
	struct data three = { .name="Blah", .addr="xxx" };
	struct data four = { .name="sdfasd", .addr="sdfasd" };


	puts("insert 6");
	rbtree_insert(tree, &key4, &four);
	puts("insert 1");
	rbtree_insert(tree, &key5, &three);
	puts("insert 3");
	rbtree_insert(tree, &key3, &three);
	puts("insert 5");
	rbtree_insert(tree, &key1, &one);
	puts("insert 4");
	rbtree_insert(tree, &key2, &two);

	struct data* d = (struct data*) rbtree_find(tree, &key4);

	if (d != NULL)
		printf("Found: {name:%s, addr:%s}\n", d->name, d->addr);
	else
		puts("Not found");

	rbnode_tojson(tree->root);

	return 0;
}
