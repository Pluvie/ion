spec( io_buffer_extend ) {

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
 
  when("the io buffer cursor is inferior to the io buffer size") {
    #define io_buffer_cursor_before_size_condition \
      io_buffer_read(io, 4);

    and_when("the amount fits into the buffer size") {
      amount = 14;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      apply(io_buffer_cursor_before_size_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:      ■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒               │        │
                └────────┬──────┬───────────────┬────────┘
                         ▼      ▼               ▼
                      cursor   end            size */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer by the buffer size");
        verify(io->buffer.capacity == 16 + io->buffer.size);

      success();
        io_close(io);
    }

    and_when("the amount exceeds the buffer size") {
      amount = 30;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:      ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒               │        │
                └────────┬──────┬───────────────┬────────┘
                         ▼      ▼               ▼
                      cursor   end            size */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer capacity by the given amount");
        verify(io->buffer.capacity == 16 + amount);

      success();
        io_close(io);
    }

    #undef io_buffer_cursor_before_size_condition
  }

  when("the io buffer cursor is inferior to the io buffer size") {
    #define io_buffer_cursor_after_size_condition \
      io_buffer_read(io, 14); \
      int original_buffer_capacity = io->buffer.capacity;

    and_when("the amount fits into the buffer size") {
      amount = 14;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      apply(io_buffer_cursor_after_size_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:                    ■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒        │       │
                └───────────────┬─┬─────────────┬────────┘
                                ▼ ▼             ▼                ▼
                             size cursor       end            capacity  */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer by the buffer size");
        verify(io->buffer.capacity == original_buffer_capacity + io->buffer.size);

      must("set the io buffer cursor to 0");
        verify(io->buffer.cursor == 0);

      success();
        io_close(io);
    }

    and_when("the amount exceeds the buffer size") {
      amount = 28;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      apply(io_buffer_cursor_after_size_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:                    ■■■■■■■■■■■■■■■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▒▒        │       │
                └───────────────┬─┬─────────────┬────────┘
                                ▼ ▼             ▼                ▼
                             size cursor       end            capacity  */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer capacity by the given amount");
        verify(io->buffer.capacity == original_buffer_capacity + amount);

      must("set the io buffer cursor to 0");
        verify(io->buffer.cursor == 0);

      success();
        io_close(io);
    }

    #undef io_buffer_cursor_after_size_condition
  }

  #undef io_buffer_enabled_precondition
  #undef io_buffer_initialized_precondition
}
