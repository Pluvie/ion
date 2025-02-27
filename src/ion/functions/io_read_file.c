static inline void* io_read_file (
    struct io* reader,
    u64 amount
)
{
  void* result = NULL;

adjust_amount:
  i64 amount_remaining = reader->length - reader->cursor;

  if (amount_remaining <= 0) {
    fail("io: end of file reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

read_data:
  if (reader->cursor + amount <= reader->allocator->position) {
    result = buffer_data(reader->allocator, reader->cursor);
    goto update_positions;
  }

  u64 amount_to_allocate = reader->cursor + amount - reader->allocator->position;
  u64 allocated_position = buffer_alloc(reader->allocator, amount_to_allocate);
  void* allocated_data = buffer_data(reader->allocator, allocated_position);

  i32 fread_output = fread(allocated_data, amount_to_allocate, 1, reader->file);

  if (unlikely(fread_output != 1)) {
    fail("io: error while reading from file: %s", strerror(errno));
    return NULL;
  }

  result = buffer_data(reader->allocator, reader->cursor);

update_positions:
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
