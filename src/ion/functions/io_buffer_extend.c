static inline void io_buffer_extend (
    struct io* io,
    int amount
)
{
  int copy_begin = 0;
  int copy_end = io->buffer.end;

  if (io->buffer.cursor > io->buffer.size)
    copy_begin = io->buffer.end - io->buffer.size;

  if (copy_begin < 0)
    copy_begin = 0;

  int copy_amount = copy_end - copy_begin;
  int new_capacity = copy_amount + io->buffer.size;
  if (amount > io->buffer.size)
    new_capacity = copy_amount + amount;

  void* old_data = io->buffer.data;
  void* new_data = malloc(new_capacity);
  if (unlikely(new_data == NULL))
    fatal("%li, not enough memory", new_capacity);

  memcpy(new_data, old_data, copy_amount);
  free(old_data);

  io->buffer.data = new_data;
  io->buffer.capacity = new_capacity;
  if (copy_begin > 0)
    io->buffer.cursor = copy_begin;
}
