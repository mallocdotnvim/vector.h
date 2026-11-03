#ifndef VECTOR_H
#define VECTOR_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
  
#define VEC_INIT_CAPACITY 16
#define new_vector(data_type) (vector) { \
  .data      = NULL,                     \
  .data_size = sizeof(data_type),        \
  .at        = vector_at,                \
  .size      = 0,                        \
  .capacity  = 0,                        \
  .reserve   = vector_reserve,           \
  .push_back = vector_push_back,         \
  .pop_back  = vector_pop_back,          \
};                                       \

typedef struct vector_impl vector;

struct vector_impl {
  void *data;
  size_t data_size;
  // Element access
  void *(*at)(vector *vec, size_t index);
  // Capacity
  size_t size;
  size_t capacity;
  void (*reserve)(vector *vec, size_t expect_capacity);
  // Modifiers
  void (*push_back)(vector *vec, void *elements);
  void (*pop_back)(vector *vec);
};

void *vector_at(vector *vec, size_t index)
{
  assert(index < vec->size);
  return (char *)(vec->data + vec->data_size * index);
}

void vector_reserve(vector *vec, size_t capacity)
{
  assert(capacity > 0);
  vec->data = realloc(vec->data, vec->data_size * capacity);
  assert(vec->data != NULL);
  vec->capacity += capacity;
}

static inline void vector_append(vector *vec, size_t expect_capacity)
{
  
  if (expect_capacity <= vec->capacity && vec->data != NULL) {
    return;
  }
  if (vec->capacity == 0) vec->capacity = VEC_INIT_CAPACITY;
  while (vec->capacity < expect_capacity) {
    vec->capacity *= 2;
  }

  vec->data = realloc(vec->data, vec->data_size * vec->capacity);
  assert(vec->data != NULL);
  return;
}

void vector_push_back(vector *vec, void *elements)
{
  if (vec->size >= vec->capacity) vector_append(vec, vec->size + 1);
  void *target = (char *)vec->data + (vec->size * vec->data_size);
  memcpy(target, elements, vec->data_size);
  vec->size++;
}

void vector_pop_back(vector *vec)
{
  assert(vec->size > 0);
  vec->size--;
}

#endif