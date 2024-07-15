static inline void* io_read_memory (
    struct io* reader,
    u64 amount
)
{
  if (reader->cursor + amount > reader->length)
    return NULL;

  void* data = reader->data + reader->cursor;
  reader->cursor += amount;
  return data;
}
