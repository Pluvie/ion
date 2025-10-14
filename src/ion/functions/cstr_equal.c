bool cstr_equal (
    const char* v,
    const char* u
)
{
  if (v == nullptr && u == nullptr)
    return true;

  if (v == nullptr || u == nullptr)
    return false;

  return strcmp(v, u) == 0;
}
