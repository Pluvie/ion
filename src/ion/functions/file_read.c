int file_read (
    struct file* file,
    void* address,
    int amount
)
{
#if platform(LINUX)
  int read_bytes = read(file->descriptor, address, amount);
  if (unlikely(read_bytes < 0)) {
    fail("file read error: %s", strerror(errno));
    return 0;
  }

  return read_bytes;

#else
  #error "Unsupported platform."
#endif
}
