int str_compare (
    str v,
    str u
)
{
  if (v.chars == nullptr && u.chars == nullptr)
    return 0;

  if (v.chars != nullptr && u.chars == nullptr)
    return 1;

  if (v.chars == nullptr && u.chars != nullptr)
    return -1;

  if (v.length > u.length)
    return 1;

  if (v.length < u.length)
    return -1;

  return memory_compare(v.chars, u.chars, v.length);
}
