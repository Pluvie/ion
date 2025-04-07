#ifdef ION_INCLUDED
static inline
#endif

bool string_equal (
    struct string* s1,
    struct string* s2
)
{
  if (s1 == NULL || s2 == NULL)
    return false;

  if (s1->length != s2->length)
    return false;

  return strneq(s1->content, s2->content, s1->length);
}
