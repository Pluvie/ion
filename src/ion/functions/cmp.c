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

static inline int cmp<char*> (
    char* v1,
    char* v2
)
{
  if (likely(v1 != NULL && v2 != NULL))
    return char_compare(v1, v2);
  else if (v1 != NULL)
    return 1;
  else if (v2 != NULL)
    return -1;
  else
    return 0;
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

static inline int cmp<string, char*> (
    string v1,
    char* v2
)
{
  if (likely(v1.length > 0 && v2 != NULL))
    return byte_compare(v1.pointer, v2, v1.length);
  else if (v1.length > 0 && v2 == NULL)
    return 1;
  else if (v1.length == 0 && v2 != NULL)
    return -1;
  else
    return 0;
}

static inline int cmp<char*, string> (
    char* v1,
    string v2
)
{
  if (likely(v1 != NULL && v2.length > 0))
    return byte_compare(v1, v2.pointer, v2.length);
  else if (v1 != NULL && v2.length == 0)
    return 1;
  else if (v1 == NULL && v2.length > 0)
    return -1;
  else
    return 0;
}
