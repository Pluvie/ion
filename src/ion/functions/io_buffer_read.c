static inline void io_buffer_read (
    struct io* io,
    int amount
)
{
  typeof(io->buffer)* buffer = &(io->buffer);

  if (unlikely(buffer->data.pointer == NULL))
    return io_buffer_init(io, amount);

  if (buffer->cursor + amount <= buffer->data.length)
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

  int window_size = 2 * buffer->size;

  if (!buffer->retained && buffer->data.length > window_size) {
    /* If the buffer is not retained and contains data for more than 2 times the buffer
     * size, chips away a portion of the buffer in order to reduce memory usage. */
    int chip_begin = buffer->data.length - window_size;
    int chipped_capacity = buffer->data.length - chip_begin;

    void* old_data = buffer->data.pointer;
    void* new_data = alloc_zero(chipped_capacity);
    memcpy(new_data, old_data + chip_begin, chipped_capacity);
    free(old_data);
    buffer->data.pointer = new_data;
    buffer->data.length = chipped_capacity;
    buffer->cursor -= chip_begin;
  }

  io->data.pointer = buffer->data.pointer + buffer->cursor;
  io->data.length = amount;
  buffer->cursor += amount;
  return;

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

  int buffer_available_quantity = buffer->data.length - buffer->cursor;
  int extended_capacity = buffer->data.length + buffer->size;
  if (amount > buffer->size)
    extended_capacity += amount;

  void* old_data = buffer->data.pointer;
  void* new_data = alloc_zero(buffer->data, extended_capacity);
  memcpy(new_data, old_data, buffer->data.length);
  free(old_data);
  buffer->data.pointer = new_data;

  void* storage = buffer->data.pointer + buffer->data.length; 
  int channel_read_quantity = extended_capacity - buffer->data.length;
  io_channel_read(io, channel_read_quantity, storage);
  if (unlikely(failure.occurred))
    return;


  /* If the underlying channel returns less data than the amount asked, we must update
   * the buffer pointers accordingly. */
  int read_bytes = io->data.length;
  io->data.pointer = buffer->data.pointer + buffer->cursor;

  if (read_bytes < channel_read_quantity) {
    io->data.length = buffer_available_quantity + read_bytes;
    buffer->data.length += read_bytes;
    buffer->cursor += read_bytes;

  } else {
    io->data.length = amount;
    buffer->data.length = extended_capacity;
    buffer->cursor += amount;
  }

  return;
}
