
#include "bvector.h"

typedef enum {
	NULLERR = 1,
	MEMERR = 2,
	SIZEERR = 3
} errors;

struct _vector {
	void* data;
	size_t count;
	size_t capacity;
	size_t sizetype;
};

static inline void copy_data(void* dist, const void* source, size_t size) {
	if (dist == NULL || source == NULL || size == 0) return;
	
	unsigned char* hptr_s = (unsigned char*)source;
	unsigned char* hptr_d = (unsigned char*)dist;
	
	size_t cnt = 0;
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

size_t vec_size_core(const vector* self) {
	if (self == NULL) return 0; 
	return self->count;
}

size_t vec_cap_core(const vector* self) {
	if (self == NULL) return 0; 
	return self->capacity;
}

static inline int vec_resize_core(vector* self) {
	if (self == NULL ) return NULLERR;
	if (self->data == 0 || self->capacity == 0) return SIZEERR;

	size_t new_sap = self->capacity * 2;

	unsigned char* new_data = (unsigned char*)malloc(self->sizetype * new_sap);
	if (new_data == NULL) {
		return MEMERR;
	}
	
	unsigned char* byte = (unsigned char*) self->data;
	
	copy_data(new_data, byte, self->sizetype * self->count);
	
	free(self->data);
	self->data = new_data;
	self->capacity = new_sap;

	return 0;
}

int vec_push_core(vector* self, const void *const data) {
	if (self == NULL || data == NULL ) return NULLERR;
	if (self->capacity == 0) return SIZEERR;

	if (self->count >= self->capacity) {
		int res = vec_resize_core(self);
		if (res != 0) {
			return res;
		}
	}

	unsigned char* byte = (unsigned char*)(self->data) + (self->sizetype * self->count);

	copy_data(byte, data, self->sizetype);

	self->count++;
	return 0;
}

void* vec_at_core(const vector* self, size_t idx) {
	if (self == NULL || idx >= self->count || self->capacity == 0) {
		return NULL;
	}

	unsigned char* byte = self->data;

	return (byte + (self->sizetype * idx));
}

void vec_popb_core(vector* self) {
	if (self == NULL || self->count == 0) { return; }
	self->count--;
}

void* vec_begin_core(const vector* self) {
	if (self == NULL || self->data == NULL || self->sizetype == 0 || self->capacity == 0) return NULL;

	return self->data;
}

void* vec_end_core(const vector* self) {
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