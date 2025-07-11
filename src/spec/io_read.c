spec( io_read ) {

  argument(struct io* io);
  argument(int amount);

  precondition("a valid io over a channel");
  precondition("a greater than zero amount");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("1111111122222222333333334444444455555555")); \
      amount = 10;

  when("the io is buffered") {
    must("behave exactly like the `io_buffer_read` function");
    /* Refer to the `io_buffer_read` spec for more details on its behaviour. */

    apply(preconditions);
    io->buffer.enabled = true;
    slice result_of_read = io_read(io, amount);
    struct io io_with_read = * io;

    apply(preconditions);
    io->buffer.enabled = true;
    slice result_of_buffer_read = io_buffer_read(io, amount);
    struct io io_with_buffer_read = * io;

    verify(io_with_read.memory == io_with_buffer_read.memory);
    verify(io_with_read.channel == io_with_buffer_read.channel);
    verify(io_with_read.length == io_with_buffer_read.cursor);
    verify(io_with_read.storage == io_with_buffer_read.storage);
    verify(io_with_read.read.count == io_with_buffer_read.read.count);
    verify(io_with_read.buffer.enabled == io_with_buffer_read.buffer.enabled);
    verify(io_with_read.buffer.retained == io_with_buffer_read.buffer.retained);
    verify(io_with_read.buffer.size == io_with_buffer_read.buffer.size);
    verify(io_with_read.buffer.end == io_with_buffer_read.buffer.end);
    verify(io_with_read.buffer.cursor == io_with_buffer_read.buffer.cursor);
    verify(io_with_read.buffer.capacity == io_with_buffer_read.buffer.capacity);
    verify(eq(result_of_read, result_of_buffer_read));

    success();
      io_close(&io_with_read);
      io_close(&io_with_buffer_read);
  }

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

  #undef preconditions
}
