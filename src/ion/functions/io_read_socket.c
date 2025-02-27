static inline void* io_read_socket (
    struct io* reader,
    u64 amount
)
{
  void* result = NULL;

read_data:
  if (reader->cursor + amount <= reader->allocator->position) {
    result = buffer_data(reader->allocator, reader->cursor);
    goto update_positions;
  }

  u64 amount_to_allocate = reader->cursor + amount - reader->allocator->position;
  u64 allocated_position = buffer_alloc(reader->allocator, amount_to_allocate);
  void* allocated_data = buffer_data(reader->allocator, allocated_position);

  i32 recv_flags = 0;
  if (reader->flags & IO_FLAGS_UNBUFFERED)
    recv_flags |= MSG_WAITALL;

  i32 recv_output = recv(reader->socket, allocated_data, amount, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    reader->length = 0;
    return NULL;
  }

  result = allocated_data;

adjust_amount:
  u64 amount_effectively_read = recv_output;
  if (amount_effectively_read < amount) {
    reader->allocator->position -= amount - amount_effectively_read;
    amount = amount_effectively_read;
  }

update_positions:
  reader->length += amount;
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
