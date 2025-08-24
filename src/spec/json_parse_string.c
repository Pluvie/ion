spec( json_parse_string ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io starts with string") {
      apply(preconditions);
      *io = io(s("\" \t  \n  \""));
      int result = json_parse_string(io);

      must("return the length of the string");
        verify(result == 9);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      apply(preconditions);
      *io = io(s("123    "));
      int result = json_parse_string(io);

      must("return -1");
        verify(result == -1);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io starts with string") {
      apply(preconditions);
      *io = io(s("\"abc\": 123 ,  \t  \n"));
      int result = json_parse_string(io);

      must("return the length of the string");
        verify(result == 5);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      apply(preconditions);
      *io = io(s("123    , 123"));
      int result = json_parse_string(io);

      must("return -1");
        verify(result == -1);
      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the io has reached the end of input") {
    apply(preconditions);
    *io = io(s("\"123\"    "));
    io->cursor = 9;
    int result = json_parse_string(io);

    must("return -1");
      verify(result == -1);
    must("restore the cursor position");
      verify(io->cursor == 9);
    success();
      io_close(io);
  } end();

  when("the io read fails") {
    apply(preconditions);
    /* An invalid io channel. Shall fail upon calling the `io_read` function. */
    io->channel = -1;
    int result = json_parse_string(io);

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
