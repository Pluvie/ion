static inline void* io_peek_file (
    struct io* reader,
    void* result,
    u64 amount
)
{
  result = io_read_file(reader, result, amount);
  fseek(reader->file, -(i64) reader->read_amount, SEEK_CUR);
  reader->cursor -= reader->read_amount;

  return result;
}
