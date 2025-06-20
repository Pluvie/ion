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

static inline int cmp<char> (
    char v1,
    char v2
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
  if (v1 != NULL && v2 != NULL)
    return strcmp(v1, v2);
  else if (v2 == NULL)
    return 1;
  else
    return -1;
}

static inline int cmp<string> (
    string v1,
    string v2
)
{
  if (v1.length > 0 && v2.length > 0)
    return strncmp(v1.content, v2.content, v1.length);
  else
    return cmp<int>(v1.length, v2.length);
}

static inline int cmp<slice> (
    slice v1,
    slice v2
)
{
  if (v1.length > 0 && v2.length > 0)
    return strncmp(v1.data, v2.data, v1.length);
  else
    return cmp<int>(v1.length, v2.length);
}
