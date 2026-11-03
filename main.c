#include <assert.h>
#include <stdio.h>

#include "vector.h"

int main(void)
{
  vector vec = new_vector(int);
  
  vec.reserve(&vec, 10);
  
  assert(vec.capacity == 10);
  
  for (size_t i = 0; i < 10; i++) {
    vec.push_back(&vec, &i);
  }
  vec.pop_back(&vec);
  assert(vec.size == 9);
  for (size_t i = 0; i < vec.size; i++) {
    printf("%d\n", *(int *)vec.at(&vec, i));
  }
  return 0;
}
