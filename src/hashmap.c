/*
 * hashmap.c
 *
 *  Created on: Nov 7, 2014
 *  Author: Rob Bassi
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
	char* key;
	void* data;
	struct entry* next;
} entry;

typedef struct {
	int size;
	entry **entries;
} hashmap;

unsigned long hash(unsigned char* key) {
	unsigned long hash = 5381;
	int c;

	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashmap* hashmap_new(int size) {
	hashmap* map = (hashmap*) malloc(sizeof(hashmap));
	map->entries = (entry**) malloc(size*sizeof(entry*));
	map->size = size;
	return map;
}

void hashmap_put(hashmap* map, char* key, void* value) {
	long hashCode = hash(key);
	int idx = hashCode % map->size;
	entry* newEntry = (entry*) malloc(sizeof(entry));

	newEntry->key = key;
	newEntry->data = value;
	newEntry->next = NULL;

	if (map->entries[idx] == NULL) {
		map->entries[idx] = newEntry;
	} else {
		entry* last = map->entries[idx];
		while (last->next != NULL)
			last = last->next;
		last->next = newEntry;
	}
}

entry* hashmap_get(hashmap* map, char* key) {
	int hashCode = hash(key);
	int idx = hashCode % map->size;

	if (map->entries[idx] != NULL) {
		if (map->entries[idx]->next == NULL) {
			return map->entries[idx];
		} else {
			entry* cursor = map->entries[idx];
			while (cursor != NULL) {
				if (strcmp(cursor->key, key) == 0)
					return cursor;
			}
		}
	}
	return NULL;
}

void hashmap_display(hashmap* map) {
	int i;
	for (i = 0; i < map->size; i++) {
		entry* cursor = map->entries[i];
		printf("%d: \n", i);
		while (cursor != NULL) {
			printf("\tkey: %s, value: %d\n", cursor->key, *((int*)cursor->data));
			cursor = cursor->next;
		}
	}
}

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
