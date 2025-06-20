/**
 * Functions used only by the `strnull` macro. */

static inline bool strnull<string> (
    string s
)
{
  return s.content == NULL || s.length == 0;
}

static inline bool strnull<char*> (
    char* s
)
{
  return s == NULL;
}
