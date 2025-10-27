/* Defines the `str` ⚡️ION⚡️ type.
  This type is a convenient wrapper over the standard C string, which is a
  nul-terminated `char*`. The `str` type is useful when working with reflection,
  language bindings and data formats, where strings are not usually nul-terminated. */
typedef struct str {
  cstr    chars;
  uint  length;
} str;
