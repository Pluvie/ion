static inline void* io_read_memory (
    struct io* reader,
    u64 amount
)
{
  if ((reader->cursor + amount) > reader->length) {
    fail("io: unable to read %li bytes, cursor would exceed length", amount);
    return NULL;
  }

  initialize(data, void*,
    pointer_offset(reader->data, reader->cursor));

  assign_to(reader->cursor, reader->cursor + amount);

  return data;
}
