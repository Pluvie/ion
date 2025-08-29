spec( json_parse_string ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      *io = io_init_with_buffer(NULL, NULL);

  when("the parsing reaches the end of input") {
    when("the io starts with string") {
      apply(preconditions);
      string source = s("\" \t  \n  \"");
      string result; json(parse_string, io, &source, &result);

      must("point the result to the parsed string, including quotes");
        verify(eq(result, "\" \t  \n  \""));
      must("advance the io cursor to consume the input");
        verify(io->cursor == result.length);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      apply(preconditions);
      string source = s("123    ");
      string result; json(parse_string, io, &source, &result);

      must("point the result to an empty string");
        verify(eq(result, NULL));
      must("reset the io cursor");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io starts with string") {
      apply(preconditions);
      string source = s("\"abc\": 123 ,  \t  \n");
      string result; json(parse_string, io, &source, &result);

      must("point the result to the parsed string, including quotes");
        verify(eq(result, "\"abc\""));
      must("advance the io cursor to consume the input");
        verify(io->cursor == result.length);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      apply(preconditions);
      string source = s("123    , 123");
      string result; json(parse_string, io, &source, &result);

      must("point the result to an empty string");
        verify(eq(result, NULL));
      must("reset the io cursor");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the io has reached the end of input") {
    apply(preconditions);
    string source = s("\"123\"    ");
    io->cursor = 9;
    string result; json(parse_string, io, &source, &result);

    must("point the result to an empty string");
      verify(eq(result, NULL));
    must("reset the io cursor");
      verify(io->cursor == 9);
    success();
      io_close(io);
  } end();

  when("the io read fails") {
    apply(preconditions);
    /* An invalid file. Shall fail upon calling the `io_read` function. */
    struct file file = { .descriptor = -1 };
    string result; json(parse_string, io, &file, &result);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("file read error: Bad file descriptor"));
    must("point the result to an empty string");
      verify(eq(result, NULL));
    must("reset the io cursor");
      verify(io->cursor == 0);
    success();
      io_close(io);

  } end();

  #undef preconditions
}
