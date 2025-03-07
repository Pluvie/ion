static inline void io_buffer_chip_away (
    struct io* io
)
{
  /**
   * If the io has flag `IO_FLAGS_BUFFER_RETAIN`, no deletion of the buffer is
   * performed, and everything is retained the buffer. Otherwise, checks if there
   * is data that has grown past the buffer size, and in that case performs buffer
   * deletion to save memory. */
  if (io->flags & IO_FLAGS_BUFFER_RETAIN)
    return;

  /**
   * If the cursor has not exceeded the buffer size, no deletion is performed. */
  if (io->cursor - io->buffer.begin < 2 * io->buffer.size)
    return;

  /**
   * The cursor has exceeded the buffer size, which means that behind the cursor there
   * is data greater or equal to `2*io->buffer.size` amount.
   *
   *                                                  io->buffer.allocator.position
   *                                                               ▲
   *                                                               │
   *                    ┌─►          2 * io->buffer.size          ◄┐
   *   ┌────────────────┐──────────────────────────────────────────┐   
   *   │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│               retained amount            │   
   *   ├────────────────┼──────────────────────▲───────────────────┘   
   *   │  chipped away  │                      │                       
   *   ▼                ▼                      │                       
   *  old              new                   cursor
   *  begin            begin
   *
   * In this case, a new begin is calculated, equal to the current cursor minus the
   * buffer size, and then an amount equal to the difference between the new begin and
   * the old begin is chipped away from the buffer.
   *
   * The deletion is performed by allocating a new buffer with the reduced amount and
   * copying over the data, and then using is as the new buffer of the io. */

  u64 old_begin = io->buffer.begin;
  u64 new_begin = io->cursor - io->buffer.size;
  u64 chipped_away = new_begin - old_begin;
  u64 retained_amount = io->buffer.allocator.position - chipped_away;
  io->buffer.begin = new_begin;

  struct buffer new_allocator = buffer_init(io->buffer.allocator.capacity);
  buffer_alloc(&new_allocator, retained_amount);
  memcpy(new_allocator.data, io->buffer.allocator.data + chipped_away, retained_amount);

  buffer_release(&(io->buffer.allocator));
  memcpy(&(io->buffer.allocator), &new_allocator, sizeof(struct buffer));
}
