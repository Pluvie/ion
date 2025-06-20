struct io io_open_memory (
    void* memory,
    int length
)
{
  return (struct io) {
    .channel = IO_MEMORY,
    .memory = memory,
    .length = length
  };
}
