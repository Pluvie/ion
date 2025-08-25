spec( io_channel_read ) {

  argument(struct io* io);
  argument(int amount);
  argument(void* address);

  precondition("a valid io");
  precondition("the underlying channel has some data available to read");
    #define preconditions \
      string data = s("1111111122222222333333334444444455555555"); \
      io = memory_alloc(spec_allocator, sizeof(struct io));

  when("the io channel is IO_MEMORY") {
    when("the io cursor plus amount is not greater than the io length") {
      apply(preconditions);
      *io = io(data);
      io->cursor = 4;
      amount = 8;
      address = NULL;
      int original_cursor = io->cursor;

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == original_cursor + amount);
      must("return a slice of data with length equal to the given amount");
        slice result = { "11112222", 8 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();

    when("the io cursor plus amount is greater than the io length") {
      apply(preconditions);
      *io = io(data);
      io->cursor = 36;
      amount = 8;
      address = NULL;

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor to the io length");
        verify(io->cursor == io->length);
      must("return a slice of data with length equal to the available data on the io");
        slice result = { "55555", 4 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();

    when("the io cursor is greater or equal than the io length") {
      apply(preconditions);
      *io = io(data);
      io->cursor = 40;
      amount = 8;
      address = NULL;
      int original_cursor = io->cursor;

      io_channel_read(io, amount, address);

      must("not read from the channel");
        verify(io->read.count == 0);
      must("not advance the io cursor");
        verify(io->cursor == original_cursor);
      must("return an empty slice of data");
        slice result = { NULL, 0 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();
  } end();

  when("the io channel is IO_FILE") {
    #define io_channel_file_condition \
      struct file file = file_create("tmp/io"); \
      *io = io(&file); \
      address = (char [64]) { 0 };

    when("the channel has available data equal or greater than the given amount") {
      apply(preconditions);
      apply(io_channel_file_condition);
      *io = io(data);
      amount = 8;
      file_write(&file, data.content, amount);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == amount);
      must("return a slice of data with length equal to the given amount");
        slice result = { "11111111", 8 };
        verify(eq(io->result, result));
      must("store the result into the address");
        verify(memeq(address, io->result.pointer, amount));

      success();
        io_close(io);
        file_delete(&file);
    } end();

    when("the channel has available data lesser than the given amount") {
      apply(preconditions);
      *io = io(data);
      io->cursor = 36;
      amount = 8;
      address = NULL;

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor to the io length");
        verify(io->cursor == io->length);
      must("return a slice of data with length equal to the available data on the io");
        slice result = { "55555", 4 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();

    when("the channel fails") {
      apply(preconditions);
      *io = io(data);
      io->cursor = 40;
      amount = 8;
      address = NULL;
      int original_cursor = io->cursor;

      io_channel_read(io, amount, address);

      must("not read from the channel");
        verify(io->read.count == 0);
      must("not advance the io cursor");
        verify(io->cursor == original_cursor);
      must("return an empty slice of data");
        slice result = { NULL, 0 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();
  } end();

  #undef preconditions
}
