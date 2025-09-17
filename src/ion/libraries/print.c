/*

     🖨️Print✅
  Enjoy your data!

*/

/*
  Utility function to dump a pointer value in a hex/ascii format.
*/
void print_hex (
    const void* pointer,
    size_t length
)
{
  const uint8_t* data = pointer;

  size_t line_length = 8;
  size_t groups = length / line_length;

  if (length % line_length > 0)
    groups++;

  for (size_t group = 0; group < groups; group++) {
    fprintf(PRINT_STREAM_DEFAULT, "| ");
    for (size_t index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        fprintf(PRINT_STREAM_DEFAULT, "   ");
        continue;
      }
      fprintf(PRINT_STREAM_DEFAULT, "%02x ", data[index]);
    }
    fprintf(PRINT_STREAM_DEFAULT, "| ");
    for (size_t index = group * line_length;
        index < (group * line_length) + line_length;
        index++) {
      if (index >= length) {
        fprintf(PRINT_STREAM_DEFAULT, "  ");
        continue;
      }
      if (data[index] <= 31)
        fprintf(PRINT_STREAM_DEFAULT, "_ ");
      else
        fprintf(PRINT_STREAM_DEFAULT, "%c ", data[index]);
    }
    fprintf(PRINT_STREAM_DEFAULT, "|\n");
  }
}

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
)
{
  va_list args;
  va_start(args);

  struct print_arg* arg = nullptr;
  bool printing_on_string = length >= 0;
  int32_t total_printed_bytes = 0;

  do {
    arg = va_arg(args, struct print_arg*);
    if (arg == nullptr)
      break;

    int32_t printed_bytes = 0;

    if (arg->flag != 0)
      printed_bytes = print_dispatch(output, length, "%s", (const char*) arg);
    else
      printed_bytes = arg->functor(output, length, arg->value);

    total_printed_bytes += printed_bytes;
    if (printing_on_string) {
      output += printed_bytes;
      length -= printed_bytes;
      if (length < 0) length = 0;
    }

  } while(arg != nullptr);

  va_end(args);

  if (!printing_on_string)
    fflush(output);

  return total_printed_bytes;
}

/*
  Prints a boolean value.
  The printed value is a string, which is "true" if the boolean is true, or "false"
  otherwise.
*/
int32_t print_bool (
    void* output,
    int32_t length,
    const bool* value
)
{
  return print_dispatch(output, length, "%s", *value ? "true" : "false");
}

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
)
{
  if (*value > 31)
    return print_dispatch(output, length, "%c", *value);
  else
    return print_dispatch(output, length, "\\%d", *value);
}

/*
  Prints an `uint8_t`.
*/
int32_t print_uint8 (
    void* output,
    int32_t length,
    const uint8_t* value
)
{
  return print_dispatch(output, length, "%hhu", *value);
}

/*
  Prints an `int16_t`.
*/
int32_t print_int16 (
    void* output,
    int32_t length,
    const int16_t* value
)
{
  return print_dispatch(output, length, "%hd", *value);
}

/*
  Prints an `uint16_t`.
*/
int32_t print_uint16 (
    void* output,
    int32_t length,
    const uint16_t* value
)
{
  return print_dispatch(output, length, "%hu", *value);
}

/*
  Prints an `int32_t`.
*/
int32_t print_int32 (
    void* output,
    int32_t length,
    const int32_t* value
)
{
  return print_dispatch(output, length, "%d", *value);
}

/*
  Prints an `uint32_t`.
*/
int32_t print_uint32 (
    void* output,
    int32_t length,
    const uint32_t* value
)
{
  return print_dispatch(output, length, "%u", *value);
}

/*
  Prints an `int64_t`.
*/
int32_t print_int64 (
    void* output,
    int32_t length,
    const int64_t* value
)
{
  return print_dispatch(output, length, "%ld", *value);
}

/*
  Prints an `uint64_t`.
*/
int32_t print_uint64 (
    void* output,
    int32_t length,
    const uint64_t* value
)
{
  return print_dispatch(output, length, "%lu", *value);
}

/*
  Prints a `float`.
*/
int32_t print_float (
    void* output,
    int32_t length,
    const float* value
)
{
  return print_dispatch(output, length, "%f", *value);
}

/*
  Prints a `double`.
*/
int32_t print_double (
    void* output,
    int32_t length,
    const double* value
)
{
  return print_dispatch(output, length, "%f", *value);
}

/*
  Prints a `char*`.
  The function adds a '"' at the begining and at the end of the string.
*/
int32_t print_char_p (
    void* output,
    int32_t length,
    const char** value
)
{
  return print_dispatch(output, length, "\"%s\"", *value);
}

/*
  Prints a `void*` as numeric address.
*/
int32_t print_void_p (
    void* output,
    int32_t length,
    const void** value
)
{
  return print_dispatch(output, length, "%p", *value);
}
