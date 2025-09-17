/*

     🖨️Print✅
  Enjoy your data!

*/

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

/*
  By default, the stream where `print` and `printl` macros operate is stderr.
  This can be changed by defining the PRINT_STREAM_DEFAULT before including the
  print.h header.
*/
#ifndef PRINT_STREAM_DEFAULT
#define PRINT_STREAM_DEFAULT  stderr
#endif

/*
  Defines some colors for printing on the tty.
*/
#define PRINT_COLOR_BLUE      "\x1b[34m"
#define PRINT_COLOR_CYAN      "\x1b[36m"
#define PRINT_COLOR_GREEN     "\x1b[32m"
#define PRINT_COLOR_GREY      "\e[38;5;250m"
#define PRINT_COLOR_MAGENTA   "\x1b[35m"
#define PRINT_COLOR_NONE      "\x1b[0m"
#define PRINT_COLOR_RED       "\x1b[31m"
#define PRINT_COLOR_YELLOW    "\x1b[33m"

/*
  This struct contains the print argument metadata.

  `flag` is always set to 0: it is used by the `print_variadic` function to distinguish
  when an argument is a `const char*` or a `struct print_arg*`.

  `value` is a pointer to the actual value to be printed.

  `functor` is the function that shall do the actual printing. This function shall
  be selected by the macro `print_selector` depending on the type of `value` using a
  _Generic statement.
*/
struct print_arg {
  const char flag;
  const void* value;
  int32_t (*functor)(void*, int32_t, const void*);
};

/*
  This macro builds a `struct print_arg*` using the provided value and functor.
*/
#define print_arg(value, functor) \
  &(struct print_arg) { 0, &value, (int32_t (*)(void*, int32_t, const void*)) functor }

/*
  This macro is used to define custom print types. By default, it points to nothing.
*/
#define print_custom(value) \
  default: nullptr

/*
  This macro selects the correct print function depending on the type of `value`.
*/
#define f(value) \
  _Generic((value), print_selector(value))

#define print_selector(value)                 \
  bool:       print_arg(value, print_bool),   \
  int8_t:     print_arg(value, print_int8),   \
  uint8_t:    print_arg(value, print_uint8),  \
  int16_t:    print_arg(value, print_int16),  \
  uint16_t:   print_arg(value, print_uint16), \
  int32_t:    print_arg(value, print_int32),  \
  uint32_t:   print_arg(value, print_uint32), \
  int64_t:    print_arg(value, print_int64),  \
  uint64_t:   print_arg(value, print_uint64), \
  float:      print_arg(value, print_float),  \
  double:     print_arg(value, print_double), \
  char*:      print_arg(value, print_char_p), \
  void*:      print_arg(value, print_void_p), \
  print_custom(value)

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
#define sprint(string, length, ...) \
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
  Utility function to dump a pointer value in a hex/ascii format.
*/
void print_hex (
    const void* pointer,
    size_t length
);

/*
  This function prints on the given `output` looping over the variadic arguments. These
  arguments can be of two types:

    - `const char*`: when the user specifies a string literal. 
    - `struct print_arg*`: when the user calls the `f` macro on a value.

  Since in C there is no way to determine the type of a variadic argument, this function
  resorts to the following trick: the variadic arg is treated like a `struct print_arg*`
  by default.

  Then, the `flag` field is checked, which corresponds to the first byte of the struct.
  If this byte is 0, the function assumes that the variadic arg is indeed a
  `struct print_arg*`, because they are built on purpose with the first byte always
  set to 0 using the `print_arg` macro. In this case, the `functor` field of this struct
  is called, which shall handle the appropriate printing of the value.

  On the other hand, if the variadic arg was instead a `const char*`, the `arg->flag`
  check points to the first byte of the string. It is highly unlikely that the first
  byte of the string is 0, as it would mean that the user asked to print an empty
  string.  Of course this could always happen, and this is the only real limitation of
  this library. Still, there is no reason to print an empty string -- as it would
  literally do nothing -- so this limitation is arguably not that relevant.

  When the variadic arg is `nullptr` the function terminates.
*/
int32_t print_variadic (
    void* output,
    int32_t length,
    ...
);

/*
  Prints a boolean value.
  The printed value is a string, which is "true" if the boolean is true, or "false"
  otherwise.
*/
int32_t print_bool (
    void* output,
    int32_t length,
    const bool* value
);

/*
  Prints an `int8_t`, which is actually a `char`.
  If the numeric value is higher than 31, the function print the ASCII equivalent
  of the value. Otherwise, since ASCII chars lower than 32 are non-printable, prints
  the numeric value prefixed with "\".
*/
int32_t print_int8 (
    void* output,
    int32_t length,
    const int8_t* value
);

/*
  Prints an `uint8_t`.
*/
int32_t print_uint8 (
    void* output,
    int32_t length,
    const uint8_t* value
);

/*
  Prints an `int16_t`.
*/
int32_t print_int16 (
    void* output,
    int32_t length,
    const int16_t* value
);

/*
  Prints an `uint16_t`.
*/
int32_t print_uint16 (
    void* output,
    int32_t length,
    const uint16_t* value
);

/*
  Prints an `int32_t`.
*/
int32_t print_int32 (
    void* output,
    int32_t length,
    const int32_t* value
);

/*
  Prints an `uint32_t`.
*/
int32_t print_uint32 (
    void* output,
    int32_t length,
    const uint32_t* value
);

/*
  Prints an `int64_t`.
*/
int32_t print_int64 (
    void* output,
    int32_t length,
    const int64_t* value
);

/*
  Prints an `uint64_t`.
*/
int32_t print_uint64 (
    void* output,
    int32_t length,
    const uint64_t* value
);

/*
  Prints a `float`.
*/
int32_t print_float (
    void* output,
    int32_t length,
    const float* value
);

/*
  Prints a `double`.
*/
int32_t print_double (
    void* output,
    int32_t length,
    const double* value
);

/*
  Prints a `char*`.
  The function adds a '"' at the begining and at the end of the string.
*/
int32_t print_char_p (
    void* output,
    int32_t length,
    const char** value
);

/*
  Prints a `void*` as numeric address.
*/
int32_t print_void_p (
    void* output,
    int32_t length,
    const void** value
);
