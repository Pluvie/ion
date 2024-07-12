u64 io_write (
    struct io* writer,
    void* data,
    u64 amount
)
{
  if (unlikely(amount == 0))
    return 0;

  if (unlikely((writer->flags & IO_WRITE) == 0))
    return 0;

  if (writer->cursor + amount > writer->length) {
    if (writer->allocator == NULL)
      return 0;

    u64 new_length = writer->length == 0 ? amount : writer->length * 2;
    void* new_data = memory_alloc_zero(writer->allocator, new_length);
    memcpy(new_data, writer->data, writer->length);
    writer->length = new_length;
    writer->data = new_data;
  }

  memcpy(writer->data + writer->cursor, data, amount);
  writer->cursor += amount;
  return amount;
}
