#include <assert.h>
#include <stdio.h>

#include "include/vector.h"

int main(void)
{
  vector vec = new_vector(long long);
  vec.reserve(&vec, 1000000);
  
  assert(vec.max_size(&vec) == 1152921504606846975);
  assert(vec.capacity == 1000000);
  
  for (size_t i = 0; i < vec.capacity; i++) {
    vec.push_back(&vec, &i);
  }

  long long sum = 0;
  for (size_t i = 0; i < vec.size; i++) {
    sum += *(long long *)vec.at(&vec, i);
  }
  printf("%lld\n", sum);
  return 0;
}
