static inline void io_buffer_init (
    struct io* io,
    int initial_capacity
)
{
  if (unlikely(io->buffer != NULL))
    return;

  if (initial_capacity <= 0)
    initial_capacity = 1024;

  io->buffer = alloc(sizeof(*io->buffer));
  *io->buffer = memory_init(initial_capacity);
}
