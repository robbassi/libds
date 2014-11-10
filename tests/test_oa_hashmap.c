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
#include "../libs/gnuplot_i.h"

int main(int argc, char**argv) {
	int size = 10000;

	// gnuplot
    gnuplot_ctrl * h ;
    h = gnuplot_init();
    gnuplot_setstyle(h, "impulses");
    gnuplot_set_xlabel(h, "n");
    gnuplot_set_ylabel(h, "time");
	FILE * putplot = fopen("put.temp", "w");
	FILE * getplot = fopen("get.temp", "w");
	gnuplot_cmd(h, "set terminal dumb");

	oa_hashmap* map = oa_hashmap_new(size, hash1);
	test_entry* test_entries = get_test_data(size);
	int i;

	print_divider();
	printf("Open Addressing Hashmap[%d]\n", size);

	clock_t start = clock(), diff;
	clock_t putstart = clock();
	for(i=0; i<size; i++) {
		oa_hashmap_put(map, test_entries[i].key, &test_entries[i].data);
		fprintf(putplot, "%d %gs\n", i, (double)(clock() - putstart)/(double)CLOCKS_PER_SEC);
		putstart = clock();
	}
	diff = clock() - start;
	printf("PUT: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	start = clock();
	for(i=0; i<size; i++) {
		oa_hashmap_entry* e = oa_hashmap_get(map, test_entries[i].key);
		fprintf(getplot, "%d %gs\n", i, (double)(clock() - start)/(double)CLOCKS_PER_SEC);
		start = clock();
	}

	gnuplot_cmd(h, "plot '%s'", "put.temp");

	diff = clock() - diff;
	printf("GET: \t\t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	for(i=0; i<size; i++) {
		oa_hashmap_delete(map, test_entries[i].key);
	}

	gnuplot_cmd(h, "plot '%s'", "get.temp");

	diff = clock() - diff;
	printf("DELETE: \t%gs\n", (double)diff/(double)CLOCKS_PER_SEC);

	print_divider();

	fclose(putplot);
	fclose(getplot);

	gnuplot_close(h);

	remove("put.temp");
	remove("get.temp");

	return 0;
}
