/**
 * Helper to check the equality of two strings. */
#define streq(s1, s2)                   \
  _Generic((s1),                        \
    string : _Generic((s2),             \
      string : streq<string, string>,   \
      slice : streq<string, slice>,     \
      char* : streq<string, char*>      \
    ),                                  \
    slice : _Generic((s2),              \
      string : streq<slice, string>,    \
      slice : streq<slice, slice>,      \
      char* : streq<slice, char*>       \
    ),                                  \
    char* : _Generic((s2),              \
      string : streq<char*, string>,    \
      slice : streq<char*, slice>,      \
      char* : streq<char*, char*>       \
    ),                                  \
    void* : _Generic((s2),              \
      string : streq<char*, string>,    \
      slice : streq<char*, slice>,      \
      char* : streq<char*, char*>       \
    )                                   \
  )(s1, s2)
