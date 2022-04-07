#pragma once

enum SIZES {
	MAX_CMD_SIZE = 10,
	OUT_SZ = sizeof(unsigned char),
	IN_SZ = sizeof(unsigned char) + sizeof(int),
	ADD_SZ = sizeof(unsigned char),
	SUB_SZ = sizeof(unsigned char),
	JMP_SZ = sizeof(unsigned char) + sizeof(int),
	HLT_SZ = sizeof(unsigned char),
	GET_SZ = sizeof(unsigned char)
};

typedef enum ASM_COMMANDS_ {
	OUT,
	IN,
	ADD,
	SUB,
	JMP,
	HLT,
	GET,
	LABEL,
	INCORRECT
} ASM_COMMANDS;