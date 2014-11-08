/*
 * hashmap.c
 *
 *  Created on: Nov 7, 2014
 *  Author: Rob Bassi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

unsigned long hash_string(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 5381;
	int c;

	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashmap* hashmap_new(int size, hash_function hash) {
	hashmap* map = (hashmap*) malloc(sizeof(hashmap));
	map->entries = (entry**) malloc(size*sizeof(entry*));
	map->size = size;
	map->hash = hash;
	return map;
}

void hashmap_put(hashmap* map, char* key, void* value) {
	long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	entry* newEntry = (entry*) malloc(sizeof(entry));

	newEntry->key = key;
	newEntry->data = value;
	newEntry->next = NULL;

	if (map->entries[idx] == NULL) {
		map->entries[idx] = newEntry;
	} else {
		entry* last = map->entries[idx];
		while (last->next != NULL)
			last = last->next;
		last->next = newEntry;
	}
}

entry* hashmap_get(hashmap* map, char* key) {
	int hashCode = map->hash(key);
	int idx = hashCode % map->size;

	if (map->entries[idx] != NULL) {
		if (map->entries[idx]->next == NULL) {
			return map->entries[idx];
		} else {
			entry* cursor = map->entries[idx];
			while (cursor != NULL) {
				if (strcmp(cursor->key, key) == 0)
					return cursor;
			}
		}
	}
	return NULL;
}
