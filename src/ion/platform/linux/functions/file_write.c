int file_write (
    struct file* file,
    void* data,
    int length
)
{
  int written_bytes = write(file->descriptor, data, length);
  if (unlikely(written_bytes < 0)) {
    fail("file write error: %s", strerror(errno));
    return 0;
  }

  return written_bytes;
}
