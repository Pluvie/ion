spec( io_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io over a channel");
  precondition("a greater than zero amount");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      amount = 10;

  when("the io is not buffered") {
    apply(preconditions);
    io->buffer.enabled = false;
    slice result = io_read(io, amount);

    must("not fail");
      verify(error.occurred == false);
    must("read the data from the io channel");
      verify(io->read.count == 1);
    must("store the data in the io storage");
      verify(io->storage != NULL);
      verify(result.data == io->storage);
    must("advance the io cursor by the given amount");
      verify(io->cursor == amount);
    must("return a slice of data of the given amount");
      verify(result.length == amount);
      verify(streq(result, "1111111122"));

    success();
      io_close(io);
  }

  or_when("the io is buffered") {
    must("behave exactly like the `io_buffer_read` function");
    /* Refer to the `io_buffer_read` spec for more details on its behaviour. */

    apply(preconditions);
    io->buffer.enabled = true;
    slice result_of_read = io_read(io, amount);
    struct io io_with_read = *io;

    apply(preconditions);
    io->buffer.enabled = true;
    slice result_of_buffer_read = io_buffer_read(io, amount);
    struct io io_with_buffer_read = *io;

    verify(eq(result_of_read, result_of_buffer_read));

    /* Equality of io structs is done without taking in consideration its buffer data
     * pointer value because, of course, the buffer shall malloc on two different
     * addresses. */
    void* io_with_read_data = io_with_read.buffer.data;
    void* io_with_buffer_read_data = io_with_buffer_read.buffer.data;
    io_with_read.buffer.data = NULL;
    io_with_buffer_read.buffer.data = NULL;
    verify(memeq(&io_with_read, &io_with_buffer_read, sizeof(struct io)));

    success();
      io_with_read.buffer.data = io_with_read_data;
      io_with_buffer_read.buffer.data = io_with_buffer_read_data;
      io_close(&io_with_read);
      io_close(&io_with_buffer_read);
  }

  #undef preconditions
}
