spec( io_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io object");
    #define valid_io_precondition \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555"));

  precondition("a greater than zero amount");
    #define valid_amount_precondition \
      amount = 10;

  when("the io is buffered") {
    #define buffer_enabled_condition \
      io->buffer.enabled = true; \
      io->buffer.size = 16;

    and_when("the io buffer is not initialized") {
      #define buffer_not_initialized_condition \
        io->buffer.data = NULL; \
        io->read.count = 0;

      apply(valid_io_precondition);
      apply(valid_amount_precondition);
      apply(buffer_enabled_condition);
      apply(buffer_not_initialized_condition);
      slice result = io_read(io, amount);

      must("not fail");
        verify(error.occurred == false);

      must("initialize the io buffer");
        verify(io->buffer.data != NULL);
        verify(io->buffer.capacity == io->buffer.size);
        verify(streq((char*) io->buffer.data, "1111111122222222"));

      must("read the data from the io channel");
        verify(io->read.count == 1);

      must("store the data in the io buffer");
        verify(result.data == io->buffer.data);

      must("advance the io cursor of the buffer size");
        verify(io->cursor == io->buffer.size);

      must("return a slice of data of the given amount");
        verify(result.length == amount);
        verify(streq(result, "1111111122"));

      success();
        io_close(io);

      #undef buffer_not_initialized_condition
    }

    and_when("the io buffer is already initialized") {
      #define buffer_initialized_condition \
        io_buffer_init(io, 4); \
        io->read.count = 0;

      apply(valid_io_precondition);
      apply(valid_amount_precondition);
      apply(buffer_enabled_condition);
      apply(buffer_initialized_condition);
      int original_io_cursor_position = io->cursor;
      slice result = io_read(io, amount);

      must("not fail");
        verify(error.occurred == false);

      must("read the data from the io buffer");
        verify(io->read.count == 0);

      must("store the data in the io buffer");
        verify(result.data == io->buffer.data + 4);

      must("not advance the io cursor");
        verify(io->cursor == original_io_cursor_position);

      must("return a slice of data of the given amount");
        verify(result.length == amount);
        verify(streq(result, "1111222222"));

      success();
        io_close(io);

      #undef buffer_initialized_condition
    }

    #undef buffer_enabled_condition
  }

  when("the io is not buffered") {
    #define buffer_not_enabled_condition \
      io->buffer.enabled = false; \
      io->read.count = 0;

    apply(valid_io_precondition);
    apply(valid_amount_precondition);
    apply(buffer_not_enabled_condition);
    slice result = io_read(io, amount);

    must("not fail");
      verify(error.occurred == false);

    must("read the data from the io channel");
      verify(io->read.count == 1);

    must("store the data in the io storage");
      verify(io->storage != NULL);
      verify(result.data == io->storage);

    must("advance the io cursor of the given amount");
      verify(io->cursor == amount);

    must("return a slice of data of the given amount");
      verify(result.length == amount);
      verify(streq(result, "1111111122"));

    success();
      io_close(io);

    #undef buffer_not_enabled_condition
  }

  #undef valid_io_precondition
  #undef valid_amount_precondition
}
