string strsub (
    string source,
    int begin,
    int end
)
{
  if (end < 0)
    end = source.length + end;

  if (unlikely(strnull(source)))
    return (string) { 0 };

  if (unlikely(begin > end))
    return (string) { 0 };

  return (string) { source.content + begin, end - begin + 1 };
}
