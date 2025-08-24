struct io io_open_slice (
    slice slice,
    int unused
)
{
  return (struct io) {
    .channel = IO_MEMORY,
    .memory = slice.pointer,
    .length = slice.length,
  };
}
