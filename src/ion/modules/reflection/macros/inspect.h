/**
 * Used to inspect an object with reflection. */
#define inspect(obj, rfx) \
  reflection_inspect(rfx, &s(#obj), obj)
