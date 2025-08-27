static inline void failure_add_reflection_info (
    struct reflection* rfx
)
{
  char path_string[256] = { 0 };
  int path_length = reflection_path_print(rfx, path_string, sizeof(path_string));

  if (path_length <= 0)
    return;

  char message[sizeof(failure.message)] = { 0 };
  failure.length = snprintf(message, sizeof(message), "[%.*s] %.*s",
    (int32) path_length, path_string, (int32) failure.length, failure.message);
  byte_copy(failure.message, message, sizeof(message));

  return;
}
