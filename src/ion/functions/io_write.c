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

  if (unlikely((writer->flags & IO_WRITE) == 0)) {
    fail("io: not flagged for writing");
    return 0;
  }

  switch (writer->type) {
  case IO_TYPE_MEM:
    return io_write_memory(writer, data, amount);
  case IO_TYPE_FILE:
    return io_write_file(writer, data, amount);
  case IO_TYPE_SOCK:
    return io_write_socket(writer, data, amount);
  }

  fail("io: unsupported type");
  return 0;
}
