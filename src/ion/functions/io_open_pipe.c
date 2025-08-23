static inline struct io io_open_pipe (
    struct pipe* pipes
)
{
  return (struct io) {
    .channel = IO_PIPE,
    .pipe = pipes,
  };
}
