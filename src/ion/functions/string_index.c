int string_index (
    string source,
    string tester
)
{
  if (unlikely(tester.length == 0))
    return -1;

  if (unlikely(tester.length > source.length))
    return -1;

  for (int i = 0; i <= source.length - tester.length; i++)
    if (strncmp(source.pointer + i, tester.pointer, tester.length) == 0)
      return i;

  return -1;
}
