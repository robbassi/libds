/*
 * hashmap.h
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#ifndef SRC_HASHMAP_H_
#define SRC_HASHMAP_H_

#include "common.h"

typedef struct entry {
	char* key;
	void* data;
	struct entry* next;
} entry;

typedef struct {
	int size;
	hash_function hash;
	entry **entries;
} hashmap;

unsigned long hash_string(void* ptr);

hashmap* hashmap_new(int size, hash_function hash);
void hashmap_put(hashmap* map, char* key, void* value);
entry* hashmap_get(hashmap* map, char* key);
void hashmap_delete(hashmap* map, char*key);

#endif /* SRC_HASHMAP_H_ */
