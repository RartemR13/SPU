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

#define CREATEB(val)  \
	bool val = false;
//---------------------

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

#define GETBYTE(val) 									 \
	char temp_str[1000] = {0};							 \
	sscanf(cur_str, "%s%s", temp_str, temp_str);		 \
	char* label = GetLabel(temp_str);					 \
	val = LMapFind(&lmap, label);						 \
	free(label);
//--------------------------------------------------------

#define WRITECMD(val) \
	CREATEC(cmd_num)  \
	SET(cmd_num, val) \
					  \
	WRITE(cmd_num)
//---------------------

#define WRITEJUMP	 \
	CREATED(byte_num)\
	GETBYTE(byte_num)\
	WRITE(byte_num)  
//--------------------

#define CURBYTE(val) \
	val = cur_byte;
//--------------------

#define LASTBYTE(val) \
	val = buf_size;
//---------------------

#define JMP(val, cmd_sz) 				\
	cur_byte = val;						\
	cur_byte -= cmd_sz;
//---------------------------------------

#define GET(val)		\
	scanf("%d", &val);
//-----------------------

#define MUL(res_val, val1, val2) \
	res_val = val1 * val2;
//--------------------------------

#define SETCMP(val1, val2)						\
	cmp_flags[CMP_EQU] = (val1 == val2);		\
	cmp_flags[CMP_NEQU] = (val1 != val2);		\
	cmp_flags[CMP_LOWER] = (val1 > val2);		\
	cmp_flags[CMP_GREATER] = (val1 < val2);		\
	cmp_flags[CMP_ELOWER] = (val1 >= val2);		\
	cmp_flags[CMP_EGREATER] = (val1 <= val2);
//-----------------------------------------------

#define CHECKCMP(val, flag) \
	val = cmp_flags[flag]; 
//----------------------------

#define JUMPIF(val, cmd_sz, bval) \
	if (bval) {					  \
		JMP(val, cmd_sz)		  \
	}
//---------------------------------

#define GETSIZE 					\
	int val = StackSize(&spu_stack);\
	StackPush(&spu_stack, val);		
//-----------------------------------

