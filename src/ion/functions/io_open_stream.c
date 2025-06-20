struct io io_open_stream (
    void* stream,
    int length
)
{
  struct io io = {
    .channel = IO_STREAM,
    .stream = stream,
  };

  if (length > 0) {
    io.length = length;
    return io;
  }

  int initial_position = ftell(io.stream);
  fseek(io.stream, 0L, SEEK_END);
  io.length = ftell(io.stream);
  fseek(io.stream, initial_position, SEEK_SET);

  return io;
}
