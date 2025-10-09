#include "../spec.h"
#include "../containers.h"

#if standard(<= C99)
#define set_add(s, e) \
  set<int>_add(s, e)
#endif
