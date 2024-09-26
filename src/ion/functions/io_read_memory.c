static inline void* io_read_memory (
    struct io* reader,
    u64 amount
)
{
  if ((reader->cursor + amount) > reader->length) {
    fail("io: unable to read %li bytes, cursor would exceed length", amount);
    return NULL;
  }

  void* data = reader->data + reader->cursor;
  reader->cursor += amount;
  return data;
}
