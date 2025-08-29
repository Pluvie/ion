static inline struct io io_init (
    struct reflection* rfx,
    memory* allocator
)
{
  return (struct io) { 0 };
}

static inline struct io io_init_with_buffer (
    struct reflection* rfx,
    memory* allocator
)
{
  struct io io = { 0 };
  io.buffer = alloc(sizeof(memory));
  *io.buffer = memory_init(1024);
  return io;
}
