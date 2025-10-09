#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define list_del(l, e) \
  list<int>_del(l, e)

#define list_push(l, e) \
  list<int>_push(l, e)
#endif
