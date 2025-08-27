void io_buffer_read (
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
    byte_copy(new_data, old_data + chip_begin, chipped_capacity);
    alloc_release(old_data);
    buffer->data.pointer = new_data;
    buffer->data.length = chipped_capacity;
    buffer->cursor -= chip_begin;
  }

  io->result.pointer = buffer->data.pointer + buffer->cursor;
  io->result.length = amount;
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

  buffer->data.pointer = alloc_resize_zero(
    buffer->data.pointer, buffer->data.length, extended_capacity);

  int channel_asked_bytes = extended_capacity - buffer->data.length;
  io_channel_read(io, channel_asked_bytes, buffer->data.pointer + buffer->data.length);
  if (unlikely(failure.occurred))
    return;

  int channel_read_bytes = io->result.length;
  int available_amount = buffer_available_quantity + channel_read_bytes;

  /* If the underlying channel returns less data than the amount asked, we must update
   * the buffer pointers accordingly. */
  io->result.pointer = buffer->data.pointer + buffer->cursor;
  buffer->data.length += channel_read_bytes;

  if (amount <= available_amount) {
    io->result.length = amount;
    buffer->cursor += amount;

  } else {
    io->result.length = available_amount;
    buffer->cursor += available_amount;
  }
}
