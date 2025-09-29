/*
  Defines the `string` ⚡️ION⚡️ types.

  This type is a convenient wrapper over the standard C string, which is a
  nul-terminated `char*`. The `string` type is useful when working with reflection,
  language bindings and data formats, where strings are not usually nul-terminated.
*/
#ifdef string
#undef string
#endif

typedef struct string {
  char* chars;
  int length;
} string;
