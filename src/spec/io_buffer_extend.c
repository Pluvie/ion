spec( io_buffer_extend ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io with buffer enabled");
    #define io_buffer_enabled_precondition \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      io->buffer.enabled = true; \
      io->buffer.size = 12;

  precondition("an amount to read that is not fully available in the buffer data "
               "and thus forces the buffer to read from the io channel");
    #define io_buffer_must_read_from_channel_precondition \
      verify(io->buffer.cursor + amount > io->buffer.end);
 
  when("the io buffer has not yet grown past 2 times the buffer size") {
    #define io_buffer_undersize_condition \
      io_buffer_init(io, 8);

    and_when("the amount to read is lesser or equal than the buffer size") {
      amount = 14;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_must_read_from_channel_precondition);
      apply(io_buffer_undersize_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:      ■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒       |                │
                └────────┬──────┬───────┬────────────────┘
                         ▼      ▼       ▼
                      cursor   size    capacity */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer by the buffer size");
        verify(io->buffer.capacity == 16 + io->buffer.size);

      success();
        io_close(io);
    }

    and_when("the amount to read is greater than the buffer size") {
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
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒       |                │
                └────────┬──────┬───────┬────────────────┘
                         ▼      ▼       ▼
                      cursor   size    capacity */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer capacity by the given amount");
        verify(io->buffer.capacity == 16 + amount);

      success();
        io_close(io);
    }

    #undef io_buffer_undersize_condition
  }

  when("the io buffer capacity is greater or equal than 2 times the buffer size") {
    #define io_buffer_oversize_condition \
      io->buffer.capacity = 34;

    and_when("the amount to read is lesser or equal than the buffer size") {
      amount = 14;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      apply(io_buffer_oversize_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:          ■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒                  |     │
                └────────┬──────┬──────────────────┬─────┘
                         ▼      ▼                  ▼
                      cursor   size             capacity */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer by the buffer size");
        verify(io->buffer.capacity == original_buffer_capacity + io->buffer.size);

      must("set the io buffer cursor to 0");
        verify(io->buffer.cursor == 0);

      success();
        io_close(io);
    }

    and_when("the amount to read is greater than the buffer size") {
      amount = 28;
      apply(io_buffer_enabled_precondition);
      apply(io_buffer_initialized_precondition);
      apply(io_buffer_oversize_condition);
      io_buffer_extend(io, amount);

      /* 
                ┌────────────────────────────────────────┐
        io:     │1111111122222222333333334444444455555555│
                └────────────────────────────────────────┘
        amount:          ■■■■■■■■■■■■■■■■■■■■■■■■■■■■
                ┌────────────────────────────────────────┐
        buffer: │▓▓▓▓▓▓▓▓▒▒▒▒▒▒▒▒                  |     │
                └────────┬──────┬──────────────────┬─────┘
                         ▼      ▼                  ▼
                      cursor   size             capacity */

      must("not fail");
        verify(error.occurred == false);

      must("extend the io buffer capacity by the given amount");
        verify(io->buffer.capacity == original_buffer_capacity + amount);

      must("set the io buffer cursor to 0");
        verify(io->buffer.cursor == 0);

      success();
        io_close(io);
    }

    #undef io_buffer_oversize_condition
  }

  #undef io_buffer_enabled_precondition
  #undef io_buffer_initialized_precondition
}
