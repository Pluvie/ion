static inline void reflect_path_failure (
    struct reflect* reflection,
    char* file,
    u64 line
)
{
  char path_string[256] = { 0 };
  i32 path_length = reflect_path_print(reflection, path_string, sizeof(path_string));

  if (path_length <= 0)
    return;

  char error_message[sizeof(error.message)] = { 0 };
  strncpy(error_message, error.message, error.length);

  fail("[%.*s] %.*s",
    path_length, path_string,
    error.length, error_message);
  error.trace[error.trace_count - 1].file = file;
  error.trace[error.trace_count - 1].line = line;

  return;
}
