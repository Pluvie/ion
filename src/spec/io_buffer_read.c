spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled");
  precondition("the underlying channel has some data available to read");
    #define preconditions(channel_available_data) \
      string data = s("1111111122222222333333334444444455555555"); \
      struct pipe channel = pipe_open(); \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(&channel); \
      io->buffer.enabled = true; \
      io->buffer.size = 8; \
      write(channel.writer, data.pointer, channel_available_data);

  when("the io buffer is not initialized") {
    #define buffer_not_initialized_condition \
      io->buffer.data = (string) { NULL, 0 };

    must("behave exactly like the `io_buffer_init` function");
    /* Refer to the `io_buffer_init` spec for more details on its behaviour. */
    int channel_available_data = 18;
    amount = 12;

    struct io io_with_buffer_init; {
      apply(preconditions(channel_available_data));
      apply(buffer_not_initialized_condition);
      io_buffer_init(io, amount);
      io_with_buffer_init = *io;
      pipe_close(&channel);
    }

    struct io io_with_buffer_read; {
      apply(preconditions(channel_available_data));
      apply(buffer_not_initialized_condition);
      io_buffer_read(io, amount);
      io_with_buffer_read = *io;
      pipe_close(&channel);
    }

    verify(io_with_buffer_init.cursor == io_with_buffer_read.cursor);
    verify(io_with_buffer_init.buffer.cursor == io_with_buffer_read.buffer.cursor);

    verify(eq(io_with_buffer_init.result, io_with_buffer_read.result));
    verify(eq(io_with_buffer_init.buffer.data, io_with_buffer_read.buffer.data));

    success();
      io_close(&io_with_buffer_init);
      io_close(&io_with_buffer_read);

  } end();
  #undef buffer_not_initialized_condition

  when("the io buffer is already initialized") {
    #define buffer_already_initialized_condition \
      io->buffer.data.pointer = alloc(io->buffer.data.length); \
      byte_copy(io->buffer.data.pointer, data.pointer, io->buffer.data.length); \
      read(channel.reader, (char[40]) { 0 }, io->buffer.data.length);

    when("the amount to read does not exceed the buffer length") {
      amount = 4;

      when("the io buffer contains data for no more than 2 times the buffer size") {
        int channel_available_data = 17;
        apply(preconditions(channel_available_data));
        io->buffer.data.length = 14;
        io->buffer.cursor = 8;
        apply(buffer_already_initialized_condition);
        string original_buffer_data = { io->buffer.data.pointer, io->buffer.data.length };
        int original_buffer_cursor = io->buffer.cursor;
        /*        ┌────────────────────────────────────────┐
          channel:│11111111222222223                       │
                  └────────────────────────────────────────┘
          amount:          ■■■■
                  ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒  │                       │
                  └───────┬─────┬──┬───────────────────────┘
                          ▼     ▼  ▼
                        cursor end 2*size */
        io_buffer_read(io, amount);

        must("not extend the buffer");
          verify(io->buffer.data.pointer == original_buffer_data.pointer);
          verify(io->buffer.data.length == original_buffer_data.length);
        must("not perform any read from the io channel");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == original_buffer_cursor + amount);
        must("return a string of data with length equal to the amount to read");
          verify(io->result.length == amount);
          verify(eq(io->result, "2222"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();

      // when("the io buffer is already initialized")
      // when("the amount to read does not exceed the buffer length")
      when("the io buffer contains data for more than 2 times the buffer size") {
        when("the io buffer is retained") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.retained = true;
          io->buffer.data.length = 24;
          io->buffer.cursor = 18;
          apply(buffer_already_initialized_condition);
          string original_buffer_data = { io->buffer.data.pointer, io->buffer.data.length };
          int original_buffer_cursor = io->buffer.cursor;
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334               │
                    └────────────────────────────────────────┘
            amount:                    ■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒                │
                    └───────────────┬─┬─────┬────────────────┘
                                    ▼ ▼     ▼
                              2*size cursor end */
          io_buffer_read(io, amount);

          must("not chip away the buffer");
            verify(io->buffer.data.pointer == original_buffer_data.pointer);
            verify(io->buffer.data.length == original_buffer_data.length);
          must("not perform any read from the io channel");
            verify(io->read.count == 0);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor == original_buffer_cursor + amount);
          must("return a string of data with length equal to the amount to read");
            verify(io->result.length == amount);
            verify(eq(io->result, "3333"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the io buffer is already initialized")
        // when("the amount to read does not exceed the buffer length")
        // when("the io buffer contains data for equal or more than 2 times the buffer size")
        when("the io buffer is not retained") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.retained = false;
          io->buffer.data.length = 24;
          io->buffer.cursor = 18;
          int original_buffer_cursor = io->buffer.cursor;
          int chipped_away_quantity = io->buffer.data.length - 2*io->buffer.size;
          apply(buffer_already_initialized_condition);
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334               │
                    └────────────────────────────────────────┘
            amount:                    ■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒                │
                    └───────────────┬─┬─────┬────────────────┘
                                    ▼ ▼     ▼
                              2*size cursor end */
          io_buffer_read(io, amount);

          must("chip away the buffer to retain only a window equal to 2 times the buffer size");
            verify(io->buffer.data.length == 2*io->buffer.size);
          must("not perform any read from the io channel");
            verify(io->read.count == 0);
          must("adjust the buffer cursor by a quantity equal to the amount to read minus "\
               "the chipped away quantity");
            verify(io->buffer.cursor == original_buffer_cursor + amount - chipped_away_quantity);
          must("return a string of data with length equal to the amount to read");
            verify(io->result.length == amount);
            verify(eq(io->result, "3333"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();
      } end();
    } end();

    // when("the io buffer is already initialized")
    when("the amount to read exceeds the buffer length") {
      when("the amount to read is not greater than the buffer size") {
        amount = 6;

        when("the underlying channel contains less data than the buffer size") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.data.length = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = false;
          apply(buffer_already_initialized_condition);
          int original_buffer_cursor = io->buffer.cursor;
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334               │
                    └────────────────────────────────────────┘
                                             ┌┐ exceeding part
            amount:                      ■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          io_buffer_read(io, amount);

          must("extend the buffer to a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.data.length == channel_available_data);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.cursor == channel_available_data);
          must("return a string of data with length equal to the available data "\
               "on the channel");
            verify(io->result.length == channel_available_data - original_buffer_cursor);
            verify(eq(io->result, "33334"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the amount to read exceeds the buffer length")
        // when("the amount to read is lesser or equal than the buffer size")
        // when("the io buffer contains data for equal or more than 2 times the buffer size")
        when("the underlying channel contains equal or more data than the buffer size") {
          int channel_available_data = 34;
          apply(preconditions(channel_available_data));
          io->buffer.data.length = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = false;
          apply(buffer_already_initialized_condition);
          int original_buffer_length = io->buffer.data.length;
          int original_buffer_cursor = io->buffer.cursor;
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455      │
                    └────────────────────────────────────────┘
                                             ┌┐ exceeding part
            amount:                      ■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size");
            verify(io->buffer.data.length == original_buffer_length + io->buffer.size);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor == original_buffer_cursor + amount);
          must("return a string of data with length equal to the amount to read");
            verify(io->result.length == amount);
            verify(eq(io->result, "333344"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();
      } end();

      // when("the io buffer is already initialized")
      // when("the amount to read exceeds the buffer length")
      when("the amount to read is greater than the buffer size") {
        amount = 10;

        when("the underlying channel contains less data than the amount to read") {
          int channel_available_data = 27;
          apply(preconditions(channel_available_data));
          io->buffer.data.length = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = true;
          apply(buffer_already_initialized_condition);
          int original_buffer_cursor = io->buffer.cursor;
          /*        ┌────────────────────────────────────────┐
            channel:│111111112222222233333333444             │
                    └────────────────────────────────────────┘
                                             ┌──────┐ exceeding part
            amount:                      ■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          io_buffer_read(io, amount);

          must("extend the buffer to a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.data.length == channel_available_data);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.cursor == channel_available_data);
          must("return a string of data with length equal to the available data "\
               "on the channel");
            verify(io->result.length == channel_available_data - original_buffer_cursor);
            verify(eq(io->result, "3333444"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the amount to read exceeds the buffer length")
        // when("the amount to read is greater than the buffer size")
        when("the underlying channel contains equal or more data than the buffer size") {
          int channel_available_data = 40;
          apply(preconditions(channel_available_data));
          io->buffer.data.length = 22;
          io->buffer.cursor = 20;
          io->buffer.retained = true;
          apply(buffer_already_initialized_condition);
          int original_buffer_length = io->buffer.data.length;
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                            ┌──────┐ exceeding part
            amount:                     ■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒                   │
                    └───────────────┬──┬─┬───────────────────┘
                                    ▼  ▼ ▼
                              2*size cursor end */
          io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size plus amount to read");
            verify(io->buffer.data.length == original_buffer_length + io->buffer.size + amount);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor = amount);
          must("return a string of data with length equal to the amount to read");
            verify(io->result.length == amount);
            verify(eq(io->result, "333344444444"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();
      } end();
    } end();
  } end();
  #undef buffer_already_initialized_condition

  #undef preconditions
}
