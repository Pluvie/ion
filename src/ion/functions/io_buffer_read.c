static inline slice io_buffer_read (
    struct io* io,
    int amount
)
{
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
      buffer: │▓▓▓▓▒▒▒▒▒▒▒▒          │                 │
              └────┬──────┬──────────┬─────────────────┘
                   ▼      ▼          ▼
                cursor   end      capacity */

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
      buffer: │▓▓▓▓▒▒▒▒▒▒▒▒          │                 │
              └────┬──────┬──────────┬─────────────────┘
                   ▼      ▼          ▼
                cursor   end      capacity */

  int copy_begin = 0;
  int copy_end = io->buffer.end;
  int copy_amount = copy_end - copy_begin;

  int new_capacity = io->buffer.end + io->buffer.size;
  if (amount > io->buffer.size)
    new_capacity = io->buffer.end + amount;

  void* old_data = io->buffer.data;
  void* new_data = malloc(new_capacity);
  if (unlikely(new_data == NULL)) {
    fail("malloc: %li, not enough memory\n", new_capacity);
    return result;
  }

  memcpy(new_data, old_data, copy_amount);
  free(old_data);
  io->buffer.data = new_data;
  io->buffer.capacity = new_capacity;

  void* storage = io->buffer.data + io->buffer.end; 
  int channel_amount = io->buffer.capacity - io->buffer.end;
  slice channel_result = io_read_channel(io, channel_amount, storage);
  if (unlikely(error.occurred))
    return result;

  result.data = io->buffer.data + io->buffer.cursor;
  result.length = amount;

  io->buffer.end += channel_result.length;
  io->buffer.cursor += amount;

  return result;
}
