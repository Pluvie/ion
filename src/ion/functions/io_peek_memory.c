static inline void* io_peek_memory (
    struct io* reader,
    void* result,
    u64 amount
)
{
  result = io_read_memory(reader, result, amount);
  if (error.occurred)
    return NULL;

  reader->cursor -= reader->read_amount;
  return result;
}
