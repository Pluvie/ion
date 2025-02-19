static inline u64 io_write_memory (
    struct io* writer,
    void* data,
    u64 amount
)
{
  if (unlikely(writer->cursor + amount > writer->length)) {
    fail("io: unable to write, memory exhausted");
    return 0;
  }

  memcpy(writer->memory + writer->cursor, data, amount);

  writer->cursor += amount;
  writer->written_amount = amount;
  writer->writes_count++;

  return amount;
}
