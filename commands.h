#pragma once

enum SIZES {
	MAX_CMD_SIZE = 10,
	OUT_SZ = sizeof(unsigned char),
	IN_SZ = sizeof(unsigned char) + sizeof(int),
	ADD_SZ = sizeof(unsigned char),
	SUB_SZ = sizeof(unsigned char)
};

typedef enum ASM_COMMANDS_ {
	OUT,
	IN,
	ADD,
	SUB,
	INCORRECT
} ASM_COMMANDS;