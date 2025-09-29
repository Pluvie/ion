int print_variadic (
    void* output,
    int length,
    ...
)
{
  va_list args
  va_start(args, length);
  int result = print_args(output, length, args);
  va_end(args);
  return result;
}
