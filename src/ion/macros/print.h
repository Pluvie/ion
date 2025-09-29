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
  This macro builds a `struct print_arg*` using the provided value and functor.
*/
#define print_arg(value, functor) \
  &(struct print_arg) { 0, (int (*)(void*, int, const void*)) functor, value }

/*
  This macro is used to define custom print types. By default, it points to nothing.
*/
#define print_custom(value) \
  default: nullptr

/*
  This macro selects the correct print function depending on the type of `value`.
*/
#define f(value)                                            \
  _Generic((value),                                         \
    bool          : print_arg(&value, print_bool),          \
    char          : print_arg(&value, print_char),          \
    unsigned char : print_arg(&value, print_char_unsigned), \
    int0          : print_arg(&value, print_int0),          \
    int           : print_arg(&value, print_int),           \
    unsigned int  : print_arg(&value, print_int_unsigned),  \
    dec           : print_arg(&value, print_dec),           \
    char*         : print_arg(&value, print_char_pointer),  \
    void*         : print_arg(&value, print_void_pointer),  \
    print_custom(value)                                     \
  )
