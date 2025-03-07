static inline void error_add_reflection_path (
    struct reflection* rfx
)
{
  char path_string[256] = { 0 };
  i32 path_length = reflection_path_print(rfx, path_string, sizeof(path_string));

  if (path_length <= 0)
    return;

  char message[sizeof(error.message)] = { 0 };
  error.length = snprintf(message, sizeof(message), "[%.*s] %.*s",
    path_length, path_string, error.length, error.message);
  memcpy(error.message, message, sizeof(message));

  return;
}
