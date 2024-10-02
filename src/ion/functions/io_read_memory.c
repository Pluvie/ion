static inline void* io_read_memory (
    struct io* reader,
    u64 amount
)
{
  if ((reader->cursor + amount) > reader->length) {
    if (!(reader->flags & IO_NO_OVERFLOW_ERROR))
      fail("io: unable to read %li bytes, cursor would overflow", amount);
    reader->read_amount = reader->length - reader->cursor;
    return NULL;
  }

  void* data = reader->data + reader->cursor;
  reader->cursor += amount;
  reader->read_amount = amount;
  return data;
}
