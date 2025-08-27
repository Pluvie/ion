string substring (
    string source,
    int begin,
    int end
)
{
  if (end < 0)
    end = source.length + end;

  if (unlikely(source.pointer == NULL))
    return (string) { 0 };

  if (unlikely(begin > end))
    return (string) { 0 };

  return (string) { source.pointer + begin, end - begin + 1 };
}
