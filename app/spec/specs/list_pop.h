#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define list_pop(l) \
  list<int>_pop(l)

#define list_push(l, e) \
  list<int>_push(l, e)
#endif
