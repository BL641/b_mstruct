
#ifndef __BVECTOR__H
#define __BVECTOR__H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _vector vector;

vector* vec_init_core(size_t typesize, size_t capacity); // Инициализация вектора
size_t vec_size_core(vector* self); // Взятие размера
size_t vec_cap_core(vector* self); // Взятие размерности 
int vec_push_core(vector* self, void* data); // пуш значения в конец
void* vec_at_core(vector* self, size_t idx); // взятие элемента
void vec_popb_core(vector* self); // удаление элемента в конце
void vec_free(vector* self); // освобождение памяти

// инициализация вектора 
#define bvector(NAME, TYPE)\
static inline vector* NAME##_init(size_t capacity){\
	return vec_init_core(sizeof(TYPE), capacity);\
}\
static inline int NAME##_push(vector* self, TYPE some){\
	return vec_push_core(self, &some);\
}\
static inline TYPE NAME##_at(vector* self, size_t idx){\
	TYPE* itcn = (TYPE*)vec_at_core(self, idx);\
	if (itcn == NULL) { \
		TYPE zero = { 0 };\
		return zero;\
	}\
	return *itcn;\
}\
static inline void NAME##_popb(vector* self){\
	return vec_popb_core(self);\
}\



#endif // !__BVECTOR__H

