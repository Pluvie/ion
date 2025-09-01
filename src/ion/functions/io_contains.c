static inline bool io_contains_direct (
    struct io_direct* io,
    void* value,
    int length
)
{
  if (char_compare(io->cursor, value, length) == 0) {
    io_advance(io, length);
    return true;
  }

  return false;
}



static inline bool io_contains_buffered (
    struct io_buffered* io,
    void* value,
    int length
)
{
  fail("to be implemented");
  return false;
}
