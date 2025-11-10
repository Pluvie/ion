int str_compare_case (
    str v,
    str u
)
{
  uint index;
  int comparison;

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

  for (index = 0; index < v.length; index++) {
    comparison = v.chars[index] - u.chars[index];
    if (comparison == 32 && v.chars[index] >= 'a' && v.chars[index] <= 'z')
      continue;
    if (comparison == -32 && v.chars[index] >= 'A' && v.chars[index] <= 'Z')
      continue;
    if (comparison != 0)
      return comparison;
  }

  return 0;
}
