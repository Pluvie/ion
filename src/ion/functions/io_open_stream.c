struct io io_open_stream (
    struct stream* stream,
    int length
)
{
  struct io io = {
    .channel = IO_STREAM,
    .stream = stream,
  };

  if (length > 0)
    io.length = length;
  else
    io.length = stream_size(stream);

  return io;
}
