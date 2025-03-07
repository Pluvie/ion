#ifdef ION_INCLUDED
static inline
#endif

void* io_peek (
    struct io* reader,
    u64 amount
)
{
  void* result = io_read(reader, amount);
  if (error.occurred)
    return NULL;

  reader->cursor -= reader->read_amount;
  return result;
}
