int print_args (
    void* output,
    int length,
    va_list args
)
{
  struct print_arg* arg = nullptr;
  bool printing_on_string = length >= 0;
  int total_printed_bytes = 0;

next_arg:
  arg = va_arg(args, struct print_arg*);
  if (arg == nullptr)
    goto terminate;

  int printed_bytes = 0;

  if (arg->flag != 0) {
    printed_bytes = print_dispatch(output, length, "%s", (const char*) arg);
    goto adjust_printed_bytes;
  }

  switch (arg->type) {
  case PRINT_ARG__INT0:
    int0 arg_int0 = va_arg(args, int0);
    printed_bytes = print_dispatch(output, length, "%i", arg_int0);
    break;

  case PRINT_ARG__INT:
    int arg_int = va_arg(args, int);
    printed_bytes = print_dispatch(output, length, INT_FORMAT "i", arg_int);
    break;

  case PRINT_ARG__UINT:
    unsigned int arg_uint = va_arg(args, unsigned int);
    printed_bytes = print_dispatch(output, length, INT_FORMAT "u", arg_uint);
    break;

  case PRINT_ARG__DEC:
    dec arg_dec = va_arg(args, dec);
    printed_bytes = print_dispatch(output, length, "%f", arg_dec);
    break;

  case PRINT_ARG__STR:
    str arg_str = va_arg(args, str);
    printed_bytes = print_dispatch(output, length, "%.*s", (int0) arg_str.length, arg_str.chars);
    break;

  case PRINT_ARG__BOOL:
    bool arg_bool = va_arg(args, int0);
    printed_bytes = print_dispatch(output, length, "%s", arg_bool ? "true" : "false");
    break;

  case PRINT_ARG__CHAR:
    char arg_char = va_arg(args, int0);
    if (arg_char > 31)
      printed_bytes = print_dispatch(output, length, "%c", arg_char);
    else
      printed_bytes = print_dispatch(output, length, "%02x", arg_char);
    break;

  case PRINT_ARG__UCHAR:
    unsigned char arg_uchar = va_arg(args, int0);
    printed_bytes = print_dispatch(output, length, "%02x", arg_uchar);
    break;

  case PRINT_ARG__CHAR_P:
    char* arg_char_p = va_arg(args, char*);
    printed_bytes = print_dispatch(output, length, "%s", arg_char_p);
    break;

  case PRINT_ARG__VOID_P:
    void* arg_void_p = va_arg(args, void*);
    printed_bytes = print_dispatch(output, length, "%p", arg_void_p);
    break;
  }

adjust_printed_bytes:
  total_printed_bytes += printed_bytes;
  if (printing_on_string) {
    output += printed_bytes;
    length -= printed_bytes;
    if (length < 0) length = 0;
  }

  goto next_arg;

terminate:
  if (!printing_on_string)
    fflush(output);

  return total_printed_bytes;
}
