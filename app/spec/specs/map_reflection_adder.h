#include "../spec.h"
#include "../containers.h"

#if standard(<= C99)
#define map_add(m, k, v) \
  map<char*, int>_add(m, k, v)
#endif
