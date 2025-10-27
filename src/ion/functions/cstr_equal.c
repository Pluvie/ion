bool cstr_equal (
    const cstr v,
    const cstr u
)
{
  if (v == nullptr && u == nullptr)
    return true;

  if (v == nullptr || u == nullptr)
    return false;

  return strcmp(v, u) == 0;
}
