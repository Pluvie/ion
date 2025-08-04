spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled");
  precondition("the underlying channel has some data available to read");
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

    must("behave exactly like the `io_buffer_init` function");
    /* Refer to the `io_buffer_init` spec for more details on its behaviour. */
    int channel_available_data = 18;
    amount = 12;

    slice result_of_buffer_init; struct io io_with_buffer_init; {
      apply(preconditions(channel_available_data));
      apply(buffer_not_initialized_condition);
      result_of_buffer_init = io_buffer_init(io, amount);
      io_with_buffer_init = *io;
      pipe_close(&channel);
    }

    slice result_of_buffer_read; struct io io_with_buffer_read; {
      apply(preconditions(channel_available_data));
      apply(buffer_not_initialized_condition);
      result_of_buffer_read = io_buffer_read(io, amount);
      io_with_buffer_read = *io;
      pipe_close(&channel);
    }

    verify(eq(result_of_buffer_init, result_of_buffer_read));

    /* Equality of io structs is done without taking in consideration its buffer data
     * pointer value because, of course, the buffer shall malloc on two different
     * addresses. */
    void* io_with_buffer_init_data = io_with_buffer_init.buffer.data;
    void* io_with_buffer_read_data = io_with_buffer_read.buffer.data;
    io_with_buffer_init.buffer.data = NULL;
    io_with_buffer_read.buffer.data = NULL;
    verify(memeq(&io_with_buffer_init, &io_with_buffer_read, sizeof(struct io)));

    success();
      io_with_buffer_init.buffer.data = io_with_buffer_init_data;
      io_with_buffer_read.buffer.data = io_with_buffer_read_data;
      io_close(&io_with_buffer_init);
      io_close(&io_with_buffer_read);

  } end();
  #undef buffer_not_initialized_condition

  when("the io buffer is already initialized") {
    #define buffer_already_initialized_condition \
      io->buffer.data = malloc(io->buffer.end); \
      memcpy(io->buffer.data, data.content, io->buffer.end); \
      read(channel.reader, (char[40]) { 0 }, io->buffer.end);

    when("the amount to read does not exceed the buffer end") {
      amount = 4;

      when("the io buffer contains data for no more than 2 times the buffer size") {
        int channel_available_data = 17;
        apply(preconditions(channel_available_data));
        io->buffer.end = 14;
        io->buffer.cursor = 8;
        apply(buffer_already_initialized_condition);
        void* original_buffer_data = io->buffer.data;
        int original_buffer_end = io->buffer.end;
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
        slice result = io_buffer_read(io, amount);

        must("not extend the buffer");
          verify(io->buffer.data == original_buffer_data);
          verify(io->buffer.end == original_buffer_end);
        must("not perform any read from the io channel");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == original_buffer_cursor + amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "2222"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();

      // when("the io buffer is already initialized")
      // when("the amount to read does not exceed the buffer end")
      when("the io buffer contains data for more than 2 times the buffer size") {
        when("the io buffer is retained") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.retained = true;
          io->buffer.end = 24;
          io->buffer.cursor = 18;
          apply(buffer_already_initialized_condition);
          void* original_buffer_data = io->buffer.data;
          int original_buffer_end = io->buffer.end;
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
          slice result = io_buffer_read(io, amount);

          must("not chip away the buffer");
            verify(io->buffer.data == original_buffer_data);
            verify(io->buffer.end == original_buffer_end);
          must("not perform any read from the io channel");
            verify(io->read.count == 0);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor == original_buffer_cursor + amount);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "3333"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the io buffer is already initialized")
        // when("the amount to read does not exceed the buffer end")
        // when("the io buffer contains data for equal or more than 2 times the buffer size")
        when("the io buffer is not retained") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.retained = false;
          io->buffer.end = 24;
          io->buffer.cursor = 18;
          int original_buffer_cursor = io->buffer.cursor;
          int chipped_away_quantity = io->buffer.end - 2*io->buffer.size;
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
          slice result = io_buffer_read(io, amount);

          must("chip away the buffer to retain only a window equal to 2 times the buffer size");
            verify(io->buffer.end == 2*io->buffer.size);
          must("not perform any read from the io channel");
            verify(io->read.count == 0);
          must("adjust the buffer cursor by a quantity equal to the amount to read minus "\
               "the chipped away quantity");
            verify(io->buffer.cursor == original_buffer_cursor + amount - chipped_away_quantity);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "3333"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();
      } end();
    } end();

    // when("the io buffer is already initialized")
    when("the amount to read exceeds the buffer end") {
      when("the amount to read is lesser or equal than the buffer size") {
        amount = 6;

        when("the underlying channel contains less data than the amount to read") {
          int channel_available_data = 25;
          apply(preconditions(channel_available_data));
          io->buffer.end = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = false;
          apply(buffer_already_initialized_condition);
          int original_buffer_end = io->buffer.end;
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
          slice result = io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size");
            verify(io->buffer.end == original_buffer_end + io->buffer.size);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.cursor == channel_available_data);
          must("return a slice of data with length equal to the available data "\
               "on the channel");
            verify(result.length == channel_available_data - original_buffer_cursor);
            verify(streq(result, "33334"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the amount to read exceeds the buffer end")
        // when("the amount to read is lesser or equal than the buffer size")
        // when("the io buffer contains data for equal or more than 2 times the buffer size")
        when("the underlying channel contains equal or more data than the amount to read") {
          int channel_available_data = 28;
          apply(preconditions(channel_available_data));
          io->buffer.end = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = false;
          apply(buffer_already_initialized_condition);
          int original_buffer_end = io->buffer.end;
          int original_buffer_cursor = io->buffer.cursor;
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444            │
                    └────────────────────────────────────────┘
                                             ┌┐ exceeding part
            amount:                      ■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          slice result = io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size");
            verify(io->buffer.end == original_buffer_end + io->buffer.size);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor == original_buffer_cursor + amount);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "333344"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();
      } end();

      // when("the io buffer is already initialized")
      // when("the amount to read exceeds the buffer end")
      when("the amount to read is greater than the buffer size") {
        amount = 12;

        when("the underlying channel contains less data than the amount to read") {
          int channel_available_data = 27;
          apply(preconditions(channel_available_data));
          io->buffer.end = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = true;
          apply(buffer_already_initialized_condition);
          int original_buffer_end = io->buffer.end;
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
          slice result = io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size plus amount to read");
            verify(io->buffer.end == original_buffer_end + io->buffer.size + amount);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the available "\
               "data on the channel");
            verify(io->buffer.cursor == original_buffer_cursor +
              (channel_available_data - original_buffer_end));
          must("return a slice of data with length equal to the available data "\
               "on the channel");
            verify(result.length == channel_available_data - original_buffer_cursor);
            verify(streq(result, "3333444"));

          success();
            io_close(io);
            pipe_close(&channel);
        } end();

        // when("the amount to read exceeds the buffer end")
        // when("the amount to read is greater than the buffer size")
        when("the underlying channel contains equal or more data than the amount to read") {
          int channel_available_data = 36;
          apply(preconditions(channel_available_data));
          io->buffer.end = 24;
          io->buffer.cursor = 20;
          io->buffer.retained = true;
          apply(buffer_already_initialized_condition);
          int original_buffer_end = io->buffer.end;
          /*        ┌────────────────────────────────────────┐
            channel:│111111112222222233333333444444445555    │
                    └────────────────────────────────────────┘
                                             ┌──────┐ exceeding part
            amount:                      ■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          slice result = io_buffer_read(io, amount);

          must("extend the buffer by a quantity equal to the buffer size plus amount to read");
            verify(io->buffer.end == original_buffer_end + io->buffer.size + amount);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor = amount);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "333344444444"));

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
