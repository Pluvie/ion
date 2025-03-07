static inline void* io_read_memory (
    struct io* io,
    u64 amount
)
{
adjust_amount:
  i64 amount_remaining = io->length - io->cursor;

  if (amount_remaining <= 0) {
    fail("io: end of memory reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

read_data:
  void* result = io->memory + io->cursor;

update_positions:
  io->cursor += amount;
  io->read_amount = amount;
  io->reads_count++;

  return result;
}
