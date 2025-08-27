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
    #define io_channel_memory_condition \
      *io = io(data); \
      address = NULL;

    when("the io cursor plus amount is not greater than the io length") {
      apply(preconditions);
      apply(io_channel_memory_condition);
      io->cursor = 4;
      amount = 8;

      int original_cursor = io->cursor;
      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == original_cursor + amount);
      must("return a string of data with length equal to the given amount");
        string result = { "11112222", 8 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();

    when("the io cursor plus amount is greater than the io length") {
      apply(preconditions);
      apply(io_channel_memory_condition);
      io->cursor = 36;
      amount = 8;

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor to the io length");
        verify(io->cursor == io->length);
      must("return a string of data with length equal to the available data on the io");
        string result = { "55555", 4 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();

    when("the io cursor is greater or equal than the io length") {
      apply(preconditions);
      apply(io_channel_memory_condition);
      io->cursor = 40;
      amount = 8;

      int original_cursor = io->cursor;
      io_channel_read(io, amount, address);

      must("not read from the channel");
        verify(io->read.count == 0);
      must("not advance the io cursor");
        verify(io->cursor == original_cursor);
      must("return an empty string of data");
        string result = { NULL, 0 };
        verify(eq(io->result, result));

      success();
        io_close(io);
    } end();
  } end();


  when("the io channel is IO_FILE") {
    #define io_channel_file_condition \
      struct file file = file_create(s("tmp/io")); \
      *io = io(&file); \
      address = alloc(64);

    when("the channel has available data equal or greater than the given amount") {
      apply(preconditions);
      apply(io_channel_file_condition);
      amount = 8;
      file_write(&file, data.pointer, amount);
      lseek(file.descriptor, 0, SEEK_SET);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == amount);
      must("return a string of data with length equal to the given amount");
        string result = { "11111111", 8 };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, amount));

      success();
        io_close(io);
        file_close(&file);
        file_delete(&file);
    } end();

    when("the channel has available data lesser than the given amount") {
      apply(preconditions);
      apply(io_channel_file_condition);
      amount = 8;
      int channel_available_data = amount - 4;
      file_write(&file, data.pointer, channel_available_data);
      lseek(file.descriptor, 0, SEEK_SET);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the channel available data");
        verify(io->cursor == channel_available_data);
      must("return a string of data with length equal to the channel available data");
        string result = { "1111", channel_available_data };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, channel_available_data));

      success();
        io_close(io);
        file_close(&file);
        file_delete(&file);
    } end();
  } end();


  when("the io channel is IO_PIPE") {
    #define io_channel_pipe_condition \
      struct pipe pipes = pipe_open(); \
      *io = io(&pipes); \
      address = alloc(64);

    when("the channel has available data equal or greater than the given amount") {
      apply(preconditions);
      apply(io_channel_pipe_condition);
      amount = 8;
      pipe_write(&pipes, data.pointer, amount);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == amount);
      must("return a string of data with length equal to the given amount");
        string result = { "11111111", 8 };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, amount));

      success();
        io_close(io);
        pipe_close(&pipes);
    } end();

    when("the channel has available data lesser than the given amount") {
      apply(preconditions);
      apply(io_channel_pipe_condition);
      amount = 8;
      int channel_available_data = amount - 4;
      pipe_write(&pipes, data.pointer, channel_available_data);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the channel available data");
        verify(io->cursor == channel_available_data);
      must("return a string of data with length equal to the channel available data");
        string result = { "1111", channel_available_data };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, channel_available_data));

      success();
        io_close(io);
        pipe_close(&pipes);
    } end();
  } end();


  /*
  when("the io channel is IO_SOCKET") {
    #define io_channel_socket_condition \
      struct socket client = socket_open(); \
      struct socket server = socket_open(); \
      *io = io(&server); \
      address = alloc(64);

    when("the channel has available data equal or greater than the given amount") {
      apply(preconditions);
      apply(io_channel_socket_condition);
      amount = 8;
      socket_write(&server, data.pointer, amount);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the given amount");
        verify(io->cursor == amount);
      must("return a string of data with length equal to the given amount");
        string result = { "11111111", 8 };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, amount));

      success();
        io_close(io);
        socket_close(&server);
    } end();

    when("the channel has available data lesser than the given amount") {
      apply(preconditions);
      apply(io_channel_socket_condition);
      amount = 8;
      int channel_available_data = amount - 4;
      socket_write(&server, data.pointer, channel_available_data);

      io_channel_read(io, amount, address);

      must("read from the channel");
        verify(io->read.count == 1);
      must("advance the cursor by the channel available data");
        verify(io->cursor == channel_available_data);
      must("return a string of data with length equal to the channel available data");
        string result = { "1111", channel_available_data };
        verify(eq(io->result, result));
      must("store the channel read result into the address");
        verify(byte_eq(address, io->result.pointer, channel_available_data));

      success();
        io_close(io);
        socket_close(&server);
    } end();
  } end();
  */

  #undef preconditions
}
