void print (
    const char* format,
    ...
)
{
  puts(format);
  va_list args;
  va_start(args, format);
  struct print_arg* arg;
  while(arg != nullptr) {
    vprintf(format, args);
  }
  va_end(args);
}
