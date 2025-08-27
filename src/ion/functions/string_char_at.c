static inline char string_char_at (
    string str,
    int pos
)
{
  if (likely(pos < str.length))
    return ((char*)str.pointer)[pos];

  return 0;
}
