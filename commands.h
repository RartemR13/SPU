#pragma once

typedef enum CMP_FLAGS_ {
	CMP_EQU,
	CMP_NEQU,
	CMP_LOWER,
	CMP_GREATER,
	CMP_ELOWER,
	CMP_EGREATER,
	FLAGS_COUNT
} CMP_FLAG;

enum SIZES {
	MAX_CMD_SIZE = 10,
	OUT_SZ = sizeof(unsigned char),
	IN_SZ = sizeof(unsigned char) + sizeof(int),
	ADD_SZ = sizeof(unsigned char),
	SUB_SZ = sizeof(unsigned char),
	JMP_SZ = sizeof(unsigned char) + sizeof(int),
	HLT_SZ = sizeof(unsigned char),
	GET_SZ = sizeof(unsigned char),
	DEL_SZ = sizeof(unsigned char),
	CALL_SZ = sizeof(unsigned char) + sizeof(int),
	RET_SZ = sizeof(unsigned char) + sizeof(int),
	COPY_SZ = sizeof(unsigned char),
	MUL_SZ = sizeof(unsigned char),
	CMP_SZ = sizeof(unsigned char),
	JE_SZ = sizeof(unsigned char) + sizeof(int),
	JNE_SZ = sizeof(unsigned char) + sizeof(int),
	JL_SZ = sizeof(unsigned char) + sizeof(int),
	JG_SZ = sizeof(unsigned char) + sizeof(int),
	JLE_SZ = sizeof(unsigned char) + sizeof(int),
	JGE_SZ = sizeof(unsigned char) + sizeof(int),
	SIZE_SZ = sizeof(unsigned char),
	SWP_SZ = sizeof(unsigned char)
};

typedef enum ASM_COMMANDS_ {
	OUT,
	IN,
	ADD,
	SUB,
	JMP,
	HLT,
	GET,
	DEL,
	CALL,
	RET,
	COPY,
	MUL,
	CMP,
	JE,
	JNE,
	JL,
	JG,
	JLE,
	JGE,
	SIZE,
	SWP,
	LABEL,
	SPACE,
	COMMENT,
	INCORRECT
} ASM_COMMANDS;