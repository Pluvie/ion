/* Default strings for formatted output, such as `printf` function. */

#define fmt(type) fmt_concat(type, _FORMAT)
#define fmt_concat(type, format) type ## format
#define str_fmt(string) (int_t) string.length, string.chars

#define CSTR_FORMAT     "s"
#define STR_FORMAT      ".*s"
#define ENUM_FORMAT     "u"
#define INT_T_FORMAT    "i"
#define UINT_T_FORMAT   "u"
