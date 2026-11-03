
#ifndef __BARRAY__H
#define __BARRAY__H

#include <stdio.h>
#include <string.h>

#define barray(T, N)\
typedef struct {\
	T data[N];\
} array_##T##_##N##;\
\
static inline int apparr_##T##_##N##(array_##T##_##N* arr, int index, T new_data){\
	if (arr == NULL) return 2;\
	if (N <= index) return 3;\
	if (index < 0) return 4;\
	\
	\
	arr->data[index] = new_data;\
	\
}\
\
static inline T arat_##T##_##N##(array_##T##_##N* arr, int index){\
	if (arr == NULL || index < 0 || index >= N) {return (T){0};}\
	\
	\
	return arr->data[index]; \
	\
}\
static inline int arr_clear_##T##_##N##(array_##T##_##N* arr) {\
	if (arr == NULL) return 1;\
	memset(arr, 0, sizeof(arr->data));\
}\
static inline int arre_##T##_##N##(array_##T##_##N* arr, int index){\
	if (arr == NULL || index < 0 || index >= N) return 1;\
	arr->data[index] = 0;\
	\
	for (int i = index; i < N - 1; i++) {\
		arr->data[i] = arr->data[i + 1]; \
	}\
	\
	size_t cnt = N - 1;\
	arr->data[cnt] = 0;\
	return 0;\
}\
\
static inline size_t arsi_##T##(array_##T##_##N* arr){\
	if (arr == NULL) return 0;\
	return (size_t)N;\
}\


#endif 
