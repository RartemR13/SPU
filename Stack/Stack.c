#include "Stack.h"

void StackInit(Stack* stack) {
	assert(stack);

	stack.storage_ = calloc(32, sizeof(int));
	assert(stack.storage_);

	stack.capacity_ = 32;
	stack.size_ = 0;
}

void StackPush(Stack* stack, int val) {
	assert(stack);

	if (stack.size_ == stack.capacity_) {
		stack.capacity_ *= 2;
		stack.storage_ = realloc(stack.storage_, stack.capacity_*2);
		assert(stack.storage_);
	}

	stack.storage_[stack.size_++] = val;
}

int StackPop(Stack* stack) {
	assert(stack && stack.size_);
	return stack.storage_[stack.size_--];
}

size_t StackSize(Stack* stack) {
	assert(stack);

	return stack.size_;
}

void StackClear(Stack* stack) {
	assert(stack);

	free(stack.storage_);
	stack.capacity_ = 0;
	stack.size_ = 0;
	stack.storage_ = NULL;
}