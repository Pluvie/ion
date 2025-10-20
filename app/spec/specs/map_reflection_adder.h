#include "../spec.h"
#include "../containers.h"

#if standard(<= C99)
#define map_set(m, k, v) \
  map<char*, int>_set(m, k, v)
#endif
