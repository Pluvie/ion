static inline void* io_read_socket (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(reader->allocator == NULL)) {
    fail("io: read from socket impossible due to missing allocator");
    return NULL;
  }

allocate_buffer:
  u64 position = buffer_alloc(reader->allocator, amount);
  reader->data = buffer_data(reader->allocator, position);

perform_read:
  i32 recv_flags = 0;
  if (reader->flags & IO_FLAGS_NO_BUFFERED)
    recv_flags |= MSG_WAITALL;

  i32 recv_output = recv(reader->descriptor, reader->data, amount, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    reader->data = NULL;
    reader->length = 0;
    return NULL;
  }

adjust_amount:
  u64 amount_effectively_read = recv_output;
  if (amount_effectively_read < amount) {
    amount = amount_effectively_read;
    reader->allocator->position = position + amount;
  }

update_positions:
  reader->data = buffer_data(reader->allocator, 0);
  reader->read_amount = amount;
  reader->length += amount;
  reader->cursor += amount;

  return buffer_data(reader->allocator, position);
}
