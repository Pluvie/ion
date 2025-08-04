static inline slice io_buffer_read (
    struct io* io,
    int amount
)
{
  if (unlikely(io->buffer.data == NULL))
    return io_buffer_init(io, amount);

  slice result = { 0 };

  if (io->buffer.cursor + amount <= io->buffer.end)
    goto read_from_buffer;
  else
    goto read_from_channel;

read_from_buffer:
  /* Reads directly and only from the buffer, since the amount completely fits into
   * the buffer available data.

      amount:      ■■■■■■
              ┌────────────────────────────────────────┐
      buffer: │▓▓▓▓▒▒▒▒▒▒▒▒                            │
              └────┬──────┬────────────────────────────┘
                   ▼      ▼           
                cursor   end */

  int window_size = 2*io->buffer.size;

  if (!io->buffer.retained && io->buffer.end > window_size) {
    /* If the buffer is not retained and contains data for more than 2 times the buffer
     * size, chips away a portion of the buffer in order to reduce memory usage. */
    int chip_begin = io->buffer.end - window_size;
    int chipped_capacity = io->buffer.end - chip_begin;

    void* old_data = io->buffer.data;
    void* new_data = malloc(chipped_capacity);
    if (unlikely(new_data == NULL))
      fatal("%li, malloc failed", chipped_capacity);

    memcpy(new_data, old_data + chip_begin, chipped_capacity);
    free(old_data);
    io->buffer.data = new_data;

    io->buffer.end = chipped_capacity;
    io->buffer.cursor -= chip_begin;
  }

  result.data = io->buffer.data + io->buffer.cursor;
  result.length = amount;
  io->buffer.cursor += amount;

  return result;

read_from_channel:
  /* Reads data from the channel, since the amount is exceeding the buffer available
   * data. Before doing so, extends the buffer in order to accomodate the new data
   * read from the channel.

      amount:      ■■■■■■■■■■■■■■
              ┌────────────────────────────────────────┐
      buffer: │▓▓▓▓▒▒▒▒▒▒▒▒                            │
              └────┬──────┬────────────────────────────┘
                   ▼      ▼           
                cursor   end */

  int buffer_available_quantity = io->buffer.end - io->buffer.cursor;
  int extended_capacity = io->buffer.end + io->buffer.size;
  if (amount > io->buffer.size)
    extended_capacity += amount;

  io->buffer.data = realloc(io->buffer.data, extended_capacity);
  if (unlikely(io->buffer.data == NULL))
    fatal("%li, realloc failed", extended_capacity);

  void* storage = io->buffer.data + io->buffer.end; 
  int channel_read_quantity = extended_capacity - io->buffer.end;
  slice channel_result = io_read_channel(io, channel_read_quantity, storage);
  if (unlikely(error.occurred))
    return result;

  result.data = io->buffer.data + io->buffer.cursor;

  /* If the underlying channel returns less data than the amount asked, we must update
   * the buffer pointers accordingly. */
  if (channel_result.length < channel_read_quantity) {
    io->buffer.end += channel_result.length;
    io->buffer.cursor = io->buffer.end;
    result.length = buffer_available_quantity + channel_result.length;

  } else {
    io->buffer.end = extended_capacity;
    io->buffer.cursor += amount;
    result.length = amount;
  }

  return result;
}
