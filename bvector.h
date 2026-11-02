
#ifndef __BVECTOR__H
#define __BVECTOR__H


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define bvector(T) \
typedef struct { \
    T* data; \
    size_t capacity; \
    size_t count; \
} vector_##T; \
\
static inline vector_##T* vector_##T##_init(size_t capacity) { \
    if (capacity == 0) return 0;\
    vector_##T* new_vect = (vector_##T*)malloc(sizeof(vector_##T)); \
    if (new_vect == NULL) return NULL; \
    \
    new_vect->capacity = capacity; \
    new_vect->data = (T*)malloc(sizeof(T) * new_vect->capacity); \
    \
    if (new_vect->data == NULL){ \
        free(new_vect); \
        return NULL;\
    }                               \
    new_vect->count = 0; \
    return new_vect; \
} \
\
static inline size_t vector_##T##_size(vector_##T* vector){ \
    if (vector == NULL) return 0; \
    return vector->count;\
} \
\
static inline void v_##T##_resize(vector_##T* vector){\
    if (vector == NULL){\
        return;   \
    }\
    vector->capacity *= 2;   \
    \
    T* new_data_ptr = (T*)malloc(sizeof(T) * vector->capacity);\
    if (new_data_ptr == NULL) return; \
    \
    for (size_t i = 0; i < vector->count; i++){\
        new_data_ptr[i] = vector->data[i]; \
    }\
    \
    free(vector->data);\
    vector->data = new_data_ptr; \
}\
\
static inline void v_##T##_pback(vector_##T* vector, T data){ \
    if (vector == NULL){ \
        return;\
    }\
    if (vector->data == NULL) { \
        return; \
    } \
    \
    if (vector->count >= vector->capacity - 1) { \
       v_##T##_resize(vector); \
    } \
    vector->data[vector->count] = data; \
    (vector->count)++; \
} \
static inline void v_##T##_pop(vector_##T* vector){\
    if (vector == NULL){\
        return;\
    }\
    vector->count--;\
    vector->data[vector->count] = 0;\
}\
\
void v_##T##_copy(vector_##T* dist, vector_##T* source){\
    if (dist == NULL || source == NULL) return;\
    \
    if (dist->capacity == 0){ \
        dist->capacity = 1;\
        dist->data = (T*)malloc(sizeof(T) * dist->capacity);\
    }\
    while (dist->capacity < source->count){\
        v_##T##_resize(dist);\
    }\
    \
    for (int i = 0; i < source->count; i++){\
        *(dist->data + i) = *(source->data + i);\
    }\
    \
    \
    dist->count = source->count;\
}\
static inline void v_##T##_free(vector_##T* vector){\
    if (vector == NULL) return;\
    free(vector->data);\
    free(vector);\
    return;\
}\
static inline T v_##T##_at(const vector_##T* vector, size_t index){ \
    if (vector == NULL || index >= vector->count) {\
        return (T){0}; \
    }\
    return  vector->data[index];\
}\
static inline size_t vector_##T##_cap(const vector_##T* vector){\
    if (vector == NULL) return -1;\
    return vector->capacity;\
}\
\

#endif // !__BVECTOR__H

