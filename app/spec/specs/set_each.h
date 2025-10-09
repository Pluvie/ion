#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define set_each(s, e, ...)                                                             \
  (struct iterator iter = { 0 };                                                        \
    set<int>_each(s, &iter); iter.position++, iter.index++)                             \
  for (e = (s)->data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))         \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index; iter.gate & (1<<1); iter.gate &= ~(1<<1))        \
  )
#endif
