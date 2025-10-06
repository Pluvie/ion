bool string_equal (
    string v,
    string u
)
{
  if (v.chars == nullptr && u.chars == nullptr)
    return true;

  if (v.chars == nullptr && u.chars != nullptr)
    return false;

  if (v.chars != nullptr && u.chars == nullptr)
    return false;

  return memory_equal(v.chars, u.chars, min(v.length, u.length));
}
