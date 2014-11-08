/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "hashmap.h"


unsigned long myhash_string(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 4503;
	int c;

	while (c = *key++)
		hash = ((hash << 7) + hash) + c; /* hash * 33 + c */

	return hash;
}


int main (int argc, char**argv) {
	hashmap* map = hashmap_new(15);

	map->hash = hash_string;

	int v = 25;
	int v2 = 2667;

	// these two collide
	hashmap_put(map, "Rob", &v);
	hashmap_put(map, "Bob", &v2);

	hashmap_put(map, "Joe", &v2);

	//entry* joe = hashmap_get(map, "Bob");

	//printf("key: %s, value: %d\n", joe->key, *((int*)joe->data));
	hashmap_display(map);

	return 0;
}
