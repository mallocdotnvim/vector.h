#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define VEC_INIT_CAPACITY 16

typedef struct vector_impl vector;
#define new_vector(data_type) (vector) { \
  .data      = NULL,                     \
  .data_size = sizeof(data_type),        \
  .at        = vector_at,                \
  .size      = 0,                        \
  .max_size  = max_size,                 \
  .capacity  = 0,                        \
  .reserve   = vector_reserve,           \
  .push_back = vector_push_back,         \
  .pop_back  = vector_pop_back,          \
};                                       \

struct vector_impl {
  void *data;
  size_t data_size;
  // Element access
  void *(*at)(const vector *vec, size_t index);
  // Capacity
  size_t size;
  size_t (*max_size)(const vector *vec);
  size_t capacity;
  void (*reserve)(vector *vec, size_t expect_capacity);
  // Modifiers
  void (*push_back)(vector *vec, void *elements);
  void (*pop_back)(vector *vec);
};

void *vector_at(const vector *vec, size_t index);
size_t max_size(const vector *vec);
void vector_reserve(vector *vec, size_t capacity);
static inline void vector_append(vector *vec, size_t expect_capacity);
void vector_push_back(vector *vec, void *elements);
void vector_pop_back(vector *vec);
#endif