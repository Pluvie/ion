spec( json_parse_spaces ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io starts with spaces") {
      apply(preconditions);
      *io = io(s(" \t  \n  "));
      int result = json_parse_spaces(io);

      must("return the length of the spaces");
        verify(result == 7);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      apply(preconditions);
      *io = io(s("123    "));
      int result = json_parse_spaces(io);

      must("return 0");
        verify(result == 0);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io starts with spaces") {
      apply(preconditions);
      *io = io(s(" \t  \n  , \"abc\": 123"));
      int result = json_parse_spaces(io);

      must("return the length of the spaces");
        verify(result == 7);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      apply(preconditions);
      *io = io(s("123    , 123"));
      int result = json_parse_spaces(io);

      must("return 0");
        verify(result == 0);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  #undef preconditions
}
