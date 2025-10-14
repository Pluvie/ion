int cstr_compare (
    const char* v,
    const char* u
)
{
  if (v == nullptr && u == nullptr)
    return 0;

  if (v != nullptr && u == nullptr)
    return 1;

  if (v == nullptr && u != nullptr)
    return -1;

  return strcmp(v, u);
}
