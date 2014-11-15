/*
 * hashmap.c
 *
 *  Created on: Nov 7, 2014
 *  Author: Rob Bassi
 *  Author: Ramsey D'silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

entry* hashmap_get_entry(hashmap* map, void* key);

hashmap* hashmap_new(int size, hash_function hash) {
	hashmap* map = (hashmap*) malloc(sizeof(hashmap));
	map->entries = (entry**) malloc(size*sizeof(entry*));
	map->size = size;
	map->hash = hash;
	return map;
}

void hashmap_put(hashmap* map, void* key, void* value) {
	unsigned long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	entry* newEntry = (entry*) malloc(sizeof(entry));
	entry* last = map->entries[idx];
	newEntry->key = key;
	newEntry->data = value;
	newEntry->next = last;
	map->entries[idx] = newEntry;
}

void* hashmap_get(hashmap* map, void* key) {
	entry *e = hashmap_get_entry(map, key);
	if (e != NULL)
		return e->data;
	return NULL;
}

void hashmap_delete(hashmap* map, void* key) {
	unsigned long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	entry* result = hashmap_get_entry(map, key); // This also moves entry to head of list
	if (result) {
		map->entries[idx] = result->next;
		free(result);
	}
}

entry* hashmap_get_entry(hashmap* map, void* key) {
	unsigned long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	entry* cursor = map->entries[idx];
	entry* first = cursor;
	entry* prev;
	while (cursor != NULL) {
		if (strcmp(cursor->key, key) == 0) {
			if (cursor != first) { // move to front
				prev->next = cursor->next;
				cursor->next = first;
				map->entries[idx] = cursor;
			}
			return cursor;
		}
		prev = cursor;
		cursor = cursor->next;
	}
	return NULL;
}

