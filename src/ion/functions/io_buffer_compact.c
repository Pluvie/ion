static inline void io_buffer_compact (
    struct io* io
)
{
//   
//   chip_away:
//     /**
//      * If the io buffer has mode `IO_BUFFER_RETAIN`, no deletion of the buffer is
//      * performed, and every data read in the past is retained. Otherwise performs buffer
//      * deletion to save memory. */
//     if (io->buffer.mode == IO_BUFFER_RETAIN)
//       goto copy_data;
//   
//     /**
//      * Deletion strategy: the `copy_begin` is moved ahead in order to match the buffer
//      * size. All data from the buffer begin (`io->buffer.data` pointer) to the
//      * `copy_begin` shall be chipped away.
//      *
//      *                    ┌─►             2 * buffer.size           ◄┐
//      *   ┌────────────────┐──────────────────────────────────────────┐   
//      *   │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓│               retained amount            │   
//      *   ├────────────────┼──────────────────────▲───────────────────┘   
//      *   │  chipped away  │                      │                       
//      *   ▼                ▼                      │                       
//      *  buffer.data      copy_begin             buffer.end
//      *                                          copy_end
//      *
//      * In this case, a new begin is calculated, equal to the current cursor minus the
//      * buffer size, and then an amount equal to the difference between the new begin and
//      * the old begin is chipped away from the buffer.
//      *
//      * The deletion is performed by allocating a new buffer with the reduced amount and
//      * copying over the data, and then using is as the new buffer of the io. */
//   
//     new_capacity = 2*io->buffer.size;
//     copy_begin = io->buffer.end - io->buffer.size;
//   
//     int cursor_delta = io->buffer.end - io->buffer.cursor;
//     io->buffer.end = io->buffer.size;
//     io->buffer.cursor = io->buffer.end - cursor_delta;
//   
//   copy_data:
//     void* new_data = malloc(new_capacity);
//     void* old_data = io->buffer.data;
//     int copy_amount = copy_end - copy_begin;
//   
//     memcpy(new_data, old_data, copy_amount);
//     free(io->buffer.data);
//     io->buffer.data = new_data;
//     io->buffer.capacity = new_capacity;
//   
//     int original_cursor_position = io->cursor.position;
//     result = io_read_channel(io, io->buffer.size, io->buffer.data + io->buffer.cursor);
//     result.length = amount;
//     io->buffer.end += result.length;
//     io->buffer.cursor += result.length;
//   
//     /* Recalculates the cursor position, since the call to `io_read_channel` has
//      * intrinsecally moved the cursor ahead of `io->buffer.size` amount. We do not
//      * want this position since with this call we are just preparing the buffer. */
//     io->cursor.position = original_cursor_position + result.length;
//     return result;
}
