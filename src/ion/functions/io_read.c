void* io_read (
    struct io* reader,
    u64 amount
)
{
  if (unlikely((reader->flags & IO_READ) == 0))
    return NULL;

  if (reader->cursor + amount > reader->length)
    return NULL;

  void* data = reader->data + reader->cursor;
  reader->cursor += amount;
  return data;
}
