static inline void* io_read_memory (
    struct io* reader,
    u64 amount
)
{
adjust_amount:
  i64 amount_remaining = reader->length - reader->cursor;

  if (amount_remaining <= 0) {
    fail("io: end of memory reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

read_data:
  void* result = reader->memory + reader->cursor;

update_positions:
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
