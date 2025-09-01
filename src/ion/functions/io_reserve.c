static inline void io_reserve_direct (
    struct io_direct* io,
    int amount
)
{
  return;
}



static inline void io_reserve_buffered (
    struct io_buffered* io,
    int amount
)
{
  fail("to be implemented");
  return;
}
