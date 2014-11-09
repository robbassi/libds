/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "hashmap.h"
#include "hashhashmap.h"

unsigned long hash1(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 5381;
	int c;

	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

unsigned long hash2(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 4503;
	int c;

	while (c = *key++)
		hash = ((hash << 7) + hash) + c; /* hash * 33 + c */

	return hash;
}

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

int main (int argc, char**argv) {
	hashmap* map = hashmap_new(15, hash1);

	int v = 25;
	int v2 = 2667;

	hashmap_put(map, "Rob", &v);
	hashmap_put(map, "Bob", &v2);
	hashmap_put(map, "Joe", &v2);

	printf("Printing hashmap:\n");
	hashmap_display(map);
	printf("\n");

	hashhashmap* map2 = hashhashmap_new(15, hash1, hash2);

	hashhashmap_put(map2, "Rob", &v);
	hashhashmap_put(map2, "Bob", &v2);
	hashhashmap_put(map2, "Joe", &v2);

	printf("Printing hashhashmap:\n");
	hashhashmap_display(map2);
	printf("\n");

	return 0;
}
