void fail (
    const char* format,
    ...
)
{
  failure.occurred = true;
  char message[sizeof(failure.message)] = { 0 };

  va_list args;
  va_start(args, format);
  vsnprintf(message, sizeof(message), format, args);
  va_end(args);

  memory_copy(failure.message, message, sizeof(message));
}
