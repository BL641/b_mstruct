
#ifndef __BVECTOR__H
#define __BVECTOR__H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _vector vector;

vector* vec_init_core(size_t typesize, size_t capacity); // Инициализация вектора
size_t vec_size_core(const vector* self); // Взятие размера
size_t vec_cap_core(const vector* self); // Взятие размерности 
int vec_push_core(vector* self, const void *const data); // пуш значения в конец
void* vec_at_core(const vector* self, size_t idx); // взятие элемента
void vec_popb_core(vector* self); // удаление элемента в конце
void vec_free(vector* self); // освобождение памяти
void* vec_begin_core(const vector* self); // получение указателя на первый элемент
void* vec_end_core(const vector* self); // Указатель на конец (ячейка после последнего элемента)
int vect_insert_core(vector* const self, size_t idx, const void *const data); // вставка элемента в вектор
int vect_erase_core(vector* const self, size_t idx); // удаление элемента в векторе
void vec_clear_core(vector* const self); // зануление счетчика данных вектора
int vec_reserve_core(vector* const self, size_t capacity); // резервирование нужного объёма данных
int vec_empty_core(const vector* const self); // проверка вектора на пустоту

// инициализация вектора 
#define bvector(NAME, TYPE)\
static inline vector* NAME##_init(size_t capacity){\
	return vec_init_core(sizeof(TYPE), capacity);\
}\
static inline int NAME##_push(vector* self, TYPE some){\
	return vec_push_core(self, &some);\
}\
static inline TYPE NAME##_at(const vector* self, size_t idx){\
	TYPE* itcn = (TYPE*)vec_at_core(self, idx);\
	if (itcn == NULL) { \
		TYPE zero = { 0 };\
		return zero;\
	}\
	return *itcn;\
}\
static inline void NAME##_popb(vector* self){\
	vec_popb_core(self);\
}\
static inline TYPE* NAME##_beg(const vector* self) {\
    return (TYPE*)vec_begin_core(self);\
}\
static inline TYPE* NAME##_end(const vector* self) {\
    return (TYPE*)vec_end_core(self);\
}\
static inline int NAME##_ins(vector* const self, size_t idx, TYPE data){\
	return vect_insert_core(self, idx, &data);\
}\
static inline int NAME##_ers(vector* const self, size_t idx){\
	return vect_erase_core(self, idx);\
}\
static inline void NAME##_clear(vector* const self) {\
	vec_clear_core(self);\
}\
static inline int NAME##_res(vector* const self, size_t capacity){\
	return vec_reserve_core(self, capacity);\
}\
static inline int NAME##_empty(const vector* const self){\
	return vec_empty_core(self);\
}

#endif // !__BVECTOR__H

