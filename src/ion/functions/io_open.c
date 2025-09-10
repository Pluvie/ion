static inline struct io io_open_string (
    string* source,
    struct reflection* rfx,
    memory* allocator
)
{
  struct io_direct* io_direct = memory_alloc(allocator, sizeof(struct io_direct));
  *io_direct = (struct io_direct) {
    .data = source,
    .cursor = source->pointer,
    .end = source->pointer + source->length,
  };

  struct io result = {
    .direct = io_direct,
    .type = IO_DIRECT,
    .rfx = rfx,
    .allocator = allocator,
  };
  return result;
}



static inline struct io io_open_pipe (
    struct pipe* source,
    struct reflection* rfx,
    memory* allocator
)
{
  struct io_buffered* io_buffered = memory_alloc(allocator, sizeof(struct io_buffered));

  *io_buffered = (struct io_buffered) {
    .channel = IO_PIPE,
    .pipe = source,
  };
  io_buffered->buffer.window_size = 1024;
  io_reserve(io_buffered, io_buffered->buffer.window_size);

  struct io result = {
    .buffered = io_buffered,
    .type = IO_BUFFERED,
    .rfx = rfx,
    .allocator = allocator,
  };

  return result;
}
