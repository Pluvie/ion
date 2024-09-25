static inline void* io_read_socket (
    struct io* reader,
    u64 amount
)
{
  if (unlikely(reader->allocator == NULL)) {
    fail("io: read from socket impossible due to missing allocator");
    return NULL;
  }

  assign_to(reader->cursor, 0);
  assign_to(reader->data, memory_alloc(reader->allocator, amount));
  initialize(read_amount, u64, 0);

  while (read_amount < amount) {
    initialize(recv_output, i32,
      call(recv,
        reader->descriptor,
        pointer_offset(reader->data, read_amount),
        amount - read_amount,
        0));

    if (likely(recv_output > 0)) {
      assign_to(read_amount, read_amount + recv_output);
      continue;
    }

    if (read_amount == 0) {
      fail("io: error while reading from socket: %s",
        call(strerror, errno));

      assign_to(reader->data, NULL);
      assign_to(reader->length, 0);
      return NULL;
    }

    break;
  }

  assign_to(reader->length, read_amount);
  assign_to(reader->cursor, read_amount);
  return reader->data;
}
