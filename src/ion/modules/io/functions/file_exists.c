#ifdef ION_INCLUDED
static inline
#endif

bool file_exists (
    char* file_name
)
{
  void* file_stream = fopen(file_name, "r");
  if (file_stream != NULL) {
    fclose(file_stream);
    return true;
  }

  if (errno == ENOENT) {
    return false;
  }

  fail("io: error while opening file: %s", strerror(errno));
  return false;
}
