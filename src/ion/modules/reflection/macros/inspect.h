/**
 * Used to inspect an object with reflection. */
#define inspect(obj, rfx, ...)        \
  reflection_inspect(rfx,             \
    (__VA_OPT__(1+)0) ?               \
      __VA_OPT__((__VA_ARGS__)+)0 :   \
      &s(#obj),                       \
    obj)
