#include "../spec.h"
#include "../containers.h"

static int int_cmp (
    int* v,
    int* u
)
{
  return (*v == *u ? 0 : (*v > *u ? 1 : -1));
}

#if standard(<= C99)
#define list_sort(l, f) \
  list<int>_sort(l, f)
#endif
