
#include <stdlib.h>
#include <stdint.h>

void makenmem(void* source, int value, size_t size) {
	if (source == NULL) return;

	unsigned char* byte = (unsigned char*)(source);

	size_t bidx = 0;
	while (bidx < size) {
		*(byte + bidx) = value;
		bidx++;
	}

	return;
}

void copy_data(void* dist, const void* source, size_t cpy_size) {
	if (dist == NULL || source == NULL || cpy_size == 0) return;

	size_t size = cpy_size;

	uint8_t* d = (uint8_t*)dist;
	const uint8_t* s = (uint8_t*)source;

	while (size >= 8) {
		*((uint64_t*)d) = *((uint64_t*)s);
		d += 8; s += 8;
		size -= 8;
	}

	if (size >= 4) {
		*((uint32_t*)d) = *((uint32_t*)s);
		d += 4; s += 4;
		size -= 4;
	}

	if (size >= 2) {
		*((uint16_t*)d) = *((uint16_t*)s);
		d += 2; s += 2;
		size -= 2;
	}

	if (size >= 1) {
		*((uint8_t*)d) = *((uint8_t*)s);
		d += 1; s += 1;
		size -= 1;
	}

	return;
}