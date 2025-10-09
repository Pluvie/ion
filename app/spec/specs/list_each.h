#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define list_each(l, e, ...)                                                            \
  (struct iterator iter = { 0 };                                                        \
    list<int>_each(l, &iter); iter.position++, iter.index++)                            \
  for (e = (l)->data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))         \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index; iter.gate & (1<<1); iter.gate &= ~(1<<1))        \
  )
#endif
