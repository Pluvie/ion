static inline void reflection_error_extract (
    struct reflection* rfx
)
{
  char path_string[256] = { 0 };
  int path_length = reflection_path_print(rfx, path_string, sizeof(path_string));

  if (path_length <= 0)
    return;

  char message[sizeof(error.message)] = { 0 };
  error.length = snprintf(message, sizeof(message), "[%.*s] %.*s",
    (int32) path_length, path_string, (int32) error.length, error.message);
  memcpy(error.message, message, sizeof(message));

  return;
}
