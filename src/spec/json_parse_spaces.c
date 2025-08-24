spec( json_parse_spaces ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io starts with spaces") {
      apply(preconditions);
      *io = io(s(" \t  \n  "));
      int original_cursor_position = io->cursor;
      int result = json_parse_spaces(io);

      must("return the length of the spaces");
        verify(result == 7);
      must("advance the cursor position");
        verify(io->cursor == original_cursor_position + result);
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      apply(preconditions);
      *io = io(s("123    "));
      int original_cursor_position = io->cursor;
      int result = json_parse_spaces(io);

      must("return 0");
        verify(result == 0);
      must("advance the cursor position");
        verify(io->cursor == original_cursor_position + result);
      success();
        io_close(io);
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io starts with spaces") {
      apply(preconditions);
      *io = io(s(" \t  \n  , \"abc\": 123"));
      int original_cursor_position = io->cursor;
      int result = json_parse_spaces(io);

      must("return the length of the spaces");
        verify(result == 7);
      must("advance the cursor position");
        verify(io->cursor == original_cursor_position + result);
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      apply(preconditions);
      *io = io(s("123    , 123"));
      int original_cursor_position = io->cursor;
      int result = json_parse_spaces(io);

      must("return 0");
        verify(result == 0);
      must("advance the cursor position");
        verify(io->cursor == original_cursor_position + result);
      success();
        io_close(io);
    } end();
  } end();

  when("the io read fails") {
    apply(preconditions);
    /* An invalid io channel. Shall fail upon calling the `io_read` function. */
    io->channel = -1;
    int result = json_parse_spaces(io);

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
