int stream_print (
    struct stream* stream,
    const char* format,
    ...
)
{
  va_list args;

  va_start(args, format);
  int len = vfprintf(stream->pointer, format, args);
  va_end(args);

  return len;
}
