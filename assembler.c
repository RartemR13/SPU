#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

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

ASM_COMMANDS Parse(char* str) {
	assert(str);

#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
	{															\
		char* cmd_pref = strstr(str, #cmd_name);				\
		if (cmd_pref && cmd_pref == str)						\
			return cmd_num;										\
	}
//---------------------------------------------------------------
#include "code_gen"
#undef DEF_CMD

	return INCORRECT;
}

int main(int argc, char** argv) {

//Check asm file.
	assert(argc == 3);

//Check extension.
	{
		char* extension = strstr(argv[1], ".asm");
		assert(extension && extension == argv[1] + strlen(argv[1]) - 4);
	}

//Open asm file.
	FILE* asm_file = fopen(argv[1], "r");
	assert(asm_file);

//Read asm file.
	char* buf = NULL;
	size_t buf_size = 0;
	ReadFile(asm_file, &buf, &buf_size);
	fclose(asm_file);

//Open bin file.
	FILE* bin_file = fopen(argv[2], "wb");
	assert(bin_file);

	char* cur_str = buf;
	strtok(buf, "\n");
	while (cur_str) {
		switch(Parse(cur_str)) {
#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
			case cmd_num:										\
				cmd_trans										\
				break;
//---------------------------------------------------------------
#include "code_gen"
#undef DEF_CMD

			case INCORRECT:
				printf("ERROR: Incorrect cmd.\n");
		}		

		cur_str = strtok(NULL, "\n");
	}

	free(buf);
	fclose(bin_file);
	return 0;
}