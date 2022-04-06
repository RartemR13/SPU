#pragma once

#include <sys/types.h>

typedef struct LMap_ {
	char** storage_;
	size_t* storageVal_;

	size_t capacity_, size_;
} LMap;

void LMapInit(LMap*);
void LMapClear(LMap*);

ssize_t LMapFind(LMap*, char*);
void LMapSet(LMap*, char*, size_t);

char* GetLabel(char*);
