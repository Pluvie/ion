spec( json_parse_bool ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \

  when("the io reads a string equal to `true`") {
    string source = s("  { \"a\":   true,   \"b\": false } ");
    apply(preconditions);
    int io_cursor_starting_position = 11;
    io->cursor = io_cursor_starting_position;

    bool value;
    bool result = json(parse_bool, io, &source, &value);

    must("return true");
      verify(result == true);
    must("advance the cursor position to consume the boolean value");
      print(">>> %li | %li",io_cursor_starting_position, io->cursor); 
      verify(io->cursor == io_cursor_starting_position + 4);
    success();
      io_close(io);
  } end();

  when("the io reads a string equal to `false`") {
    string source = s("  { \"a\":   true,   \"b\": false } ");
    apply(preconditions);
    int io_cursor_starting_position = 24;
    io->cursor = io_cursor_starting_position;

    bool value;
    bool result = json(parse_bool, io, &source, &value);

    must("return true");
      verify(result == true);
    must("advance the cursor position to consume the boolean value");
      verify(io->cursor == io_cursor_starting_position + 5);
    success();
      io_close(io);
  } end();

  when("the io reads other strings") {
    string source = s("  { \"a\":   true,   \"b\": false } ");
    apply(preconditions);
    int io_cursor_starting_position = 3;
    io->cursor = io_cursor_starting_position;

    bool value;
    bool result = json(parse_bool, io, &source, &value);

    must("return false");
      verify(result == false);
    must("restore the io cursor to the original position");
      verify(io->cursor == io_cursor_starting_position);
    success();
      io_close(io);
  } end();

  when("the io read fails") {
    /* An invalid file. Shall fail upon calling the `io_read` function. */
    struct file file = file_open(s("/wrong/path"));
    apply(preconditions);
    io_buffer_init(io, 0);

    bool value;
    json(parse_bool, io, &file, &value);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("file open error: No such file or directory"));
    must("restore the io cursor to the original position");
      verify(io->cursor == 0);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
