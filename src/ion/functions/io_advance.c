static inline void io_advance_direct (
    struct io_direct* io,
    int amount
)
{
  if (likely(io->cursor < io->end)) {
    io->cursor += amount;
    return;
  }

  io->cursor = EMPTY_STRING;
  return;
}



static inline void io_advance_buffered (
    struct io_buffered* io,
    int amount
)
{
  fail("to be implemented");
  return;
}
