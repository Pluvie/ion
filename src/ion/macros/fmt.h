/* Default strings for formatted output, such as `printf` function. */

#define fmt(type) fmt_concat(type, _FORMAT)
#define fmt_concat(type, format) type ## format
#define str_fmt(string) (int_t) string.length, string.chars

/* Defines some standard formats to print the most common types. */
#define CSTR_FORMAT         "s"
#define STR_FORMAT          ".*s"
#define ENUM_FORMAT         "u"
#define INT_T_FORMAT        "i"
#define UINT_T_FORMAT       "u"

/* Defines some colors for printing on the tty. */
#define FMT_COLOR_BLUE      "\x1b[34m"
#define FMT_COLOR_CYAN      "\x1b[36m"
#define FMT_COLOR_GREEN     "\x1b[32m"
#define FMT_COLOR_GREY      "\e[38;5;250m"
#define FMT_COLOR_MAGENTA   "\x1b[35m"
#define FMT_COLOR_NONE      "\x1b[0m"
#define FMT_COLOR_RED       "\x1b[31m"
#define FMT_COLOR_YELLOW    "\x1b[33m"
