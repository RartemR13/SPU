#pragma once

#include <assert.h>

typedef struct Stack_ {
	Stack_node* storage_;
	size_t capacity_, size_;
} Stack;

void StackInit(Stack*);
void StackPush(Stack*, int);
int StackPop(Stack*);
size_t StackSize(Stack*);
void StackClear(Stack*);