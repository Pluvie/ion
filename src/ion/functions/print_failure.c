void print_failure (
    bool is_fatal,
    ...
)
{
  failure.occurred = true;
  char message[sizeof(failure.message)] = { 0 };

  va_list args;
  va_start(args, is_fatal);
  print_args(message, sizeof(message), args);
  va_end(args);

  memory_copy(failure.message, message, sizeof(message));

  if (is_fatal)
    abort();
}
