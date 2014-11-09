/*
 * test_hashhashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "fixtures.h"
#include "../src/hashhashmap.h"

void hashmap_display(hashmap* map) {
	int i;
	for (i = 0; i < map->size; i++) {
		entry* cursor = map->entries[i];
		printf("%d: \n", i);
		while (cursor != NULL) {
			printf("\tkey: %s, value: %d\n", cursor->key, *((int*)cursor->data));
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

	int v = 25;
	int v2 = 2667;

	int i;
	for(i=0; i<sizeof(test_entries)/sizeof(test_entry); i++) {
		hashhashmap_put(map, test_entries[i].key, test_entries[i].data);
	}

	printf("Printing hashhashmap:\n");
	hashhashmap_display(map);
	printf("\n");

	return 0;
}
