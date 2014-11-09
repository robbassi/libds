/*
 * test_hashhashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <time.h>
#include <stdio.h>
#include "fixtures.h"
#include "../src/hashhashmap.h"

void hashmap_display(hashmap* map) {
	int i;
	for (i = 0; i < map->size; i++) {
		entry* cursor = map->entries[i];
		printf("%d: \n", i);
		while (cursor != NULL) {
			printf("\tkey: %s, value: %d\n", cursor->key, *(int*)cursor->data);
			cursor = cursor->next;
		}
	}
}

void hashhashmap_display(hashhashmap* map) {
	hashmap* map2;
	int i;
	for (i = 0; i < map->size; i++) {
		map2 = map->hashmaps[i];
		if (map2) {
			printf("%d:\n", i);
			hashmap_display(map2);
		} else {
			printf("%d: NULL\n", i);
		}
	}
}

int main(int argc, char**argv) {

	hashhashmap* map = hashhashmap_new(15, hash1, hash2);

	int size = 10000;
	int i;
	test_entry* test_entries = malloc(size * sizeof(test_entry));
	test_entries = get_test_data(size);

	print_divider();
	printf("Hashhashmap[%d]\n", size);

	clock_t start = clock(), diff;
	for(i=0; i<size; i++) {
		hashhashmap_put(map, test_entries[i].key, &test_entries[i].data);
	}
	diff = clock() - start;
	printf("PUT: \t\t%ldms\n", diff);

	for(i=0; i<size; i++) {
		hashhashmap_get(map, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("GET: \t\t%ldms\n", diff);

	for(i=0; i<size; i++) {
		hashhashmap_delete(map, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("DELETE: \t%ldms\n", diff);

	print_divider();

	return 0;
}
