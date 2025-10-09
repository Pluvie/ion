#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define map_del(m, k) \
  map<char*, int>_del(m, k)

#define map_set(m, k, v) \
  map<char*, int>_set(m, k, v)
#endif
