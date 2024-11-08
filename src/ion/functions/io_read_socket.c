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
  u64 read_amount = 0;

  while (read_amount < amount) {
    i32 recv_avail;
    ioctl(reader->descriptor, FIONREAD, &recv_avail);
    if (recv_avail <= 0)
      break;

    i32 recv_output = recv(
      reader->descriptor, reader->data + read_amount, amount - read_amount, 0);

    if (likely(recv_output > 0)) {
      read_amount += recv_output;
      continue;
    }

    if (read_amount == 0) {
      fail("io: error while reading from socket: %s", strerror(errno));
      reader->data = NULL;
      reader->length = 0;
      return NULL;
    }

    break;
  }

  reader->length = read_amount;
  reader->cursor = read_amount;
  reader->read_amount = read_amount;
  return reader->data;
}
