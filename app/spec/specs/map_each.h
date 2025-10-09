#include "../spec.h"
#include "../containers.h"

static struct {
  void* unused;
} sim;

#if standard(<= C99)
#define map_each(m, k, v, ...)                                                          \
  (struct iterator iter = { 0 };                                                        \
    map<char*, int>_each(m, &iter); iter.position++, iter.index++)                      \
  for (k = (m)->keys.data + iter.position; iter.gate & (1<<0); iter.gate &= ~(1<<0))    \
  for (v = (m)->values + iter.position; iter.gate & (1<<1); iter.gate &= ~(1<<1))       \
  __VA_OPT__(                                                                           \
    for (int __VA_ARGS__ = iter.index; iter.gate & (1<<2); iter.gate &= ~(1<<2))        \
  )
#endif
