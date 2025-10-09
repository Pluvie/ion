#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define map_get(m, k) \
  map<char*, int>_get(m, k)

#define map_set(m, k, v) \
  map<char*, int>_set(m, k, v)
#endif
