/*
  This macro prints sequentially its arguments over the default print stream.
*/
#define print(...) \
  print_variadic(PRINT_STREAM_DEFAULT, -1 __VA_OPT__(, __VA_ARGS__), nullptr)

/*
  This macro prints sequentially its arguments over the default print stream.
  It also appends a new line at the end.
*/
#define printl(...) \
  print_variadic(PRINT_STREAM_DEFAULT, -1 __VA_OPT__(, __VA_ARGS__), "\n", nullptr)

/*
  This macro prints sequentially its arguments over the given string, up to the
  given length.
*/
#define prints(string, length, ...) \
  print_variadic(string, length __VA_OPT__(, __VA_ARGS__), nullptr)

/*
  This macro dispatches the print call depending on the `length` argument.
  If `length` is less than 0, `output` is assumed to be a stream and the `fprintf`
  function is called. Otherwise, `output` is assumed to be a string and the `snprintf`
  function is called.
*/
#define print_dispatch(output, length, format, ...)             \
  (length < 0 ?                                                 \
    fprintf(output, format __VA_OPT__(, __VA_ARGS__)) :         \
    snprintf(output, length, format  __VA_OPT__(, __VA_ARGS__)) \
  )

/*
  This macro passes the correct print_arg struct depending on the type of `value`.
*/
#define f(...)                                                    \
  _Generic(__VA_ARGS__,                                           \
    bool          : &(struct print_arg) { 0, PRINT_ARG__BOOL },   \
    int0          : &(struct print_arg) { 0, PRINT_ARG__INT0 },   \
    int           : &(struct print_arg) { 0, PRINT_ARG__INT },    \
    unsigned int  : &(struct print_arg) { 0, PRINT_ARG__UINT },   \
    dec           : &(struct print_arg) { 0, PRINT_ARG__DEC },    \
    str           : &(struct print_arg) { 0, PRINT_ARG__STR },    \
    char          : &(struct print_arg) { 0, PRINT_ARG__CHAR },   \
    unsigned char : &(struct print_arg) { 0, PRINT_ARG__UCHAR },  \
    char*         : &(struct print_arg) { 0, PRINT_ARG__CHAR_P }, \
    void*         : &(struct print_arg) { 0, PRINT_ARG__VOID_P }  \
  ), __VA_ARGS__
