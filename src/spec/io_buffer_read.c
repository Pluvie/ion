spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io over a channel with buffer enabled");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      io->buffer.enabled = true;

  when("the io buffer is not initialized") {
    when("the amount to read is greater than the buffer size") {
      apply(preconditions);
      io->buffer.data = NULL;
      io->buffer.cursor = 0;
      io->buffer.size = 8;
      amount = 12;
      slice result = io_buffer_read(io, amount);
      /*        ┌────────────────────────────────────────┐
        channel:│1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:  ■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │       │                                │
                ├───────┬────────────────────────────────┘
                ▼       ▼
             cursor    size */
      must("initialize the buffer data with a capacity equal to the amount to read");
        verify(io->buffer.data != NULL);
        verify(io->buffer.capacity == amount);
      must("advance the buffer cursor by a quantity equal to the amount to read");
        verify(io->buffer.cursor == amount);
      must("read data from the io channel");
        verify(io->read.count == 1);
      must("return a slice of data with length equal to the amount to read");
        verify(result.length == amount);
        verify(streq(result, "111111112222"));
      /*        ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▓▓▓▓                            │
                └───────┬───┬────────────────────────────┘
                        ▼   ▼
                      size cursor */
      success();
        io_close(io);
    }

    or_when("the amount to read is not greater than the buffer size") {
      apply(preconditions);
      io->buffer.data = NULL;
      io->buffer.cursor = 0;
      io->buffer.size = 8;
      amount = 4;
      slice result = io_buffer_read(io, amount);
      /*        ┌────────────────────────────────────────┐
        channel:│1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:  ■■■■
                ┌────────────────────────────────────────┐
        buffer: │       │                                │
                ├───────┬────────────────────────────────┘
                ▼       ▼
             cursor    size */
      must("initialize the buffer data with a capacity equal to the buffer size");
        verify(io->buffer.data != NULL);
        verify(io->buffer.capacity == io->buffer.size);
      must("advance the buffer cursor by a quantity equal to the amount to read");
        verify(io->buffer.cursor == amount);
      must("read data from the io channel");
        verify(io->read.count == 1);
      must("return a slice of data with length equal to the amount to read");
        verify(result.length == amount);
        verify(streq(result, "1111"));
      /*        ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▒▒▒▒                                │
                └────┬──┬────────────────────────────────┘
                     ▼  ▼
                cursor  size */
      success();
        io_close(io);
    }
  }

  or_when("the io buffer is already initialized") {
    when("the io buffer contains data for less than 2 times the buffer size") {
      when("the amount to read exceeds the buffer remaining data") {
        when("the exceeding part is greater than the buffer size") {
          must("extend the buffer by a quantity equal to the amount to read");
          must("read the exceeding amount from the io channel");
          must("advance the buffer cursor by a quantity equal to the amount to read");
          must("return a slice of data with length equal to the amount to read");
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

          //*spec_code_here*

          /*        ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓               │
                    └────────────────┬───────┬───────────────┘
                                     ▼       ▼
                                2*size  cursor == end */
          success();
        }

        or_when("the exceeding part is not greater than the buffer size") {
          must("extend the buffer by a quantity equal to the buffer size");
          must("read the exceeding amount from the io channel");
          must("advance the buffer cursor by a quantity equal to the amount to read");
          must("return a slice of data with length equal to the amount to read");
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

          //*spec_code_here*

          /*        ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒                  │
                    └───────────────────┬─┬──────────────────┘
                                        ▼ ▼  
                                   cursor end */
          success();
        }
      }

      or_when("the amount to read does not exceed the buffer remaining data") {
        must("read the data directly from the buffer");
        must("not perform any channel read");
        must("advance the buffer cursor by a quantity equal to the amount to read");
        must("return a slice of data with length equal to the amount to read");
        /*        ┌────────────────────────────────────────┐
          channel:│1111111122222222333333334444444455555555│
                  └────────────────────────────────────────┘
          amount:            ■■
                  ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▒▒▒▒  │                       │
                  └──────────┬──┬──┬───────────────────────┘
                             ▼  ▼  ▼
                        cursor end 2*size */

        //*spec_code_here*

        /*        ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▒▒  │                       │
                  └───────────┬─┬──┬───────────────────────┘
                              ▼ ▼  ▼
                        cursor end 2*size */
        success();
      }
    }

    or_when("the io buffer contains data for equal or more than 2 times the buffer size") {
      when("the amount to read exceeds the buffer remaining data") {
        when("the exceeding part is not greater than the buffer size") {
          apply(preconditions);
          io->buffer.size = 8;
          /* Simulates a previous read which had loaded data into the buffer from the
           * io channel. */
          io->buffer.end = 24;
          io->buffer.data = malloc(io->buffer.end);
          memcpy(io->buffer.data, io->memory, io->buffer.end);
          io->cursor = io->buffer.end;
          io->buffer.cursor = 20;
          amount = 10;
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
          must("extend the buffer by a quantity equal to the amount to the buffer size");
            verify(io->buffer.end == 14);
          must("read the exceeding amount from the io channel");
            verify(io->read.count = 1);
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
          /* Simulates a previous read which had loaded data into the buffer from the
           * io channel. */
          io->buffer.end = 24;
          io->buffer.data = malloc(io->buffer.end);
          memcpy(io->buffer.data, io->memory, io->buffer.end);
          io->cursor = io->buffer.end;
          io->buffer.cursor = 20;
          amount = 16;
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
          must("extend the buffer by a quantity equal to the amount to the amount to read");
            verify(io->buffer.end == 20);
          must("read the exceeding amount from the io channel");
            verify(io->read.count = 1);
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
        must("read the data directly from the buffer");
        must("not perform any channel read");
        must("advance the buffer cursor by a quantity equal to the amount to read");
        must("return a slice of data with length equal to the amount to read");
        /*        ┌────────────────────────────────────────┐
          channel:│1111111122222222333333334444444455555555│
                  └────────────────────────────────────────┘
          amount:            ■■
                  ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▒▒▒▒  │                       │
                  └──────────┬──┬──┬───────────────────────┘
                             ▼  ▼  ▼
                        cursor end 2*size */

        //*spec_code_here*

        /*        ┌────────────────────────────────────────┐
          buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒                  │
                  └───────────────────┬─┬──────────────────┘
                                      ▼ ▼  
                                 cursor end */
        success();
      }
    }
  }

  #undef preconditions
}
