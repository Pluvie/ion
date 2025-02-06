#ifdef ION_INCLUDED
static inline
#endif

void* io_peek (
    struct io* reader,
    u64 amount
)
{
  if (unlikely((reader->mode & IO_READ) == 0))
    return NULL;

  if (reader->cursor + amount > reader->length)
    return NULL;

  void* data = reader->data + reader->cursor;
  return data;
}
