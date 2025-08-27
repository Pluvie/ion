static inline int char_compare (
    char* v1,
    char* v2,
    int len
)
{
  if (len >= 0)
    return strncmp(v1, v2, len);
  else
    return strcmp(v1, v2);
}
