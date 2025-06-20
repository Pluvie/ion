static inline struct io io_open_pipe (
    int descriptor
)
{
  return (struct io) {
    .channel = IO_PIPE,
    .pipe = descriptor,
  };
}
