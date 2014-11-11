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
	entry* last = map->entries[idx];
	newEntry->key = key;
	newEntry->data = value;
	newEntry->next = last;
	map->entries[idx] = newEntry;
}

entry* hashmap_get(hashmap* map, char* key) {
	long hashCode = map->hash(key);
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

void hashmap_delete(hashmap* map, char* key) {
	long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	entry* result = hashmap_get(map, key); // This also moves entry to head of list
	if (result) {
		map->entries[idx] = result->next;
		free(result);
	}
}
