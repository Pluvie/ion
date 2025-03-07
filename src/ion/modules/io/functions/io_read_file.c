static inline void* io_read_file (
    struct io* io,
    u64 amount
)
{
  void* result = NULL;

adjust_amount:
  /**
   * If the amount to read, added to the cursor, falls out from the file length,
   *
   *               length
   *                 │
   *  ┌──────────────▼
   *  │              │
   *  └───────────▲──┘     ▲
   *       cursor │        │
   *               ────────
   *               + amount
   * 
   * there are two possible cases:
   *
   *   1. The cursor was already at maximum length: in this case fail with an error
   *      that tells that the end of file was reached.
   *   2. The cursor was before the maximum length: in this case the amount is adjusted
   *      to match the remaining amount between the cursor and the length. */

  i64 amount_remaining = io->length - io->cursor;

  if (amount_remaining <= 0) {
    fail("io: end of file reached");
    return NULL;
  }

  if (amount > amount_remaining)
    amount = amount_remaining;

check_allocation:
  /**
   * If the cursor plus the amount falls into the buffered data, return the data
   * directly from the buffer, and does not perform any system call to `fread`.
   *
   * Otherwise, allocates an amount equal to the buffer size -- or equal to the
   * asked amount, if it exceeds the buffer size -- and perform the system call to
   * `fread`, storing the retrieved data into the allocated buffer. */
  if (io->cursor + amount <= io_buffer_limit(io)) {
    result = io_buffer_data(io);
    goto update_positions;
  }

  u64 amount_to_allocate = io->buffer.size;
  u64 amount_overflowing = io->cursor + amount - io_buffer_limit(io);
  if (amount_overflowing > amount_to_allocate)
    amount_to_allocate = amount_overflowing;

  u64 allocated_position = buffer_alloc(&(io->buffer.allocator), amount_to_allocate);
  void* allocated_data = buffer_data(&(io->buffer.allocator), allocated_position);

read_data:
  i32 fread_output = fread(allocated_data, amount_to_allocate, 1, io->file);

  if (unlikely(fread_output != 1)) {
    fail("io: error while reading from file: %s", strerror(errno));
    return NULL;
  }

check_retention:
  io_buffer_chip_away(io);
  result = io_buffer_data(io);

update_positions:
  io->cursor += amount;
  io->read_amount = amount;
  io->reads_count++;

  return result;
}
