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

	puts("insert 5");
	rbtree_insert(tree, &key1, &one);
	puts("insert 4");
	rbtree_insert(tree, &key2, &two);
	puts("insert 3");
	rbtree_insert(tree, &key3, &three);
	puts("insert 6");
	rbtree_insert(tree, &key4, &two);
	puts("insert 1");
	rbtree_insert(tree, &key5, &three);
	struct data* d = (struct data*) rbtree_find(tree, &key3);

	if (d != NULL)
		printf("Found: {name:%s, addr:%s}\n", d->name, d->addr);
	else
		puts("Not found");
	return 0;
}
