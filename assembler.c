#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

size_t GetFileSize(FILE* file) {
	assert(fseek(file, 0L, SEEK_END) == 0);
	size_t file_size = ftell(file);
	assert(fseek(file, 0L, SEEK_SET) == 0);

	return file_size;
}

void ReadFile(FILE* file, char** buf, size_t* buf_size) {
	size_t file_size = GetFileSize(file);
	*buf = calloc(file_size+1, sizeof(char));
	assert(*buf);

	assert(fread(*buf, sizeof(char), file_size, file));

	buf[file_size] = '\0';
	*buf_size = file_size+1;
}

int main(int argc, char** argv) {

	FILE* asm_file = fopen(argv[1], "r");
	assert(asm_file);

	char* buf = NULL;
	size_t buf_size = 0;
	ReadFile(asm_file, &buf, &buf_size);
	fclose(asm_file);


	char* cur_str = buf;
	strtok(buf, "\n");
	while (cur_str) {
		printf("%s\n", cur_str);

		cur_str = strtok(NULL, "\n");
	}

	free(buf);
	return 0;
}