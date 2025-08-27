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
    io_read(io, amount);

    must("not fail");
      verify(failure.occurred == false);
    must("read the data from the io channel");
      verify(io->read.count == 1);
    must("return the data in the io result");
      verify(io->result.pointer != NULL);
    must("advance the io cursor by the given amount");
      verify(io->cursor == amount);
    must("return a string of data of the given amount");
      string result = { "1111111122", amount };
      verify(eq(io->result, result));

    success();
      io_close(io);
  } end();

  when("the io is buffered") {
    must("behave exactly like the `io_buffer_read` function");
    /* Refer to the `io_buffer_read` spec for more details on its behaviour. */

    apply(preconditions);
    io->buffer.enabled = true;
    io_read(io, amount);
    struct io io_with_read = *io;

    apply(preconditions);
    io->buffer.enabled = true;
    io_buffer_read(io, amount);
    struct io io_with_buffer_read = *io;

    verify(io_with_read.cursor == io_with_buffer_read.cursor);
    verify(io_with_read.buffer.cursor == io_with_buffer_read.buffer.cursor);

    verify(eq(io_with_read.result, io_with_buffer_read.result));
    verify(eq(io_with_read.buffer.data, io_with_buffer_read.buffer.data));

    success();
      io_close(&io_with_read);
      io_close(&io_with_buffer_read);
  } end();

  #undef preconditions
}
