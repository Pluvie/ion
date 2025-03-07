static inline u64 io_write_file (
    struct io* writer,
    void* data,
    u64 amount
)
{
write_data:
  i32 fwrite_output = fwrite(data, amount, 1, writer->file);

  if (unlikely(fwrite_output != 1)) {
    fail("io: error while writing from file: %s", strerror(errno));
    return 0;
  }

update_positions:
  writer->cursor += amount;
  writer->length += amount;
  writer->written_amount = amount;

  return writer->written_amount;
}
