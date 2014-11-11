/*
 * hashhashmap.h
 *
 *  Created on: Nov 8, 2014
 *      Author: Ramsey D'silva
 */

#ifndef SRC_HASHHASHMAP_H_
#define SRC_HASHHASHMAP_H_

#include "hashmap.h"

typedef struct {
	int size;
	hash_function hash1;
	hash_function hash2;
	hashmap **hashmaps;
} hashhashmap;

hashhashmap* hashhashmap_new(int size, hash_function hash1, hash_function hash2);
void hashhashmap_put(hashhashmap* map, char* key, void* value);
entry* hashhashmap_get(hashhashmap* map, char* key);
void hashhashmap_delete(hashhashmap* map, char*key);

#endif /* SRC_HASHHASHMAP_H_ */
