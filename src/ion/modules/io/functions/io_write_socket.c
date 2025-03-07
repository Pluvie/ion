static inline u64 io_write_socket (
    struct io* writer,
    void* data,
    u64 amount
)
{
write_data:
  i32 written_amount = send(writer->socket, data, amount, 0);

  if (unlikely(written_amount < 0)) {
    fail("io: error while writing to socket: %s", strerror(errno));
    return 0;
  }

update_positions:
  writer->length += written_amount;
  writer->cursor += written_amount;
  writer->written_amount = written_amount;

  return written_amount;
}
