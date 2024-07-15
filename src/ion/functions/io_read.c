void* io_read (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(amount == 0))
    return NULL;

  if (unlikely((reader->flags & IO_READ) == 0))
    return NULL;

  switch (reader->type) {
  case IO_TYPE_MEM:
    return io_read_memory(reader, amount);
  case IO_TYPE_FILE:
    return io_read_file(reader, amount);
  case IO_TYPE_SOCK:
    return io_read_socket(reader, amount);
  }

  return NULL;
}
