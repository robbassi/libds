/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "fixtures.h"
#include "../src/hashmap.h"

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

int main(int argc, char**argv) {
	hashmap* map = hashmap_new(15, hash1);

	int i;
	for(i=0; i<sizeof(test_entries)/sizeof(test_entry); i++) {
		hashmap_put(map, test_entries[i].key, test_entries[i].data);
	}

	printf("Printing hashmap:\n");
	hashmap_display(map);
	printf("\n");

	return 0;
}
