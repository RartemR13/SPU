#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "commands.h"
#include "DSL.h"
#include "LMap/LMap.h"

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
	char temp_cmd[1000] = {0};
	int count_read = sscanf(str, "%s", temp_cmd);

#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
	if (strlen(temp_cmd) <= MAX_CMD_SIZE) {						\
		if (count_read == 1 && strcmp(temp_cmd, #cmd_name) == 0)\
			return cmd_num;										\
	}
//---------------------------------------------------------------
#include "code_gen"
#undef DEF_CMD

	return INCORRECT;
}

void SetJmpBytes(char* buf, size_t buf_size, LMap* lmap) {
	size_t cur_byte = 0;
	char* cur_str = buf;
	strtok(buf, "\n");
	while (cur_str) {
		char* label = strstr(cur_str, ":");
		if (label != NULL) {
			label = GetLabel(label+1);
			LMapSet(lmap, label, cur_byte);

			cur_str = strtok(NULL, "\n");
			continue;
		}
		switch(Parse(cur_str)) {
#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
			case cmd_num:										\
				cur_byte += cmd_sz;								\
				break;
//---------------------------------------------------------------
#include "code_gen"
#undef DEF_CMD
		}		

		cur_str = strtok(NULL, "\n");
	}

	for (int i = 0; i < buf_size-1; ++i)
		if (buf[i] == 0)
			buf[i] = '\n';
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

	LMap lmap = {0};
	LMapInit(&lmap);

	SetJmpBytes(buf, buf_size, &lmap);

//Open bin file.
	FILE* bin_file = fopen(argv[2], "wb");
	assert(bin_file);

	char* cur_str = buf;
	size_t cur_byte = 0;
	strtok(buf, "\n");
	while (cur_str) {
		switch(Parse(cur_str)) {
#define DEF_CMD(cmd_name, cmd_num, cmd_sz, cmd_trans, cmd_exec) \
			case cmd_num:										\
				cmd_trans										\
				cur_byte += cmd_sz;								\
				break;
//---------------------------------------------------------------
#include "code_gen"
#undef DEF_CMD

			case INCORRECT:
				printf("ERROR: Incorrect cmd: %s\n", cur_str);
		}		

		cur_str = strtok(NULL, "\n");
	}

	LMapClear(&lmap);

	free(buf);
	fclose(bin_file);
	return 0;
}