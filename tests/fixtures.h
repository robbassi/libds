#ifndef TEST_FIXTURES_H_
#define TEST_FIXTURES_H_

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
	void* data;
} test_entry;

test_entry test_entries[10] = {
		{"Rob", "123"},
		{"Joe", "234"},
		{"Bob", "432"},
		{"John", "bla"},
		{"Mary", "342"},
		{"Jane", "23"},
		{"Tyrone", "aw23"},
		{"Bob", "323"},
		{"Sara", "1233"},
		{"Tim", "bla"}
};

#endif /* TEST_FIXTURES_H_ */
