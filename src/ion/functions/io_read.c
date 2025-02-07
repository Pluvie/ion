#ifdef ION_INCLUDED
static inline
#endif

void* io_read (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(amount == 0)) {
    fail("io: requested to read 0 bytes");
    return NULL;
  }

  if (unlikely((reader->mode & IO_MODE_READ) == 0)) {
    fail("io: mode not enabled for reading");
    return NULL;
  }

  switch (reader->channel) {
  case IO_CHANNEL_MEM:
    return io_read_memory(reader, amount);
  case IO_CHANNEL_FILE:
    return io_read_file(reader, amount);
  case IO_CHANNEL_SOCK:
    return io_read_socket(reader, amount);
  }

  fail("io: unsupported channel");
  return NULL;
}
