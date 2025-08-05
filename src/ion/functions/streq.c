/**
 * Functions used only by the `streq` macro. */

static inline bool streq<string, string> (
    string s1,
    string s2
)
{
  return cmp<string>(s1, s2) == 0;
}

static inline bool streq<string, slice> (
    string s1,
    slice s2
)
{
  string s = (string) { s2.data, s2.length };
  return cmp<string>(s1, s) == 0;
}

static inline bool streq<slice, string> (
    slice s1,
    string s2
)
{
  slice s = (slice) { s2.content, s2.length };
  return cmp<slice>(s1, s) == 0;
}

static inline bool streq<slice, slice> (
    slice s1,
    slice s2
)
{
  return cmp<slice>(s1, s2) == 0;
}

static inline bool streq<string, char*> (
    string s1,
    char* s2
)
{
  return strncmp(s1.content, s2, s1.length) == 0;
}

static inline bool streq<slice, char*> (
    slice s1,
    char* s2
)
{
  return strncmp(s1.data, s2, s1.length) == 0;
}

static inline bool streq<char*, string> (
    char* s1,
    string s2
)
{
  return strncmp(s1, s2.content, s2.length) == 0;
}

static inline bool streq<char*, slice> (
    char* s1,
    slice s2
)
{
  return strncmp(s1, s2.data, s2.length) == 0;
}

static inline bool streq<char*, char*> (
    char* s1,
    char* s2
)
{
  return strcmp(s1, s2) == 0;
}
