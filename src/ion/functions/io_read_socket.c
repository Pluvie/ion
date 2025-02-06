static inline void* io_read_socket (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(reader->allocator == NULL)) {
    fail("io: read from socket impossible due to missing allocator");
    return NULL;
  }

  /* if (reader->allocator->position */
  u64 position = buffer_alloc(reader->allocator, amount);
  reader->data = buffer_data(reader->allocator, position);

  i32 recv_flags = 0;
  if (reader->flags & IO_NO_BUFFERED)
    recv_flags |= MSG_WAITALL;

  i32 recv_output = recv(reader->descriptor, reader->data, amount, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    reader->data = NULL;
    reader->length = 0;
    return NULL;
  }

  reader->read_amount = recv_output;
  reader->length += recv_output;
  reader->cursor += recv_output;

  return reader->data;
}
