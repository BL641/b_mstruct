
#include "bvector.h"

struct _vector {
	void* data;
	size_t count;
	size_t capacity;
	size_t sizetype;
};

static inline void makenmem(void* source, int value, size_t size) {
	if (source == NULL) return;

	unsigned char* byte = (unsigned char*)(source);

	int bidx = 0;
	while (bidx < size) { 
		*(byte + bidx) = value;
		bidx++;
	}

	return;
}

static inline void copy_data(void* dist, void* source, size_t size) {
	if (dist == NULL || source == NULL || size == 0) return;
	
	unsigned char* hptr_s = (unsigned char*)source;
	unsigned char* hptr_d = (unsigned char*)dist;
	
	int cnt = 0;
	while (cnt < size) {
		*(hptr_d + cnt) = *(hptr_s + cnt);
		cnt++;
	}
	
	return;
}

vector* vec_init_core(size_t sizetype, size_t capacity) {
	if (capacity == 0) return NULL;
	vector* new_vec = (vector*)malloc(sizeof(vector)); if (new_vec == NULL) return NULL;

	new_vec->data = malloc(sizetype * capacity);
	if (new_vec->data == NULL) {
		free(new_vec);
		return NULL;
	}

	new_vec->count = 0;
	new_vec->capacity = capacity;
	new_vec->sizetype = sizetype;

	return new_vec;
}

size_t vec_size_core(vector* self) {
	if (self == NULL) return -1;
	if (self->data == NULL) return -2;
	if (self->count < 0 || self->capacity < 0) return -3;

	return self->count;
}

size_t vec_cap_core(vector* self) {
	if (self == NULL) return -1;
	if (self->data == NULL) return -2;
	if (self->count < 0 || self->capacity < 0) return -3;

	return self->capacity;
}

static inline void vec_resize_core(vector* self) {
	if (self == NULL || self->data == 0 || self->capacity == 0) return;

	size_t new_sap = self->capacity * 2;

	unsigned char* new_data = (unsigned char*)malloc(self->sizetype * new_sap);
	if (new_data == NULL) {
		return;
	}

	makenmem(new_data, 0, self->sizetype * new_sap);
	
	unsigned char* byte = (unsigned char*) self->data;
	
	for (int i = 0; i < self->count; i++) {
		*(new_data + (i * self->sizetype)) = *(byte + (i * self->sizetype));
	}
	
	free(self->data);
	self->data = new_data;
	self->capacity = new_sap;
}

int vec_push_core(vector* self, void* data) {
	if (self == NULL || data == NULL || self->capacity == 0) return 1;

	if (self->count == self->capacity - 1) {
		vec_resize_core(self);
	}

	unsigned char* byte = (unsigned char*)(self->data) + (self->sizetype * self->count);

	copy_data(byte, data, self->sizetype);

	self->count++;
	return 0;
}

void* vec_at_core(vector* self, size_t idx) {
	if (self == NULL || idx >= self->count || self->capacity == 0) {
		return 0;
	}

	unsigned char* byte = self->data;

	return (byte + (self->sizetype * idx));
}

void vec_popb_core(vector* self) {
	if (self == NULL || self->data == NULL) {
		return;
	}
	else if (self->capacity == 0 || self->sizetype == 0 || self->count == 0) {
		return;
	}

	unsigned char* byte = (unsigned char*)self->data;

	makenmem((byte + (self->sizetype * (self->count - 1))), 0, self->sizetype);
	
	self->count--;
}

void* vec_begin_core(vector* self) {
	if (self == NULL || self->data == NULL || self->sizetype == 0 || self->capacity == 0) return NULL;

	return self->data;
}

void* vec_end_core(vector* self) {
	if (self == NULL || self->data == NULL || self->sizetype == 0 || self->capacity == 0) return NULL;
	unsigned char* byte = self->data;

	return (byte + (self->sizetype * self->count));
}

void vec_free(vector* self) {
	if (self == NULL) return;
	free(self->data);
	free(self);
	return;
}