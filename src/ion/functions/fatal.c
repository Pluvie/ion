void fatal (
    const cstr format,
    ...
)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  abort();
}
