spec( json_parse_bool ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io)); \
      *io = io(s("  { \"a\":   true,   \"b\": false } "));

  when("the io reads a string equal to `true`") {
    apply(preconditions);
    int io_cursor_starting_position = 11;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_bool(io);

    must("not fail");
      verify(unlikely(failure.occurred) == false);

    must("return lengthof(\"true\")");
      verify(result == lengthof("true"));

    must("restore the io cursor to the original position");
      verify(io->cursor == io_cursor_starting_position);

    success();
      io_close(io);

  } end();

  when("the io reads a string equal to `false`") {
    apply(preconditions);
    int io_cursor_starting_position = 24;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_bool(io);

    must("not fail");
      verify(unlikely(failure.occurred) == false);

    must("return lengthof(\"false\")");
      verify(result == lengthof("false"));

    must("restore the io cursor to the original position");
      verify(io->cursor == io_cursor_starting_position);

    success();
      io_close(io);

  } end();

  when("the io reads other strings") {
    apply(preconditions);
    int io_cursor_starting_position = 3;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_bool(io);

    must("not fail");
      verify(unlikely(failure.occurred) == false);

    must("return -1");
      verify(result == -1);

    must("restore the io cursor to the original position");
      verify(io->cursor == io_cursor_starting_position);

    success();
      io_close(io);

  } end();

  when("the io read fails") {
    apply(preconditions);
    /* An invalid io channel. Shall fail upon calling the `io_read` function. */
    io->channel = -1;

    int io_cursor_starting_position = 3;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_bool(io);

    must("fail with a specific error");
      verify(unlikely(failure.occurred) == true);
      verify(streq(failure.message, "io: invalid channel"));

    must("return -1");
      verify(result == -1);

    success();
      io_close(io);

  } end();

  #undef preconditions
}
