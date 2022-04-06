#include <stdio.h>
#include <stdlib.h>

#include "Stack/Stack.h"
#include "commands.h"

#include "DSL.h"


size_t GetFileSize(FILE* file) {
	assert(file);

	assert(fseek(file, 0L, SEEK_END) == 0);
	size_t file_size = ftell(file);
	assert(fseek(file, 0L, SEEK_SET) == 0);

	return file_size;
}

void ReadFile(FILE* file, char** buf, size_t* buf_size) {
	assert(file && buf && buf_size);

	size_t file_size = GetFileSize(file);
	*buf = calloc(file_size+1, sizeof(char));
	assert(*buf);

	assert(fread(*buf, sizeof(char), file_size, file));

	(*buf)[file_size] = '\0';
	*buf_size = file_size+1;
}

int main(int argc, char** argv) {
//Check bin file.
	assert(argc == 2);

	FILE* bin_file = fopen(argv[1], "rb");

//Read bin file.
	char* buf = NULL;
	size_t buf_size = 0;
	ReadFile(bin_file, &buf, &buf_size);
	fclose(bin_file);
	buf_size--;

//Init spu stack
	Stack spu_stack = {0};
	StackInit(&spu_stack);

	ssize_t cur_byte = 0;
	while (cur_byte < (ssize_t)buf_size) {
		switch((unsigned char)buf[cur_byte]) {
#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
			case cmd_num:										\
				cmd_exec										\
				cur_byte += cmd_sz;								\
				break;
//---------------------------------------------------------------

#include "code_gen"
#undef DEF_CMD
		}
	}

	StackClear(&spu_stack);
	free(buf);
	return 0;
}