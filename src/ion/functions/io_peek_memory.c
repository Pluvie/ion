static inline void* io_peek_memory (
    struct io* reader,
    u64 amount
)
{
  if ((reader->cursor + amount) > reader->length) {
    if (!(reader->flags & IO_FLAGS_NO_OVERFLOW_ERROR))
      fail("io: unable to peek %li bytes, cursor would overflow", amount);
    reader->read_amount = reader->length - reader->cursor;
    return NULL;
  }

  void* data = reader->data + reader->cursor;
  reader->read_amount = amount;
  return data;
}
