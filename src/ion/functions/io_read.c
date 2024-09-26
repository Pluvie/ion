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

  if (unlikely((reader->flags & IO_READ) == 0)) {
    fail("io: not flagged for reading");
    return NULL;
  }

  switch (reader->type) {
  case IO_TYPE_MEM:
    return io_read_memory(reader, amount);
  case IO_TYPE_FILE:
    return io_read_file(reader, amount);
  case IO_TYPE_SOCK:
    return io_read_socket(reader, amount);
  }

  fail("io: unsupported type");
  return NULL;
}
