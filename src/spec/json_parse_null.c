spec( json_parse_null ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      *io = io(s("  { \"a\":   null } "));

  when("the io reads a string equal to `true`") {
    apply(preconditions);
    int io_cursor_starting_position = 11;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_null(io);

    must("not fail");
      verify(error.occurred == false);

    must("return lengthof(\"null\")");
      verify(result == lengthof("null"));

    must("restore the io cursor to the original position");
      verify(io->cursor == io_cursor_starting_position);

    success();
      io_close(io);

  } end();

  when("the io reads other strings") {
    apply(preconditions);
    int io_cursor_starting_position = 3;
    io->cursor = io_cursor_starting_position;
    int result = json_parse_null(io);

    must("not fail");
      verify(error.occurred == false);

    must("return 0");
      verify(result == 0);

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
    int result = json_parse_null(io);

    must("fail with a specific error");
      verify(error.occurred == true);
      verify(streq(error.message, "io: invalid channel"));

    must("return -1");
      verify(result == -1);

    success();
      io_close(io);

  } end();

  #undef preconditions
}
