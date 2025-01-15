static inline void* io_read_socket (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(reader->allocator == NULL)) {
    fail("io: read from socket impossible due to missing allocator");
    return NULL;
  }

  reader->cursor = 0;
  reader->data = memory_alloc(reader->allocator, amount);

  i32 recv_output = recv(reader->descriptor, reader->data, amount, 0);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    reader->data = NULL;
    reader->length = 0;
    return NULL;
  }

  reader->read_amount = recv_output;
  reader->length = recv_output;
  reader->cursor = recv_output;

  return reader->data;
}
