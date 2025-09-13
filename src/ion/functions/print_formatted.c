void print_formatted (
    void* stream,
    ...
)
{
  va_list args;
  va_start(args);
  struct print_arg* arg = nullptr;

next_arg:
  arg = va_arg(args, struct print_arg*); 

  if (arg == nullptr)
    goto end;

  if (arg->flag != 0) {
    fprintf(stream, "%s", (const char*) arg);
    goto next_arg;
  }

  switch (arg->type) {
  case PRINT_ARG__BOOL:
    fprintf(stream, "%s", *((bool*) arg->value) ? "true" : "false");
    break;
  case PRINT_ARG__CHAR:
    fprintf(stream, "%c", *((char*) arg->value));
    break;
  case PRINT_ARG__UCHAR:
    fprintf(stream, "%hhu", *((unsigned char*) arg->value));
    break;
  case PRINT_ARG__SHORT:
    fprintf(stream, "%hd", *((short*) arg->value));
    break;
  case PRINT_ARG__USHORT:
    fprintf(stream, "%hu", *((unsigned short*) arg->value));
    break;
  case PRINT_ARG__INT:
    fprintf(stream, "%i", *((int0*) arg->value));
    break;
  case PRINT_ARG__UINT:
    fprintf(stream, "%u", *((unsigned*) arg->value));
    break;
  case PRINT_ARG__LONG:
    fprintf(stream, "%li", *((long*) arg->value));
    break;
  case PRINT_ARG__ULONG:
    fprintf(stream, "%lu", *((unsigned long*) arg->value));
    break;
  case PRINT_ARG__LONGLONG:
    fprintf(stream, "%lli", *((long long*) arg->value));
    break;
  case PRINT_ARG__ULONGLONG:
    fprintf(stream, "%llu", *((unsigned long long*) arg->value));
    break;
  case PRINT_ARG__DEC:
    fprintf(stream, "%f", *((dec*) arg->value));
    break;
  case PRINT_ARG__CHAR_P:
    fprintf(stream, "%s", *((char**) arg->value));
    break;
  case PRINT_ARG__VOID_P:
    fprintf(stream, "%p", *((void**) arg->value));
    break;
  }

  goto next_arg;

end:
  va_end(args);
}
