#include <time.h>
#include <stdlib.h>

#ifndef TEST_FIXTURES_H_
#define TEST_FIXTURES_H_

void print_divider() {
	printf("-----------------------------------------\n");
}

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {
            int n;
        	for (n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

unsigned long hash1(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 5381;
	int c;

	while (c = *key++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}

unsigned long hash2(void* ptr) {
	unsigned char* key = (unsigned char*) ptr;
	unsigned long hash = 4503;
	int c;

	while (c = *key++)
		hash = ((hash << 7) + hash) + c; /* hash * 33 + c */

	return hash;
}

typedef struct test_entry {
	char* key;
	int data;
} test_entry;

test_entry* get_test_data(int size) {
	test_entry* test_entries = malloc(size * sizeof(test_entry));
	int i;
	srand(time(NULL));
	for (i=0; i<size; i++) {
		test_entries[i].key = randstring(5);
		test_entries[i].data = i;
	}
	return test_entries;
}

#endif /* TEST_FIXTURES_H_ */
