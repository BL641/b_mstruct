

#ifndef __BARRAY__H
#define __BARRAY__H

#include <stdlib.h>
#include <stdint.h>

#include "butils.h"

typedef struct _array array;

array* array_init_core(size_t capacity, size_t sizetype); // инициализация статического массива
int array_append_core(array* const self, const void* const data); // добавления элемента в конец массива
void* array_at_core(const array* const self, size_t idx); // получение значения элемента массива
void* array_begin_core(const array* const self); // указатель на начало массива 
void* array_end_core(const array* const self); // указатель на конец массива
size_t array_size_core(const array* const self); // текущий размер массива
size_t array_msize_core(const array* const self); // максимально возможный размер массива
int array_empty_core(const array* const self); // проверка массива на пустоту
void array_fill_core(array* const self, int value); // выдача элементам массива какого либо значения
void array_zeroat_core(array* const self, size_t idx); // зануление определенного элемента
int array_remove_core(array* const self, size_t idx); // удаление элемента

#define barray(NAME, TYPE)\
static inline array* NAME##_init(size_t capacity){\
	return array_init_core(capacity, sizeof(TYPE));\
}\
static inline int NAME##_app(array* const self, TYPE data){\
	return array_append_core(self, &data);\
}\
static inline TYPE NAME##_at(const array* const self, size_t idx){\
	TYPE* itcn = (TYPE*)array_at_core(self, idx);\
	if (itcn == NULL) {\
		TYPE zero = {0};\
		return zero;\
	}\
	return *itcn;\
}\
static inline TYPE* NAME##_beg(const array* const self){\
	return (TYPE*)array_begin_core(self);\
}\
static inline TYPE* NAME##_end(const array* const self){\
	return (TYPE*)array_end_core(self);\
}\
static inline size_t NAME##_size(const array* const self){\
	return array_size_core(self);\
}\
static inline size_t NAME##_msize(const array* const self){\
	return array_msize_core(self);\
}\
static inline int NAME##_empty(const array* const self){\
	return array_empty_core(self);\
}\
static inline void NAME##_fill(array* const self, int value){\
	array_fill_core(self, value);\
}\
static inline void NAME##_z_at(array* const self, size_t idx){\
	array_zeroat_core(self, idx);\
}\
static inline int NAME##_remove(array* const self, size_t idx){\
	return array_remove_core(self, idx);\
}\

#endif 
