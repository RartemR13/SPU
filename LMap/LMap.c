#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "LMap.h"


void LMapInit(LMap *lmap) {
	assert(lmap);

	lmap->storage_ = calloc(32, sizeof(char*));
	lmap->storageVal_ = calloc(32, sizeof(size_t));
	lmap->capacity_ = 32;
	lmap->size_ = 0;
}

void LMapClear(LMap *lmap) {
	assert(lmap);

	for (int i = 0; i < lmap->size_; ++i)
		free(lmap->storage_[i]);

	free(lmap->storage_);
	free(lmap->storageVal_);
	lmap->capacity_ = 0;
	lmap->size_ = 0;
	lmap->storage_ = NULL;
	lmap->storageVal_ = NULL;
}

ssize_t LMapFind(LMap *lmap, char *str) {
	assert(lmap && str);
	ssize_t ret = -1;

	for (int i = 0; i < lmap->size_; ++i) {
		assert(lmap->storage_[i]);

		if (strcmp(lmap->storage_[i], str) == 0) {
			ret = lmap->storageVal_[i];
			break;
		}
	}

	return ret;
}

void LMapSet(LMap *lmap, char *str, size_t byte) {
	assert(lmap && str);

	if (lmap->size_ == lmap->capacity_) {
		lmap->capacity_ *= 2;
		lmap->storage_ = realloc(lmap->storage_, lmap->capacity_ * sizeof(char*));
		lmap->storageVal_ = realloc(lmap->storageVal_, lmap->capacity_ * sizeof(size_t));
		assert(lmap->storage_ && lmap->storageVal_);
	}

	lmap->storage_[lmap->size_] = str;
	lmap->storageVal_[lmap->size_++] = byte;
}

char* GetLabel(char* str) {
	assert(str);

	char* ret = NULL;
	size_t len = 0;

	for (int i = 0; ; ++i) {
		if ((str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9') ||
			str[i] == '_') 
		{
			len++;
			continue;
		}

		break;
	}

	ret = calloc(len+1, sizeof(char));
	assert(ret);

	memcpy(ret, str, len*sizeof(char));

	return ret;
}