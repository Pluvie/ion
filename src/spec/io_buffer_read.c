spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io over a channel");
  precondition("the io must have the buffer enabled");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      io->buffer.enabled = true;

  when("the io buffer is not initialized") {
    when("the amount to read is greater than the buffer size") {
      must("initialize the buffer data with a capacity equal to the amount to read");
      must("advance the buffer cursor by the given amount");
      must("read data from the io channel");
      must("return a slice of data of the given amount");
      /*        ┌────────────────────────────────────────┐
        channel:│1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:  ■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │       │                                │
                ├───────┬────────────────────────────────┘
                ▼       ▼
             cursor    size */
      apply(preconditions);
      io->buffer.data = NULL;
      io->buffer.cursor = 0;
      io->buffer.size = 8;
      amount = 12;
      slice result = io_buffer_read(io, amount);
      verify(io->buffer.data != NULL);
      verify(io->buffer.capacity == amount);
      verify(io->buffer.cursor == amount);
      verify(io->read.count == 1);
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
      must("initialize the buffer data with a capacity equal to the buffer size");
      must("advance the buffer cursor by the given amount");
      must("read data from the io channel");
      must("return a slice of data of the given amount");
      /*        ┌────────────────────────────────────────┐
        channel:│1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:  ■■■■
                ┌────────────────────────────────────────┐
        buffer: │       │                                │
                ├───────┬────────────────────────────────┘
                ▼       ▼
             cursor    size */
      apply(preconditions);
      io->buffer.data = NULL;
      io->buffer.cursor = 0;
      io->buffer.size = 8;
      amount = 4;
      slice result = io_buffer_read(io, amount);
      verify(io->buffer.data != NULL);
      verify(io->buffer.capacity == io->buffer.size);
      verify(io->buffer.cursor == amount);
      verify(io->read.count == 1);
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
          must("advance the buffer cursor by the given amount");
          must("return a slice of data of the given amount");
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
          must("advance the buffer cursor by the given amount");
          must("return a slice of data of the given amount");
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
        must("advance the buffer cursor by the given amount");
        must("return a slice of data of the given amount");
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
        when("the exceeding part is greater than the buffer size") {
          must("extend the buffer by a quantity equal to the amount to read");
          must("chip away previous buffer data and retain only a quantity equal to "\
               "the buffer size");
          must("read the exceeding amount from the io channel");
          must("advance the buffer cursor by the given amount");
          must("adjust the buffer cursor by subtracting the chipped away quantity");
          must("return a slice of data of the given amount");
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                             ┌────┐ exceeding part
            amount:                      ■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */

          //*spec_code_here*

          /*           chipped away
                    ┌───────────────┐
                    ┌────────────────────────────────────────┐
            buffer: │                ▓▓▓▓▓▓▓▓▓▓▓▓▒▒          │
                    └───────────────────────────┬─┬──────────┘
                                                ▼ ▼
                                             cursor end */
          success();
        }
        or_when("the exceeding part is not greater than the buffer size") {
          must("extend the buffer by a quantity equal to the amount to the buffer size");
          must("chip away previous buffer data and retain only a quantity equal to "\
               "the buffer size");
          must("read the exceeding amount from the io channel");
          must("advance the buffer cursor by the given amount");
          must("adjust the buffer cursor by subtracting the chipped away quantity");
          must("return a slice of data of the given amount");
          /*        ┌────────────────────────────────────────┐
            channel:│1111111122222222333333334444444455555555│
                    └────────────────────────────────────────┘
                                             ┌──────────┐ exceeding part
            amount:                      ■■■■■■■■■■■■■■■■
                    ┌────────────────────────────────────────┐
            buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒                │
                    └───────────────┬───┬───┬────────────────┘
                                    ▼   ▼   ▼
                              2*size  cursor end */

          //*spec_code_here*

          /*           chipped away
                    ┌───────────────┐
                    ┌────────────────────────────────────────┐
            buffer: │                ▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓    │
                    └───────────────────────────────────┬────┘
                                                        ▼  
                                                  cursor == end */
          success();
        }
      }

      or_when("the amount to read does not exceed the buffer remaining data") {
        must("read the data directly from the buffer");
        must("not perform any channel read");
        must("advance the buffer cursor by the given amount");
        must("return a slice of data of the given amount");
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
