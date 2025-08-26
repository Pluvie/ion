int pipe_write (
    struct pipe* pipes,
    void* data,
    int length
)
{
  int written_bytes = write(pipes->writer, data, length);
  if (written_bytes < 0) {
    fail("pipe write error: %s", strerror(errno));
    return 0;
  }

  return written_bytes;
}
