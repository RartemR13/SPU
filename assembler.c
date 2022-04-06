#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(int argc, char** argv) {

	FILE* file = fopen(argv[1], "r");
	assert(file);

	size_t buf_sz = 0;
	char* str = NULL;

	while (getline(&str, &buf_sz, file) != EOF) {
		printf("%s", str);
	}
	free(str);

	return 0;
}