
#ifndef BPAIR_H
#define BPAIR_H

#include <stdlib.h>

#define bpair(NAME, TYPEF, TYPES)\
typedef struct{\
	TYPEF first;\
	TYPES second;\
} NAME;\
\
static inline NAME* NAME##_init(TYPEF first, TYPES second){\
	NAME* self = (NAME*)malloc(sizeof(NAME));\
	if (self == NULL) return NULL;\
	self->first = first;\
	self->second = second;\
	return self;\
}\
\
static inline void NAME##_swap(NAME* f, NAME* s){\
	if (f == NULL || s == NULL) return;\
	NAME temp = *f;\
	*f = *s;\
	*s = temp;\
	return;\
}\
static inline void NAME##_set(NAME* self, TYPEF first, TYPES second){\
	if (self == NULL) return;\
	self->first = first;\
	self->second = second;\
	return;\
}

#endif // !BPAIR_H

