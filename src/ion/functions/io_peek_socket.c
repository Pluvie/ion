static inline void* io_peek_socket (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(reader->allocator == NULL)) {
    fail("io: peek from socket impossible due to missing allocator");
    return NULL;
  }

allocate_buffer:
  u64 allocator_initial_position = reader->allocator->position;
  u64 position = buffer_alloc(reader->allocator, amount);
  reader->data = buffer_data(reader->allocator, position);

perform_read:
  i32 recv_flags = MSG_PEEK;
  if (reader->flags & IO_FLAGS_NO_BUFFERED)
    recv_flags |= MSG_WAITALL;

  i32 recv_output = recv(reader->descriptor, reader->data, amount, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while peeking from socket: %s", strerror(errno));
    reader->data = NULL;
    reader->length = 0;
    return NULL;
  }

adjust_amount:
  u64 amount_effectively_read = recv_output;
  if (amount_effectively_read < amount) {
    amount = amount_effectively_read;
    reader->allocator->position = allocator_initial_position + amount;
  }

update_positions:
  reader->read_amount = amount;
  reader->length += amount;

  return reader->data;
}
