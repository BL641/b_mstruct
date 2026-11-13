
#include <stdlib.h>

static inline void makenmem(void* source, int value, size_t size) {
	if (source == NULL) return;

	unsigned char* byte = (unsigned char*)(source);

	size_t bidx = 0;
	while (bidx < size) {
		*(byte + bidx) = value;
		bidx++;
	}

	return;
}