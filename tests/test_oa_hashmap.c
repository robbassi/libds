/*
 * test_hashmap.c
 *
 *  Created on: Nov 8, 2014
 *      Author: rob
 */

#include <time.h>
#include <stdio.h>
#include "fixtures.h"
#include "../src/hashmaps/open_address.h"

int main(int argc, char**argv) {
	int size = 10000;
	oa_hashmap* map = oa_hashmap_new(size, hash1);
	test_entry* test_entries = get_test_data(size);
	int i;

	print_divider();
	printf("Open Addressing Hashmap[%d]\n", size);

	clock_t start = clock(), diff;
	for(i=0; i<size; i++) {
		oa_hashmap_put(map, test_entries[i].key, &test_entries[i].data);
	}
	diff = clock() - start;
	printf("PUT: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		oa_hashmap_entry* e = oa_hashmap_get(map, test_entries[i].key);
		if (e == NULL) {
			printf("Couldnt get");
		}
	}

	diff = clock() - diff;
	printf("GET: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		oa_hashmap_delete(map, test_entries[i].key);
	}

	diff = clock() - diff;
	printf("DELETE: \t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	print_divider();

	return 0;
}
