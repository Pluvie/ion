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

    if (arg->flag != 0) {
      printed_bytes = (length < 0 ?
        fprintf(output, "%s", (const char*) arg) :
        snprintf(output, length, "%s", (const char*) arg)
      );
    } else {
      switch (arg->type) {
      case PRINT_ARG_TYPE_BOOL:
        const char* bool_output = *(bool*) arg->value ? "true" : "false";
        printed_bytes = (length < 0 ?
          fprintf(output, "%s", bool_output) :
          snprintf(output, length, "%s", bool_output)
        );
        break;

      case PRINT_ARG_TYPE_CHAR:
        printed_bytes = (length < 0 ?
          fprintf(output, "%c", *(char*) arg->value) :
          snprintf(output, length, "%c", *(char*) arg->value)
        );
        break;

      case PRINT_ARG_TYPE_INT:
        printed_bytes = (length < 0 ?
          fprintf(output, INT_FORMAT, *(int*) arg->value) :
          snprintf(output, length, INT_FORMAT, *(int*) arg->value)
        );
        break;

      case PRINT_ARG_TYPE_UNSIGNED_INT:
        printed_bytes = (length < 0 ?
          fprintf(output, INT_UFORMAT, *(unsigned int*) arg->value) :
          snprintf(output, length, INT_UFORMAT, *(unsigned int*) arg->value)
        );
        break;

      case PRINT_ARG_TYPE_DEC:
        printed_bytes = (length < 0 ?
          fprintf(output, "%f", *(dec*) arg->value) :
          snprintf(output, length, "%f", *(dec*) arg->value)
        );
        break;

      case PRINT_ARG_TYPE_CHAR_POINTER:
        printed_bytes = (length < 0 ?
          fprintf(output, "%s", (char*) arg->value) :
          snprintf(output, length, "%s", (char*) arg->value)
        );
        break;

      case PRINT_ARG_TYPE_VOID_POINTER:
        printed_bytes = (length < 0 ?
          fprintf(output, "%p", (void*) arg->value) :
          snprintf(output, length, "%p", (void*) arg->value)
        );
        break;
      }
    }

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
