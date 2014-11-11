/*
 * hashhashmap.c
 *
 *  Created on: Nov 8, 2014
 *  Author: Ramsey D'silva
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.c"
#include "hashhashmap.h"

hashhashmap* hashhashmap_new(int size, hash_function hash1, hash_function hash2) {
	hashhashmap* map = (hashhashmap*) malloc(sizeof(hashhashmap));
	map->hashmaps = (hashmap**) malloc(size*sizeof(hashmap));
	map->size = size;
	map->hash1 = hash1;
	map->hash2 = hash2;
	return map;
}

void hashhashmap_put(hashhashmap* map, char* key, void* value) {
	long hashCode = map->hash1(key);
	int idx = hashCode % map->size;

	hashmap* map2 = map->hashmaps[idx];
	if (map2 == NULL) {
		map2 = hashmap_new(map->size, map->hash2);
		map->hashmaps[idx] = map2;
	}
	hashmap_put(map2, key, value);
}


entry* hashhashmap_get(hashhashmap* map, char* key) {
	int hashCode = map->hash1(key);
	int idx = hashCode % map->size;
	hashmap* map2 = map->hashmaps[idx];
	if (map2) {
		return hashmap_get(map2, key);
	}
	return NULL;
}

void hashhashmap_delete(hashhashmap* map, char* key) {
	int hashCode = map->hash1(key);
	int idx = hashCode % map->size;
	hashmap* map2 = map->hashmaps[idx];
	if (map2) {
		hashmap_delete(map2, key);
	}
}
