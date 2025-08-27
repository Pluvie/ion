struct io io_open_pipe (
    struct pipe* pipes,
    int
)
{
  return (struct io) {
    .channel = IO_PIPE,
    .pipe = pipes,
  };
}
