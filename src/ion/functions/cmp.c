/**
 * Predefined comparison functions for ⚡️ION⚡️ base types. */

static inline int cmp<int> (
    int v1,
    int v2
)
{
  if (v1 == v2) return 0;
  if (v1 > v2) return 1;
  else return -1;
}

static inline int cmp<dec> (
    dec v1,
    dec v2
)
{
  if (v1 == v2) return 0;
  if (v1 > v2) return 1;
  else return -1;
}

static inline int cmp<bool> (
    bool v1,
    bool v2
)
{
  if (v1 == v2) return 0;
  if (v1 > v2) return 1;
  else return -1;
}

static inline int cmp<string> (
    string v1,
    string v2
)
{
  if (likely(v1.length > 0 && v2.length > 0))
    return byte_compare(v1.pointer, v2.pointer, v1.length);
  else
    return cmp<int>(v1.length, v2.length);
}

static inline int cmp<struct io*> (
    struct io* v1,
    struct io* v2
)
{
  return byte_compare(v1, v2, sizeof(struct io));
}
