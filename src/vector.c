#include "../include/vector.h"

void *vector_at(const vector *vec, size_t index)
{
  assert(index < vec->size);
  return (char *)(vec->data + vec->data_size * index);
}

size_t max_size(const vector *vec)
{
  return SIZE_MAX / (2 *vec->data_size);
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