spec( io_error_extract ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions(channel_data) \
      struct pipe channel; pipe_open(&channel); \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(channel.reader); \
      write(channel.writer, channel_data.content, channel_data.length);

  when("the io is buffered") {
    when("there are no newlines in the extraction") {
      apply(preconditions(
        s("the error must be shown exactly at the colon : there you go")));
      io->buffer.enabled = true;
      io->buffer.size = 8;

      io_read(io, 52);
      io->buffer.cursor = 46;

      fail("some previous error message to be retained");
      io_error_extract(io);

      must("set the error message at the appropriate cursor location");
        verify(error.occurred == true);
        verify(streq(error.message,
          "some previous error message to be retained, at position 46:\n"\
          " be shown exactly at the colon : there you go\n"\
          "                               ^\n"));

      success();
        io_close(io);
        pipe_close(&channel);
    } end();

    when("there are newlines in the extraction") {
      apply(preconditions(
        s("the error must be \nshown exactly at \nthe colon : there \nyou \ngo")));
      io->buffer.enabled = true;
      io->buffer.size = 8;

      io_read(io, 54);
      io->buffer.cursor = 48;

      fail("some previous error message to be retained");
      io_error_extract(io);

      must("set the error message at the appropriate cursor location");
        verify(error.occurred == true);
        verify(streq(error.message,
          "some previous error message to be retained, at position 48:\n"\
          "e \\shown exactly at \\the colon : there \\you \\g\n"\
          "                               ^\n"));

      success();
        io_close(io);
        pipe_close(&channel);
    } end();
  } end();

  when("the io is not buffered") {
    when("there are no newlines in the extraction") {
      apply(preconditions(
        s("the error must be shown exactly at the colon : there you go")));

      io_read(io, 52);
      io->cursor = 46;

      fail("some previous error message to be retained");
      io_error_extract(io);

      must("set the error message at the appropriate cursor location");
        verify(error.occurred == true);
        verify(streq(error.message,
          "some previous error message to be retained, at position 46:\n"\
          "the error must be shown exactly at the colon :\n"\
          "                                             ^\n"));

      success();
        io_close(io);
        pipe_close(&channel);
    } end();

    when("there are newlines in the extraction") {
      apply(preconditions(
        s("the error must be \nshown exactly at \nthe colon : there \nyou \ngo")));

      io_read(io, 54);
      io->cursor = 48;

      fail("some previous error message to be retained");
      io_error_extract(io);

      must("set the error message at the appropriate cursor location");
        verify(error.occurred == true);
        verify(streq(error.message,
          "some previous error message to be retained, at position 48:\n"\
          "the error must be \\shown exactly at \\the colon :\n"\
          "                                               ^\n"));

      success();
        io_close(io);
        pipe_close(&channel);
    } end();
  } end();

  #undef preconditions
}
