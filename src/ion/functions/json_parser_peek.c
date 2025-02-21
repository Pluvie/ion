static inline void* json_parser_peek (
    struct io* input,
    struct buffer* allocator,
    u64* max_position
)
{
  void* peek_window = NULL;

  switch (input->channel) {
  case IO_CHANNEL_MEM:
    *max_position = input->length - input->cursor;

    peek_window = io_peek(input, NULL, *max_position);
    if (error.occurred)
      return NULL;

    return peek_window;

  case IO_CHANNEL_FILE:
  case IO_CHANNEL_SOCK:
    u64 capacity = allocator->capacity * 2;
    if (capacity == 0)
      capacity = 256;

    buffer_release(allocator);
    *allocator = buffer_init(capacity);

    buffer_alloc(allocator, allocator->capacity);
    peek_window = buffer_data(allocator, 0);

    io_peek(input, peek_window, allocator->capacity);
    if (error.occurred)
      return NULL;

    if (input->read_amount < allocator->capacity)
      *max_position = input->read_amount;

    return peek_window;
  }

  return NULL;
}
