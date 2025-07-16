spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled");
    #define preconditions(channel_available_data) \
      string data = s("1111111122222222333333334444444455555555"); \
      struct pipe channel; pipe_open(&channel); \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(channel.reader); \
      io->buffer.enabled = true; \
      io->buffer.size = 8; \
      write(channel.writer, data.content, channel_available_data);

  when("the io buffer is not initialized") {
    #define buffer_not_initialized_condition \
      io->buffer.data = NULL;

    when("the amount to read is greater than the buffer size") {
      amount = 12;

      when("the underlying channel contains less data than the amount to read") {
        int channel_available_data = 7;
        apply(preconditions(channel_available_data));
        apply(buffer_not_initialized_condition);
        /*        ┌────────────────────────────────────────┐
          channel:│1111111                                 │
                  └────────────────────────────────────────┘
          amount:  ■■■■■■■■■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_read(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("set the buffer capacity equal to the amount to read");
          verify(io->buffer.capacity == amount);
        must("read data from the io channel");
          verify(io->read.count = 1);
        must("advance the buffer cursor by a quantity equal to the available data "\
             "on the channel");
          verify(io->buffer.cursor == channel_available_data);
        must("set the buffer end equal to the available data on the channel");
          verify(io->buffer.end == channel_available_data);
        must("return a slice of data with length equal to the available data on "\
             "the channel");
          verify(result.length == channel_available_data);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      }

      or_when("the underlying channel contains equal or more data than the amount "\
              "to read") {
        int channel_available_data = 15;
        apply(preconditions(channel_available_data));
        apply(buffer_not_initialized_condition);
        /*        ┌────────────────────────────────────────┐
          channel:│11111111222222                          │
                  └────────────────────────────────────────┘
          amount:  ■■■■■■■■■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_read(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("set the buffer capacity equal to the amount to read");
          verify(io->buffer.capacity == amount);
        must("read data from the io channel");
          verify(io->read.count = 1);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == amount);
        must("set the buffer end equal to the amount to read");
          verify(io->buffer.end == amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "111111112222"));

        success();
          io_close(io);
          pipe_close(&channel);
      }
    }

    // in: "the io buffer is not initialized"
    or_when("the amount to read is lesser or equal than the buffer size") {
      amount = 4;

      when("the underlying channel contains less data than the amount to read") {
        int channel_available_data = 3;
        apply(preconditions(channel_available_data));
        apply(buffer_not_initialized_condition);
        /*        ┌────────────────────────────────────────┐
          channel:│111                                     │
                  └────────────────────────────────────────┘
          amount:  ■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_read(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("set the buffer capacity equal to the buffer size");
          verify(io->buffer.capacity == io->buffer.size);
        must("read data from the io channel");
          verify(io->read.count = 1);
        must("advance the buffer cursor by a quantity equal to the available data "\
             "on the channel");
          verify(io->buffer.cursor == channel_available_data);
        must("set the buffer end equal to the available data on the channel");
          verify(io->buffer.cursor == channel_available_data);
        must("return a slice of data with length equal to the available data on "\
             "the channel");
          verify(result.length == channel_available_data);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      }

      // in: "the io buffer is not initialized"
      // in: "the amount to read is lesser or equal than the buffer size"
      or_when("the underlying channel contains equal or more data than the amount "\
              "to read") {
        int channel_available_data = 7;
        apply(preconditions(channel_available_data));
        apply(buffer_not_initialized_condition);
        /*        ┌────────────────────────────────────────┐
          channel:│1111111                                 │
                  └────────────────────────────────────────┘
          amount:  ■■■■
                  ┌────────────────────────────────────────┐
          buffer: │       │                                │
                  ├───────┬────────────────────────────────┘
                  ▼       ▼
               cursor    size */
        slice result = io_buffer_read(io, amount);

        must("initialize the buffer data");
          verify(io->buffer.data != NULL);
        must("set the buffer capacity equal to the buffer size");
          verify(io->buffer.capacity == io->buffer.size);
        must("read data from the io channel");
          verify(io->read.count = 1);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == amount);
        must("set the buffer end equal to the amount to read");
          verify(io->buffer.cursor == amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "1111111"));

        success();
          io_close(io);
          pipe_close(&channel);
      }
    }
  }
  #undef buffer_not_initialized_condition

  or_when("the io buffer is already initialized") {
    #define buffer_already_initialized_condition \
      io->buffer.data = malloc(io->buffer.end); \
      memcpy(io->buffer.data, data.content, io->buffer.end); \
      read(channel.reader, (char[40]) { 0 }, io->buffer.end); \
      io->buffer.capacity = io->buffer.end; \
      io->cursor = io->buffer.end; \
      io->buffer.size = 8;

    when("the amount to read exceeds the buffer end") {
      when("the amount to read is lesser or equal than the buffer size") {
        when("the io buffer contains data for less than 2 times the buffer size") {
          when("the underlying channel contains less data than the amount to read") {
            int channel_available_data = 17;
            apply(preconditions(channel_available_data));
            amount = 6;
            io->buffer.end = 14;
            io->buffer.cursor = 12;
            apply(buffer_already_initialized_condition);
            int original_buffer_end = io->buffer.end;
            int original_buffer_cursor = io->buffer.cursor;
            /*        ┌────────────────────────────────────────┐
              channel:│11111111222222223                       │
                      └────────────────────────────────────────┘
                                     ┌──┐ exceeding part
              amount:              ■■■■■■
                      ┌────────────────────────────────────────┐
              buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▒▒  │                       │
                      └───────────┬─┬──┬───────────────────────┘
                                  ▼ ▼  ▼
                            cursor end 2*size */
            slice result = io_buffer_read(io, amount);

            must("extend the buffer by a quantity equal to the buffer size");
              verify(io->buffer.capacity == original_buffer_end + io->buffer.size);
            must("read the exceeding amount from the io channel");
              verify(io->read.count == 1);
            must("advance the buffer cursor by a quantity equal to the available "\
                 "data on the channel");
              verify(io->buffer.cursor = channel_available_data);
            must("return a slice of data with length equal to the available data "\
                 "on the channel");
              verify(result.length == channel_available_data - original_buffer_cursor);
              verify(streq(result, "22223"));

            success();
              io_close(io);
              pipe_close(&channel);
          }

          // in: "the exceeding part is lesser or equal than the buffer size"
          // in: "the underlying channel contains less data than the exceeding part"
          // in: "the amount to read exceeds the buffer end"
          or_when("the io buffer contains data for equal or more than 2 times the "\
                  "buffer size") {
          }
        }

        or_when("the underlying channel contains less data than the amount to read") {
          when("the io buffer contains data for less than 2 times the buffer size") {
            /*        ┌────────────────────────────────────────┐
              channel:│1111111122222222333333334444444455555555│
                      └────────────────────────────────────────┘
                                     ┌────┐ exceeding part
              amount:            ■■■■■■■■■■
                      ┌────────────────────────────────────────┐
              buffer: │▓▓▓▓▓▓▓▓▓▓▒▒▒▒  │                       │
                      └──────────┬──┬──┬───────────────────────┘
                                 ▼  ▼  ▼
                            cursor end 2*size */
          }

          // in: "the amount to read exceeds the buffer end"
          or_when("the io buffer contains data for equal or more than 2 times the "\
                  "buffer size") {
          }
        }
      }

      // in: "the io buffer is already initialized"
      // in: "the amount to read exceeds the buffer end"
      or_when("the exceeding part is greater than the buffer size") {
        when("the io buffer contains data for less than 2 times the buffer size") {
        }

        // in: "the amount to read exceeds the buffer end"
        or_when("the io buffer contains data for equal or more than 2 times the "\
                "buffer size") {
        }
      }
    }

    // in: "the io buffer is already initialized"
    or_when("the amount to read does not exceed the buffer end") {
      when("the io buffer contains data for less than 2 times the buffer size") {
      }

      // in: "the io buffer is already initialized"
      // in: "the amount to read does not exceed the buffer end"
      or_when("the io buffer contains data for equal or more than 2 times the "\
              "buffer size") {
      }
    }
  }
  #undef buffer_already_initialized_condition

  #undef preconditions
}
