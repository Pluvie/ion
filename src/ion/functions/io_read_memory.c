static inline void* io_read_memory (
    struct io* reader,
    void* result,
    u64 amount
)
{
adjust_amount:
  u64 amount_remaining = reader->length - reader->cursor;

  if (amount_remaining == 0) {
    fail("io: end of input reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

read_data:
  if (result == NULL)
    result = reader->memory + reader->cursor;
  else
    memcpy(result, reader->memory + reader->cursor, amount);

update_positions:
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
