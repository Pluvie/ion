#ifdef ION_INCLUDED
static inline
#endif

void* io_peek (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(amount == 0)) {
    fail("io: requested to peek 0 bytes");
    return NULL;
  }

  if (unlikely((reader->mode & IO_MODE_READ) == 0)) {
    fail("io: mode not enabled for reading");
    return NULL;
  }

  switch (reader->channel) {
  case IO_CHANNEL_MEM:
    return io_peek_memory(reader, amount);
  case IO_CHANNEL_FILE:
    return io_peek_file(reader, amount);
  case IO_CHANNEL_SOCK:
    return io_peek_socket(reader, amount);
  }

  fail("io: unsupported channel");
  return NULL;
}
