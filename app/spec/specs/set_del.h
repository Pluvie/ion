#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define set_add(s, e) \
  set<char*>_add(s, e)

#define set_del(s, e) \
  set<char*>_del(s, e)
#endif
