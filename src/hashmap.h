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
void hashmap_put(hashmap* map, char* key, void* value);
entry* hashmap_get(hashmap* map, char* key);
void hashmap_display(hashmap* map);

#endif /* SRC_HASHMAP_H_ */
