int print (
    const char* format,
    ...
)
{
  va_list args;

  va_start(args, format);
  int len = fprintf(stderr, format, args);
  va_end(args);

  return len;
}
