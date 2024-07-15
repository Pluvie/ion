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

  switch (writer->type) {
  case IO_TYPE_MEM:
    goto write_memory;
  case IO_TYPE_FILE:
    goto write_file;
  case IO_TYPE_SOCK:
    goto write_socket;
  }

write_memory:
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

write_file:
  fprintf(stderr, "not implemented: io write for type IO_TYPE_FILE\n");
  abort();

write_socket:
  i32 written_amount = send(writer->descriptor, data, amount, 0);

  if (unlikely(written_amount < 0))
    return 0;

  return written_amount;
}
