/*
 * hashmap.h
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#ifndef SRC_OA_HASHMAP_H_
#define SRC_OA_HASHMAP_H_

#include "../common.h"

#define DELETED "DELETED"

typedef struct entry {
	char* key;
	void* data;
} oa_hashmap_entry;

typedef struct {
	int size;
	int retry;
	hash_function hash;
	oa_hashmap_entry** entries;
} oa_hashmap;

oa_hashmap* oa_hashmap_new(int size, hash_function hash);
void oa_hashmap_put(oa_hashmap* map, char* key, void* value);
oa_hashmap_entry* oa_hashmap_get(oa_hashmap* map, char* key);
void oa_hashmap_delete(oa_hashmap* map, char*key);

#endif /* SRC_OA_HASHMAP_H_ */
