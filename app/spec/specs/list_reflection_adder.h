#include "../spec.h"
#include "../containers.h"

#if standard(<= C99)
#define list_push(l, e) \
  list<int>_push(l, e)
#endif
