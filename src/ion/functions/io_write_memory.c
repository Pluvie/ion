static inline u64 io_write_memory (
    struct io* writer,
    void* data,
    u64 amount
)
{
  if (writer->cursor + amount > writer->length) {
    if (writer->allocator == NULL) {
      fail("io: unable to write, memory exhausted and no allocator specified");
      return 0;
    }

    u64 new_length = writer->length * 2;
    if (new_length < amount)
      new_length = amount;

    u64 new_position = buffer_alloc_zero(writer->allocator, new_length);
    void* new_data = buffer_data(writer->allocator, new_position);

    memcpy(new_data, writer->data, writer->length);
    writer->length = new_length;
    writer->data = new_data;
  }

  memcpy(writer->data + writer->cursor, data, amount);
  writer->cursor += amount;
  writer->written_amount = amount;
  return amount;
}
