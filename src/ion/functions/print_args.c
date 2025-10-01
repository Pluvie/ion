int print_args (
    void* output,
    int length,
    va_list args
)
{
  struct print_arg* arg = nullptr;
  bool printing_on_string = length >= 0;
  int total_printed_bytes = 0;

  do {
    arg = va_arg(args, struct print_arg*);
    if (arg == nullptr)
      break;

    int printed_bytes = 0;

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

  if (!printing_on_string)
    fflush(output);

  return total_printed_bytes;
}

int print_bool (void* output, int length, bool* value) {
  return print_dispatch(output, length, "%s", *value ? "true" : "false");
}
int print_char (void* output, int length, char* value) {
  return print_dispatch(output, length, "%c", *value);
}
int print_char_unsigned (void* output, int length, unsigned char* value) {
  return print_dispatch(output, length, "%02x", *value);
}
int print_int0 (void* output, int length, int0* value) {
  return print_dispatch(output, length, "%i", *value);
}
int print_int (void* output, int length, int* value) {
  return print_dispatch(output, length, INT_FORMAT "i", *value);
}
int print_int_unsigned (void* output, int length, unsigned int* value) {
  return print_dispatch(output, length, INT_FORMAT "u", *value);
}
int print_dec (void* output, int length, dec* value) {
  return print_dispatch(output, length, "%f", *value);
}
int print_char_pointer (void* output, int length, char** value) {
  return print_dispatch(output, length, "\"%s\"", *value);
}
int print_void_pointer (void* output, int length, void** value) {
  return print_dispatch(output, length, "%p", *value);
}
