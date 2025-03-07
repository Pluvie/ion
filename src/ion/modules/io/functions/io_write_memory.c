static inline u64 io_write_memory (
    struct io* writer,
    void* data,
    u64 amount
)
{
write_data:
  if (unlikely(writer->cursor + amount > writer->length)) {
    fail("io: unable to write, memory exhausted");
    return 0;
  }

  memcpy(writer->memory + writer->cursor, data, amount);

update_positions:
  writer->cursor += amount;
  writer->written_amount = amount;

  return amount;
}
