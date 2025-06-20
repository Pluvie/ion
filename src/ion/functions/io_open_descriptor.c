static inline struct io io_open_descriptor (
    int descriptor,
    int length
)
{
  struct stat stat;
  if (fstat(descriptor, &stat) != 0) {
    fail("error while calling `fstat` for descriptor %li: %s",
      descriptor, strerror(errno));
    return (struct io) { 0 };
  }

  if (S_ISSOCK(stat.st_mode))
    return io_open_socket(descriptor);

  if (S_ISFIFO(stat.st_mode))
    return io_open_pipe(descriptor);
  
  if (S_ISREG(stat.st_mode))
    return io_open_file(descriptor, length, &stat);

  fail("cannot determine descriptor %li type: neither socket, pipe, nor file",
    descriptor);
  return (struct io) { 0 };
}
