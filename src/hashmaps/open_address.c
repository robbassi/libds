/*
 * hashmap.c
 *
 *  Created on: Nov 7, 2014
 *  Author: Rob Bassi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "open_address.h"

oa_hashmap* oa_hashmap_new(int size, hash_function hash) {
	oa_hashmap* map = (oa_hashmap*) malloc(sizeof(oa_hashmap));
	map->entries = (oa_hashmap_entry**) malloc(size*sizeof(oa_hashmap_entry));
	map->size = size;
	map->hash = hash;
	map->retry = 0;
	return map;
}

void oa_hashmap_put(oa_hashmap* map, char* key, void* data) {
	long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	oa_hashmap_entry* newEntry = (oa_hashmap_entry*) malloc(sizeof(oa_hashmap_entry));
	newEntry->key = key;
	newEntry->data = data;

	oa_hashmap_entry* cursor = map->entries[idx];
	int tries = 0;
	int original_idx = idx-1;
	while (cursor != NULL && strcmp(cursor->key, DELETED) != 0) {

		if (idx == original_idx) {
			return; // no space, exit without put
		}

		idx++;
		tries++;
		if (idx == map->size) {
			idx = 0;
		}
		cursor = map->entries[idx];
	}

	map->entries[idx] = newEntry;
	if (tries > map->retry) {
		map->retry = tries;
	}
}

oa_hashmap_entry* oa_hashmap_get(oa_hashmap* map, char* key) {
	long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	int tries = 0;

	oa_hashmap_entry* cursor = map->entries[idx];
	while (cursor != NULL && strcmp(cursor->key, DELETED) != 0 && tries <= map->retry) {
		if (strcmp(cursor->key, key) == 0) {
			return cursor;
		}
		tries++;
		idx++;
		if (idx == map->size) {
			idx = 0;
		}
		cursor = map->entries[idx];
	}

	return NULL;
}

void oa_hashmap_delete(oa_hashmap* map, char* key) {
	long hashCode = map->hash(key);
	int idx = hashCode % map->size;
	oa_hashmap_entry* result = oa_hashmap_get(map, key);
	if (result != NULL) {
		result->key = DELETED;
	}
}
