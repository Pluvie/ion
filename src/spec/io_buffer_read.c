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
    #define buffer_already_initialized_condition(end_value, cursor_value) \
      io->buffer.end = end_value; \
      io->buffer.data = malloc(io->buffer.end); \
      memcpy(io->buffer.data, channel_data, io->buffer.end); \
      io->cursor = io->buffer.end; \
      io->buffer.cursor = cursor_value; \
      io->buffer.size = 8;

    when("the amount to read exceeds the buffer remaining data") {
      when("the io buffer contains data for less than 2 times the buffer size") {
      }

      // in: "the amount to read exceeds the buffer remaining data"
      or_when("the io buffer contains data for equal or more than 2 times the "\
              "buffer size") {
      }
    }

    // in: "the io buffer is already initialized"
    or_when("the amount to read does not exceed the buffer remaining data") {
      when("the io buffer contains data for less than 2 times the buffer size") {
      }

      // in: "the io buffer is already initialized"
      // in: "the amount to read does not exceed the buffer remaining data"
      or_when("the io buffer contains data for equal or more than 2 times the "\
              "buffer size") {
      }
    }
  }
  #undef buffer_already_initialized_condition

  #undef preconditions
}





void old(void) {


  or_when("the io buffer is already initialized") {
    /* Simulates previous calls to `io_buffer_read` in order to create the conditions
     * where the end and cursor values of the buffer represent significant spec cases. */
    #define simulate_previous_reads(end_value, cursor_value) \
      io->buffer.end = end_value; \
      io->buffer.data = malloc(io->buffer.end); \
      memcpy(io->buffer.data, io->memory, io->buffer.end); \
      io->cursor = io->buffer.end; \
      io->buffer.cursor = cursor_value;

    when("the io buffer contains data for less than 2 times the buffer size") {
      when("the amount to read exceeds the buffer remaining data") {
        when("the exceeding part is not greater than the buffer size") {
          apply(preconditions);
          io->buffer.size = 8;
          amount = 10;
          simulate_previous_reads(14, 10);
          int original_buffer_end = io->buffer.end;
          int original_buffer_cursor = io->buffer.cursor;
          int exceeding_quantity = (io->buffer.cursor + amount) - io->buffer.end;
          slice result = io_buffer_read(io, amount);
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
          must("extend the buffer by a quantity equal to the buffer size");
            verify(io->buffer.end == original_buffer_end + exceeding_quantity);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor = original_buffer_cursor + amount);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "2222223333"));
          /*        ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒                  │
                    └───────────────────┬─┬──────────────────┘
                                        ▼ ▼  
                                   cursor end */
          success();
            io_close(io);
        }

        or_when("the exceeding part is greater than the buffer size") {
          apply(preconditions);
          io->buffer.size = 8;
          amount = 16;
          simulate_previous_reads(14, 10);
          int original_buffer_end = io->buffer.end;
          int original_buffer_cursor = io->buffer.cursor;
          int exceeding_quantity = (io->buffer.cursor + amount) - io->buffer.end;
          slice result = io_buffer_read(io, amount);
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                   ┌──────────┐ exceeding part
            amount:            ■■■■■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▒▒▒▒  │                       │
                    └──────────┬──┬──┬───────────────────────┘
                               ▼  ▼  ▼
                          cursor end 2*size */
          must("extend the buffer by a quantity equal to the exceeding quantity");
            verify(io->buffer.end == original_buffer_end + exceeding_quantity);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
            verify(io->buffer.cursor = original_buffer_cursor + amount);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "2222223333333344"));
          /*        ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓              │
                    └────────────────┬────────┬──────────────┘
                                     ▼        ▼
                                2*size  cursor == end */
          success();
            io_close(io);
        }

      }

      or_when("the amount to read does not exceed the buffer remaining data") {
        apply(preconditions);
        io->buffer.size = 8;
        amount = 2;
        simulate_previous_reads(14, 10);
        int original_buffer_cursor = io->buffer.cursor;
        slice result = io_buffer_read(io, amount);
        /*        ┌────────────────────────────────────────┐
          channel:│1111111122222222333333334444444455555555│
                  └────────────────────────────────────────┘
          amount:            ■■
                  ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▒▒▒▒  │                       │
                  └──────────┬──┬──┬───────────────────────┘
                             ▼  ▼  ▼
                        cursor end 2*size */
        must("read the data directly from the buffer and not perform any channel read");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == original_buffer_cursor + amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "22"));
        /*        ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▒▒  │                       │
                  └───────────┬─┬──┬───────────────────────┘
                              ▼ ▼  ▼
                        cursor end 2*size */
        success();
          io_close(io);
      }
    }

    or_when("the io buffer contains data for equal or more than 2 times the buffer size") {
      when("the amount to read exceeds the buffer remaining data") {
        when("the exceeding part is not greater than the buffer size") {
          apply(preconditions);
          io->buffer.size = 8;
          amount = 10;
          simulate_previous_reads(24, 20);
          int original_buffer_end = io->buffer.end;
          slice result = io_buffer_read(io, amount);
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                             ┌────┐ exceeding part <= size
            amount:                      ■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          must("chip away previous buffer data to retain only a quantity equal to "\
               "the buffer size");
            int chipped_away_quantity = original_buffer_end - io->buffer.size;
            verify(chipped_away_quantity == 16);
          must("extend the buffer by a quantity equal to the buffer size");
            verify(io->buffer.end == 14);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
          must("adjust the buffer cursor by subtracting the chipped away quantity");
            verify(io->buffer.cursor == 14);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "3333444444"));
          /*           chipped away
                    ┌───────────────┐
                    ┌────────────────────────────────────────┐
            buffer: │                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒        │
                    └─────────────────────────────┬─┬────────┘
                                                  ▼ ▼
                                             cursor end */
          success();
            io_close(io);
        }

        or_when("the exceeding part is greater than the buffer size") {
          apply(preconditions);
          io->buffer.size = 8;
          amount = 16;
          simulate_previous_reads(24, 20);
          int original_buffer_end = io->buffer.end;
          slice result = io_buffer_read(io, amount);
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                             ┌──────────┐ exceeding part > size
            amount:                      ■■■■■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */
          must("chip away previous buffer data to retain only a quantity equal to "\
               "the buffer size");
            int chipped_away_quantity = original_buffer_end - io->buffer.size;
            verify(chipped_away_quantity == 16);
          must("extend the buffer by a quantity equal to the exceeding quantity");
            verify(io->buffer.end == 20);
          must("read the exceeding amount from the io channel");
            verify(io->read.count == 1);
          must("advance the buffer cursor by a quantity equal to the amount to read");
          must("adjust the buffer cursor by subtracting the chipped away quantity");
            verify(io->buffer.cursor == 20);
          must("return a slice of data with length equal to the amount to read");
            verify(result.length == amount);
            verify(streq(result, "3333444444445555"));
          /*           chipped away
                    ┌───────────────┐
                    ┌────────────────────────────────────────┐
            buffer: │                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    │
                    └───────────────────────────────────┬────┘
                                                        ▼  
                                                  cursor == end */
          success();
            io_close(io);
        }
      }

      or_when("the amount to read does not exceed the buffer remaining data") {
        apply(preconditions);
        io->buffer.size = 8;
        amount = 2;
        simulate_previous_reads(22, 18);
        int original_buffer_cursor = io->buffer.cursor;
        slice result = io_buffer_read(io, amount);
        /*        ┌────────────────────────────────────────┐
          channel:│1111111122222222333333334444444455555555│
                  └────────────────────────────────────────┘
          amount:                    ■■
                  ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                  │
                  └───────────────┬─┬───┬──────────────────┘
                                  ▼ ▼   ▼
                            2*size  cursor end */
        must("read the data directly from the buffer and not perform any channel read");
          verify(io->read.count == 0);
        must("advance the buffer cursor by a quantity equal to the amount to read");
          verify(io->buffer.cursor == original_buffer_cursor + amount);
        must("return a slice of data with length equal to the amount to read");
          verify(result.length == amount);
          verify(streq(result, "33"));
        /*        ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒                  │
                  └───────────────────┬─┬──────────────────┘
                                      ▼ ▼  
                                 cursor end */
        success();
          io_close(io);
      }
    }
  }

  #undef preconditions
  #undef simulate_previous_reads
}
