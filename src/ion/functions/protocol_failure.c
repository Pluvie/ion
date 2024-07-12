static inline void protocol_failure (
    struct protocol* p,
    const char* format,
    ...
)
{
print_path:
  char path_string[256] = { 0 };
  i32 path_length = protocol_path_print(p, path_string, sizeof(path_string));

print_message:
  char message_string[256] = { 0 };
  i32 message_length = 0;

  va_list variadics;
  va_start(variadics, format);

  message_length = vsnprintf(
    message_string, sizeof(message_string), format, variadics);
      
  if (unlikely(message_length < 0)) {
    failure(p->error, "internal error");
    return;
  }

  if (path_length > 0)
    goto print_message_and_path;
  else
    goto print_message_only;

print_message_and_path:
  failure(p->error, "[%.*s] %.*s",
    path_length, path_string,
    message_length, message_string);
  return;

print_message_only:
  failure(p->error, "%.*s", message_length, message_string);
  return;
}
