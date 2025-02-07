#ifdef ION_INCLUDED
static inline
#endif

u64 io_write (
    struct io* writer,
    void* data,
    u64 amount
)
{
  if (unlikely(amount == 0)) {
    fail("io: requested to write 0 bytes");
    return 0;
  }

  if (unlikely((writer->mode & IO_MODE_WRITE) == 0)) {
    fail("io: mode not enabled for writing");
    return 0;
  }

  switch (writer->channel) {
  case IO_CHANNEL_MEM:
    return io_write_memory(writer, data, amount);
  case IO_CHANNEL_FILE:
    return io_write_file(writer, data, amount);
  case IO_CHANNEL_SOCK:
    return io_write_socket(writer, data, amount);
  }

  fail("io: unsupported channel");
  return 0;
}
