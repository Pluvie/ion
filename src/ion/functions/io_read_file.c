static inline void* io_read_file (
    struct io* reader,
    void* result,
    u64 amount
)
{
adjust_amount:
  u64 amount_remaining = reader->length - reader->cursor;

  if (amount_remaining == 0) {
    fail("io: end of file reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

read_data:
  i32 fread_output = fread(result, amount, 1, reader->file);

  if (unlikely(fread_output != 1)) {
    fail("io: error while reading from file: %s", strerror(errno));
    return NULL;
  }

update_positions:
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
