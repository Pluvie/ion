static inline void protocol_failure (
    struct protocol* p
)
{
  char path_string[256] = { 0 };
  i32 path_length = protocol_path_print(p, path_string, sizeof(path_string));

  if (path_length <= 0)
    return;

  char error_message[sizeof(error.message)] = { 0 };
  strncpy(error_message, error.message, error.length);

  fail("[%.*s] %.*s",
    path_length, path_string,
    error.length, error_message);
  return;
}
