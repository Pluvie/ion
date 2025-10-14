bool str_equal (
    str v,
    str u
)
{
  if (v.chars == nullptr && u.chars == nullptr)
    return true;

  if (v.chars == nullptr || u.chars == nullptr)
    return false;

  if (v.length != u.length)
    return false;

  return memory_equal(v.chars, u.chars, v.length);
}
