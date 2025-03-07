static inline void* io_read_socket (
    struct io* io,
    u64 amount
)
{
  void* result = NULL;

check_allocation:
  /**
   * If the cursor plus the amount falls into the buffered data, return the data
   * directly from the buffer, and does not perform any system call to `recv`.
   *
   * Otherwise, allocates an amount equal to the buffer size -- or equal to the
   * asked amount, if it exceeds the buffer size -- and perform the system call to
   * `recv`, storing the retrieved data into the allocated buffer. */
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
  i32 recv_flags = 0;
  if (io->flags & IO_FLAGS_WAIT_ALL)
    recv_flags |= MSG_WAITALL;

  i32 recv_output = recv(io->socket, allocated_data, amount_to_allocate, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    io->length = 0;
    return NULL;
  }

adjust_amount:
  /**
   * If the amount of data returned by the system call `recv` is lesser than the
   * requested amount, adjust the buffer allocated position accordingly.
   *
   * Also, since a socket io does not know the length of its data a priori, the
   * amount read is added to the io read, indicating that data was available. */
  u64 amount_effectively_read = recv_output;
  if (amount_effectively_read < amount) {
    io->buffer.allocator.position -= amount - amount_effectively_read;
    amount = amount_effectively_read;
  }

  io->length += amount;

check_retention:
  io_buffer_chip_away(io);
  result = io_buffer_data(io);

update_positions:
  io->cursor += amount;
  io->read_amount = amount;
  io->reads_count++;

  return result;
}
