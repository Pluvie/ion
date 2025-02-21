static inline void* io_read_socket (
    struct io* reader,
    void* result,
    u64 amount
)
{
read_data:
  i32 recv_flags = 0;
  if (reader->flags & IO_FLAGS_NO_BUFFERED)
    recv_flags |= MSG_WAITALL;

  byte discarded_result[result == NULL ? amount : 1];

  i32 recv_output = recv(reader->socket,
    result == NULL ? discarded_result : result, amount, recv_flags);

  if (unlikely(recv_output < 0)) {
    fail("io: error while reading from socket: %s", strerror(errno));
    reader->length = 0;
    return NULL;
  }

adjust_amount:
  u64 amount_effectively_read = recv_output;
  if (amount_effectively_read < amount)
    amount = amount_effectively_read;

update_positions:
  reader->length += amount;
  reader->cursor += amount;
  reader->read_amount = amount;
  reader->reads_count++;

  return result;
}
