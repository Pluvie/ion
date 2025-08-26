int pipe_read (
    struct pipe* pipes,
    void* address,
    int amount
)
{
  int read_bytes = read(pipes->reader, address, amount);
  if (read_bytes < 0) {
    fail("pipe read error: %s", strerror(errno));
    return 0;
  }

  return read_bytes;
}
