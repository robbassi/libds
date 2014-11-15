/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <time.h>
#include <stdio.h>
#include "fixtures.h"
#include "../src/hashmaps/hashmap.h"

void hashmap_display(hashmap* map) {
	int i;
	for (i = 0; i < map->size; i++) {
		entry* cursor = map->entries[i];

			printf("%d: \n", i);

		while (cursor != NULL) {
			printf("\tkey: %s, %d\n", (char*)cursor->key, *((int*)cursor->data));
			cursor = cursor->next;
		}
	}
}

int main(int argc, char**argv) {
	hashmap* map = hashmap_new(150, hash1);
	int size = 50000;
	test_entry* test_entries = get_test_data(size);
	int i;

	print_divider();
	printf("Hashmap[%d]\n", size);

	clock_t start = clock(), diff;
	for(i=0; i<size; i++) {
		hashmap_put(map, test_entries[i].key, &test_entries[i].data);
	}
	diff = clock() - start;
	printf("PUT: \t\t%fs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		hashmap_get(map, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("GET: \t\t%fs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		hashmap_delete(map, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("DELETE: \t%fs\n", (double)diff/(double)CLOCKS_PER_SEC);

	print_divider();

	return 0;
}
