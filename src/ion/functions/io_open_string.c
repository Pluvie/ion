struct io io_open_string (
    string string,
    int unused
)
{
  return (struct io) {
    .channel = IO_MEMORY,
    .memory = string.pointer,
    .length = string.length,
  };
}
