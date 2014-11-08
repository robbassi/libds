/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <stdio.h>
#include "hashmap.h"


int main (int argc, char**argv) {
	hashmap* map = hashmap_new(15);
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
