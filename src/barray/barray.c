
#include "barray.h"

typedef enum {
	NULLERR = 1,
	MEMERR = 2,
	SIZEERR = 3
} errors;

struct _array {
	void* data;
	size_t sizetype;
	size_t count;
	size_t capacity;
};

array* array_init_core(size_t capacity, size_t sizetype) {
	if (capacity == 0 || sizetype == 0) return NULL;

	array* new_arr = (array*)malloc(sizeof(array)); if (new_arr == NULL) return NULL;	
	new_arr->data = malloc(capacity * sizetype);
	
	if (new_arr->data == NULL) {
		free(new_arr);
		return NULL;
	}

	new_arr->sizetype = sizetype;
	new_arr->capacity = capacity;
	new_arr->count = 0;

	return new_arr;
}

int array_append_core(array* const self, const void* const data) {
	if (self == NULL || data == NULL) {
		return NULLERR;
	}
	if (self->sizetype == 0 || self->capacity == 0) {
		return SIZEERR;
	}

	if (self->count >= self->capacity) {
		return SIZEERR;
	}


	uint8_t* byte = (uint8_t*)self->data + (self->count * self->sizetype);
	copy_data(byte, data, self->sizetype);
	
	self->count++;
	return 0;
}

void* array_at_core(const array* const self, size_t idx) {
	if (self == NULL || self->data == NULL || idx >= self->capacity || idx >= self->count) return NULL;
	uint8_t* byte = (uint8_t*)self->data;

	return (byte + (idx * self->sizetype));
}

void* array_begin_core(const array* const self) {
	if (self == NULL) return NULL;

	return self->data;
}

void* array_end_core(const array* const self) {
	if (self == NULL) return NULL;

	uint8_t* byte = (uint8_t*)(self->data) + (self->count * self->sizetype);
	return byte;
}

size_t array_size_core(const array* const self) {
	if (self == NULL) return 0;

	return self->count;
}

size_t array_msize_core(const array* const self) {
	if (self == NULL) return 0;

	return self->capacity;
}

int array_empty_core(const array* const self) {
	if (self == NULL) return NULLERR;
	
	return self->count == 0;
}

void array_fill_core(array* const self, int value) {
	if (self == NULL) return;

	makenmem(self->data, value, self->capacity * self->sizetype);
	self->count = self->capacity;
}

void array_zeroat_core(array* const self, size_t idx) {
	if (self == NULL) return;
	if (idx >= self->capacity || self->sizetype == 0) return;

	uint8_t* byte = (uint8_t*)self->data + (idx * self->sizetype);

	makenmem(byte, 0, self->sizetype);
	return;
}

void array_pop_core(array* const self) {
	if (self == NULL || self->count == 0) return;
	
	self->count--;
}

int array_remove_core(array* const self, size_t idx) {
	if (self == NULL || self->data == NULL) return NULLERR;
	if (idx >= self->count || self->count == 0) return SIZEERR;

	uint8_t* s = (uint8_t*)self->data;
	
	for (int i = idx; i < self->count - 1; i++) {
		copy_data((s + (i * self->sizetype)), (s + ((i + 1) * self->sizetype)), self->sizetype);
 	}

	self->count--;
}