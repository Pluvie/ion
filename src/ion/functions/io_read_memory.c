static inline void* io_read_memory (
    struct io* reader,
    void* result,
    u64 amount
)
{
  if (unlikely((reader->cursor + amount) > reader->length))
    goto check_overflow;

read_data:
  if (result == NULL)
    result = reader->memory + reader->cursor;
  else
    memcpy(result, reader->memory + reader->cursor, amount);

  reader->cursor += amount;
  reader->read_amount = amount;
  return result;

check_overflow:
  if (reader->flags & IO_FLAGS_NO_OVERFLOW_ERROR) {
    amount = reader->length - reader->cursor;
    goto read_data;
  }

  fail("io: unable to read %li bytes, cursor would overflow", amount);
  return NULL;
}
