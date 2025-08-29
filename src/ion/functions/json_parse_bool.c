static inline bool json<T>_parse_bool (
    struct io* io,
    T* source,
    bool* result
)
{
  char* data = io_read(io, source, lengthof("false"));

  if (char_compare("true", data, lengthof("true")) == 0) {
    *result = true;
    return true;
  }

  if (char_compare("false", data, lengthof("false")) == 0) {
    *result = false;
    return true;
  }

  if (likely(*data != 0))
    io->cursor -= lengthof("false");

  return false;
}
