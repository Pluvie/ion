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
      } end();

      when("the underlying channel contains equal or more data than the amount to read") {
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
      } end();
    } end();

    // in: "the io buffer is not initialized"
    when("the amount to read is lesser or equal than the buffer size") {
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
      } end();

      // in: "the io buffer is not initialized"
      // in: "the amount to read is lesser or equal than the buffer size"
      when("the underlying channel contains equal or more data than the amount "\
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
      } end();
    } end();
  } end();
  #undef buffer_not_initialized_condition

  when("the io buffer is already initialized") {
    #define buffer_already_initialized_condition \
      io->buffer.data = malloc(io->buffer.end); \
      memcpy(io->buffer.data, data.content, io->buffer.end); \
      read(channel.reader, (char[40]) { 0 }, io->buffer.end); \
      io->buffer.capacity = io->buffer.end; \
      io->cursor = io->buffer.end; \
      io->buffer.size = 8;

    when("the amount to read exceeds the buffer end") {
      when("the amount to read is lesser or equal than the buffer size") {
        amount = 6;

        when("the io buffer contains data for less than 2 times the buffer size") {
          when("the underlying channel contains less data than the amount to read") {
            int channel_available_data = 17;
            apply(preconditions(channel_available_data));
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
          } end();

          // in: "the amount to read exceeds the buffer end"
          // in: "the amount to read is lesser or equal than the buffer size"
          // in: "the io buffer contains data for less than 2 times the buffer size"
          when("the underlying channel contains equal or more data than the amount "\
                  "to read") {
            int channel_available_data = 20;
            apply(preconditions(channel_available_data));
            io->buffer.end = 14;
            io->buffer.cursor = 12;
            apply(buffer_already_initialized_condition);
            int original_buffer_end = io->buffer.end;
            /*        ┌────────────────────────────────────────┐
              channel:│11111111222222223333                    │
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
            must("advance the buffer cursor by a quantity equal to the amount to read");
              verify(io->buffer.cursor = amount);
            must("return a slice of data with length equal to the amount to read");
              verify(result.length == amount);
              verify(streq(result, "222233"));

            success();
              io_close(io);
              pipe_close(&channel);
          } end();
        } end();

        // in: "the amount to read exceeds the buffer end"
        // in: "the amount to read is lesser or equal than the buffer size"
        when("the io buffer contains data for equal or more than 2 times the "\
                "buffer size") {
          when("the underlying channel contains less data than the amount to read") {
            when("the buffer is not retained") {
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

              must("extend the buffer by a quantity equal to the buffer size and chip "\
                   "away the buffer data to retain only a backward quantity equal to "\
                   "the buffer size");
                verify(io->buffer.capacity ==
                  (original_buffer_end + io->buffer.size) -
                  (original_buffer_end - io->buffer.size));
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the available "\
                   "data on the channel");
                verify(io->buffer.cursor = channel_available_data);
              must("return a slice of data with length equal to the available data "\
                   "on the channel");
                verify(result.length == channel_available_data - original_buffer_cursor);
                verify(streq(result, "33334"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();

            // in: "the amount to read exceeds the buffer end"
            // in: "the amount to read is lesser or equal than the buffer size"
            // in: "the io buffer contains data for equal or more than 2 times the buffer size
            // in: "the underlying channel contains less data than the amount to read"
            when("the buffer is retained") {
              int channel_available_data = 25;
              apply(preconditions(channel_available_data));
              io->buffer.end = 24;
              io->buffer.cursor = 20;
              io->buffer.retained = true;
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
                verify(io->buffer.capacity == original_buffer_end + io->buffer.size);
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the available "\
                   "data on the channel");
                verify(io->buffer.cursor = channel_available_data);
              must("return a slice of data with length equal to the available data "\
                   "on the channel");
                verify(result.length == channel_available_data - original_buffer_cursor);
                verify(streq(result, "33334"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();
          } end();

          // in: "the amount to read exceeds the buffer end"
          // in: "the amount to read is lesser or equal than the buffer size"
          // in: "the io buffer contains data for equal or more than 2 times the buffer size"
          when("the underlying channel contains equal or more data than the amount "\
                  "to read") {
            when("the buffer is not retained") {
              int channel_available_data = 28;
              apply(preconditions(channel_available_data));
              io->buffer.end = 24;
              io->buffer.cursor = 20;
              io->buffer.retained = false;
              apply(buffer_already_initialized_condition);
              int original_buffer_end = io->buffer.end;
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

              must("extend the buffer by a quantity equal to the buffer size and chip "\
                   "away the buffer data to retain only a backward quantity equal to "\
                   "the buffer size");
                verify(io->buffer.capacity ==
                  (original_buffer_end + io->buffer.size) -
                  (original_buffer_end - io->buffer.size));
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the amount to read");
                verify(io->buffer.cursor = amount);
              must("return a slice of data with length equal to the amount to read");
                verify(result.length == amount);
                verify(streq(result, "333344"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();

            // in: "the amount to read exceeds the buffer end"
            // in: "the amount to read is lesser or equal than the buffer size"
            // in: "the io buffer contains data for equal or more than 2 times the buffer size
            // in: "the underlying channel contains less data than the amount to read"
            // in: "the underlying channel contains equal or more data than the amount to read"
            when("the buffer is retained") {
              int channel_available_data = 28;
              apply(preconditions(channel_available_data));
              io->buffer.end = 24;
              io->buffer.cursor = 20;
              io->buffer.retained = true;
              apply(buffer_already_initialized_condition);
              int original_buffer_end = io->buffer.end;
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
                verify(io->buffer.capacity == original_buffer_end + io->buffer.size);
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the amount to read");
                verify(io->buffer.cursor = amount);
              must("return a slice of data with length equal to the amount to read");
                verify(result.length == amount);
                verify(streq(result, "333344"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();
          } end();
        } end();
      } end();

      when("the amount to read is greater than the buffer size") {
        amount = 12;

        when("the io buffer contains data for less than 2 times the buffer size") {
          when("the underlying channel contains less data than the amount to read") {
            int channel_available_data = 19;
            apply(preconditions(channel_available_data));
            io->buffer.end = 14;
            io->buffer.cursor = 12;
            apply(buffer_already_initialized_condition);
            int original_buffer_end = io->buffer.end;
            int original_buffer_cursor = io->buffer.cursor;
            /*        ┌────────────────────────────────────────┐
              channel:│1111111122222222333                     │
                      └────────────────────────────────────────┘
                                     ┌────────┐ exceeding part
              amount:              ■■■■■■■■■■■■
                      ┌────────────────────────────────────────┐
              buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▒▒  │                       │
                      └───────────┬─┬──┬───────────────────────┘
                                  ▼ ▼  ▼
                            cursor end 2*size */
            slice result = io_buffer_read(io, amount);

            must("extend the buffer by a quantity equal to the amount to read");
              verify(io->buffer.capacity == original_buffer_end + amount);
            must("read the exceeding amount from the io channel");
              verify(io->read.count == 1);
            must("advance the buffer cursor by a quantity equal to the available "\
                 "data on the channel");
              verify(io->buffer.cursor = channel_available_data);
            must("return a slice of data with length equal to the available data "\
                 "on the channel");
              verify(result.length == channel_available_data - original_buffer_cursor);
              verify(streq(result, "2222333"));

            success();
              io_close(io);
              pipe_close(&channel);
          } end();

          // in: "the amount to read exceeds the buffer end"
          // in: "the amount to read is greater than the buffer size"
          // in: "the io buffer contains data for less than 2 times the buffer size"
          when("the underlying channel contains equal or more data than the amount to read") {
            int channel_available_data = 26;
            apply(preconditions(channel_available_data));
            io->buffer.end = 14;
            io->buffer.cursor = 12;
            apply(buffer_already_initialized_condition);
            int original_buffer_end = io->buffer.end;
            /*        ┌────────────────────────────────────────┐
              channel:│11111111222222223333333344              │
                      └────────────────────────────────────────┘
                                     ┌────────┐ exceeding part
              amount:              ■■■■■■■■■■■■
                      ┌────────────────────────────────────────┐
              buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▒▒  │                       │
                      └───────────┬─┬──┬───────────────────────┘
                                  ▼ ▼  ▼
                            cursor end 2*size */
            slice result = io_buffer_read(io, amount);

            must("extend the buffer by a quantity equal to the amount to read");
              verify(io->buffer.capacity == original_buffer_end + amount);
            must("read the exceeding amount from the io channel");
              verify(io->read.count == 1);
            must("advance the buffer cursor by a quantity equal to the amount to read");
              verify(io->buffer.cursor = amount);
            must("return a slice of data with length equal to the amount to read");
              verify(result.length == amount);
              verify(streq(result, "222233333333"));

            success();
              io_close(io);
              pipe_close(&channel);
          } end();
        } end();

        // in: "the amount to read exceeds the buffer end"
        // in: "the amount to read is greater than the buffer size"
        when("the io buffer contains data for equal or more than 2 times the buffer size") {
          when("the underlying channel contains less data than the amount to read") {
            when("the buffer is not retained") {
              int channel_available_data = 27;
              apply(preconditions(channel_available_data));
              io->buffer.end = 24;
              io->buffer.cursor = 20;
              io->buffer.retained = false;
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

              must("extend the buffer by a quantity equal to the amount to read and "\
                   "chip away the buffer data to retain only a backward quantity equal "\
                   "to the buffer size");
                verify(io->buffer.capacity ==
                  (original_buffer_end + amount) -
                  (original_buffer_end - io->buffer.size));
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the available "\
                   "data on the channel");
                verify(io->buffer.cursor = channel_available_data);
              must("return a slice of data with length equal to the available data "\
                   "on the channel");
                verify(result.length == channel_available_data - original_buffer_cursor);
                verify(streq(result, "3333444"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();

            // in: "the amount to read exceeds the buffer end"
            // in: "the amount to read is greater than the buffer size"
            // in: "the io buffer contains data for equal or more than 2 times the buffer size"
            // in: "the underlying channel contains less data than the amount to read"
            when("the buffer is retained") {
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

              must("extend the buffer by a quantity equal to the amount to read");
                verify(io->buffer.capacity == original_buffer_end + amount);
              must("read the exceeding amount from the io channel");
                verify(io->read.count == 1);
              must("advance the buffer cursor by a quantity equal to the available "\
                   "data on the channel");
                verify(io->buffer.cursor = channel_available_data);
              must("return a slice of data with length equal to the available data "\
                   "on the channel");
                verify(result.length == channel_available_data - original_buffer_cursor);
                verify(streq(result, "3333444"));

              success();
                io_close(io);
                pipe_close(&channel);
            } end();
          } end();

          // in: "the amount to read exceeds the buffer end"
          // in: "the amount to read is greater than the buffer size"
          // in: "the io buffer contains data for equal or more than 2 times the buffer size"
          when("the underlying channel contains equal or more data than the amount to read") {
            when("the buffer is not retained") {
              int channel_available_data = 36;
              apply(preconditions(channel_available_data));
              io->buffer.end = 24;
              io->buffer.cursor = 20;
              io->buffer.retained = false;
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

              must("extend the buffer by a quantity equal to the amount to read and "\
                   "chip away the buffer data to retain only a backward quantity equal "\
                   "to the buffer size");
                verify(io->buffer.capacity ==
                  (original_buffer_end + amount) -
                  (original_buffer_end - io->buffer.size));
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

            // in: "the amount to read exceeds the buffer end"
            // in: "the amount to read is greater than the buffer size"
            // in: "the io buffer contains data for equal or more than 2 times the buffer size"
            // in: "the underlying channel contains equal or more data than the amount to read"
            when("the buffer is retained") {
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

              must("extend the buffer by a quantity equal to the amount to read");
                verify(io->buffer.capacity == original_buffer_end + amount);
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
    } end();

    // in: "the io buffer is already initialized"
    when("the amount to read does not exceed the buffer end") {
      amount = 4;

      when("the io buffer contains data for less than 2 times the buffer size") {
        int channel_available_data = 17;
        apply(preconditions(channel_available_data));
        io->buffer.end = 14;
        io->buffer.cursor = 8;
        apply(buffer_already_initialized_condition);
        void* original_buffer_data = io->buffer.data;
        int original_buffer_capacity = io->buffer.capacity;
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
          verify(io->buffer.capacity == original_buffer_capacity);
        must("not perform any read from the io channel");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor = amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "2222"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();

      // in: "the io buffer is already initialized"
      // in: "the amount to read does not exceed the buffer end"
      when("the io buffer contains data for equal or more than 2 times the buffer size") {
        int channel_available_data = 25;
        apply(preconditions(channel_available_data));
        io->buffer.end = 24;
        io->buffer.cursor = 18;
        apply(buffer_already_initialized_condition);
        void* original_buffer_data = io->buffer.data;
        int original_buffer_capacity = io->buffer.capacity;
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

        must("not extend the buffer");
          verify(io->buffer.data == original_buffer_data);
          verify(io->buffer.capacity == original_buffer_capacity);
        must("not perform any read from the io channel");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor = amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "3333"));

        success();
          io_close(io);
          pipe_close(&channel);
      } end();
    } end();
  } end();
  #undef buffer_already_initialized_condition

  #undef preconditions
}
