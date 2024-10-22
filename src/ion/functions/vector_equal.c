#ifdef ION_INCLUDED
static inline
#endif

bool vector_equal (
    struct vector* v1,
    struct vector* v2
)
{
  if (v1->length != v2->length)
    return false;

  if (v1->typesize != v2->typesize)
    return false;

  u64 length = v1->length;
  u64 typesize = v1->typesize;

  for (u64 index = 0; index < length; index++)
    if (memcmp(vector_get(v1, index), vector_get(v2, index), typesize) != 0)
      return false;

  return true;
}
