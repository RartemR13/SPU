#pragma once

#define IN(val)													\
	{															\
		char cmd_name[MAX_CMD_SIZE] = {0};						\
		assert(sscanf(cur_str, "%s%d", cmd_name, &val) == 2);	\
	}
//---------------------------------------------------------------

#define CREATED(val) \
	int val = 0;
//-------------------

#define CREATEC(val)      \
	unsigned char val = 0;
//-------------------------

#define SET(val1, val2) \
	val1 = val2;
//-----------------------

#define WRITE(val) 									\
	assert(fwrite(&val, sizeof(val), 1, bin_file));
//---------------------------------------------------

#define READ(val)										  \
	val = *(int*)(buf + cur_byte + sizeof(unsigned char));
//---------------------------------------------------------

#define PUSH(val)			   \
	StackPush(&spu_stack, val);
//------------------------------

#define POP(val)			   \
	val = StackPop(&spu_stack);
//------------------------------

#define OUT(val)		\
	printf("%d\n", val);
//-----------------------

#define ADD(res_val, val1, val2) \
	res_val = val1 + val2;
//--------------------------------

#define SUB(res_val, val1, val2) \
	res_val = val2 - val1;
//--------------------------------
	