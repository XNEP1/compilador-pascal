/* Vetores Genericos auto expansivos em C
 * Por Bruno Krugel
 * Clone de uma idea de Henrique Colini
 */

// Você pode acessar os valores por VEC_T.data[i], mas não pode nem adicionar nem remover assim.
// A adição e remoção são feitas similar a uma pilha.

#pragma once

#include <assert.h>

#define DEF_VEC(VEC_T, T)                  \
    typedef struct VEC_T {                 \
        int size;                          \
        int capacity;                      \
        T *data;                           \
    } VEC_T;                               \
    VEC_T VEC_T##_new(int capacity);       \
    void VEC_T##_destroy(VEC_T *vec);      \
    void VEC_T##_push(VEC_T *vec, T data); \
    T VEC_T##_pop(VEC_T *vec);             \
    T VEC_T##_top(VEC_T *vec);             

#define IMPL_VEC(VEC_T, T)                                      \
    VEC_T VEC_T##_new(int capacity) {                           \
        assert(capacity > 0);                                   \
        VEC_T new_vec;                                          \
        new_vec.size = 0;                                       \
        new_vec.capacity = capacity;                            \
        new_vec.data = (T *)malloc(capacity * sizeof(T));       \
        return new_vec;                                         \
    }                                                           \
    void VEC_T##_destroy(VEC_T *vec) { free(vec->data); };      \
    void VEC_T##_push(VEC_T *vec, T data) {                     \
        if (vec->size == vec->capacity) {                       \
            vec->capacity *= 2;                                 \
            vec->data = (T *)realloc(vec->data, vec->capacity); \
            assert(vec->data);                                  \
        }                                                       \
        vec->data[vec->size++] = data;                          \
    }                                                           \
    T VEC_T##_pop(VEC_T *vec) {                                 \
        assert(vec->size > 0);                                  \
        return vec->data[--vec->size];                          \
    }                                                           \
    T VEC_T##_top(VEC_T *vec) {                                 \
        assert(vec->size > 0);                                  \
        return vec->data[vec->size - 1];                        \
    }
