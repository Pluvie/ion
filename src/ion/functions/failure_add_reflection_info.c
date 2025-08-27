void failure_add_reflection_info (
    struct reflection* rfx
)
{
  char path_string[256] = { 0 };
  string path = { path_string, sizeof(path_string) };

  path.length = reflection_path_print(rfx, path);
  if (path.length <= 0)
    return;

  fail("[%.*s] %.*s", sp(path), sp(failure.message));

  return;
}
