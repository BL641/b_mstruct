
#include "butils.h"

#define WORD_SIZE sizeof(uintptr_t)
#define WORD_MASK WORD_SIZE - 1

const char* bstrerr(int errc) {
	switch (errc) {
	case 0: return "All is good";
	case NULLERR: return "Nullptr error";
	case MEMERR: return "Mem alloc error";
	case SIZEERR: return "Size error";
	default: return "Unknown error";
	}
}

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

void copy_data(void* restrict dist, const void* restrict source, size_t cpy_size) {
	if (dist == NULL || source == NULL || cpy_size == 0) {
		return;
	}

	size_t size = cpy_size;
	
	uint8_t* d = (uint8_t*)dist;
	const uint8_t* s = (const uint8_t*)source;

	if (size < WORD_SIZE){
		while (size--) {
			*d = *s;
			d++; s++;
		}
		return;
	}

	while (((uintptr_t)d & WORD_MASK) != 0) {
		*d = *s;
		d++; s++;
		size--;
	}

	if (((uintptr_t)s & WORD_MASK) == 0) {
		while (size >= WORD_SIZE) {
			*(uint64_t*)d = *(const uint64_t*)s;
			d += 8; s += 8;
			size -= 8;
		}
		
		if (size >= 4) {
			*(uint32_t*)d = *(const uint32_t*)s;
			d += 4; s += 4;
			size -= 4;
		}

		if (size >= 2) {
			*(uint16_t*)d = *(const uint16_t*)s;
			d += 2; s += 2;
			size -= 2;
		}

		if (size >= 1) {
			*(uint8_t*)d = *(const uint8_t*)s;
			d++; s++;
			size--;
		}

		return;
	}

	while (size--) {
		*d = *s;
		d++; s++;
	}

	return;
}

void move_data(void* dist, const void* source, size_t cpy_size) {
	if (dist == NULL || source == NULL || cpy_size == 0 || dist == source) {
		return;
	}

	size_t size = cpy_size;

	uint8_t* d = (uint8_t*)dist;
	const uint8_t* s = (const uint8_t*)source;


	if (s + cpy_size <= d) {
		copy_data(d, s, size);
		return;
	}

	if (d < s) {
		copy_data(d, s, size);
		return;
	}

	d += size;
	s += size;
	while (size--) {
		d--; s--;
		*d = *s;
	}

	return;
}