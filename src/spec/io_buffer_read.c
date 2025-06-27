spec( io_buffer_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled");
    #define io_buffer_enabled_precondition \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      io->buffer.enabled = true;

  precondition("the io buffer has already been initialized");
    #define io_buffer_initialized_precondition \
      io->buffer.size = 16; \
      io->buffer.capacity = 16; \
      io_buffer_init(io, 4); \
      io->read.count = 0;

  when("the amount fits into the io buffer available data") {
    amount = 6;
    apply(io_buffer_enabled_precondition);
    apply(io_buffer_initialized_precondition);
    slice result = io_buffer_read(io, amount);

    /*
              ┌────────────────────────────────────────┐
      io:     │1111111122222222333333334444444455555555│
              └────────────────────────────────────────┘
      amount:      ■■■■■■
              ┌────────────────────────────────────────┐
      buffer: │▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒               │        │
              └────┬──────────┬───────────────┬────────┘
                   ▼          ▼               ▼
                cursor        end           size */

    must("not fail");
      verify(error.occurred == false);

    must("advance the io buffer cursor by the given amount");
      verify(io->buffer.cursor == 4 + amount);

    must("read the data from the buffer without performing any read from the io channel");
      verify(io->read.count == 0);

    must("return a slice of data of the given amount");
      verify(result.length == amount);
      verify(streq(result, "111122"));

    success();
      io_close(io);
  }

  when("the amount exceeds the io buffer available data") {
    and_when("the amount fits into the buffer size") {
      amount = 14;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      slice result = io_buffer_read(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:      ■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒               │        │
                └────┬──────────┬───────────────┬────────┘
                     ▼          ▼               ▼
                  cursor        end           size */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer by the buffer size");
        verify(io->buffer.capacity == 16 + io->buffer.size);

      must("advance the io buffer cursor by the given amount");
        verify(io->buffer.cursor == 4 + amount);

      must("read the exceeding amount from the io channel");
        verify(io->read.count == 1);

      must("return a slice of data of the given amount");
        verify(result.length == amount);
        verify(streq(result, "11112222222233"));

      success();
        io_close(io);
    }

    and_when("the amount exceeds the buffer size") {
      amount = 30;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      slice result = io_buffer_read(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:      ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒               │        │
                └────┬──────────┬───────────────┬────────┘
                     ▼          ▼               ▼
                  cursor        end           size */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer capacity by the given amount");
        verify(io->buffer.capacity == 16 + amount);

      must("advance the io buffer cursor by the given amount");
        verify(io->buffer.cursor == 4 + amount);

      must("read the exceeding amount from the io channel");
        verify(io->read.count == 1);

      must("return a slice of data of the given amount");
        verify(result.length == amount);
        verify(streq(result, "111122222222333333334444444455"));

      success();
        io_close(io);
    }
  }

  #undef io_buffer_enabled_precondition
  #undef io_buffer_initialized_precondition
}
