int string_print (
    string target,
    const char* format,
    ...
)
{
  va_list args;

  va_start(args, format);
  int len = vsnprintf(target.pointer, target.length, format, args);
  va_end(args);

  return len;
}
