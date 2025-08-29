spec( json_parse_string ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io starts with string") {
      string source = s("\" \t  \n  \"");
      apply(preconditions);

      string result;
      json(parse_string, io, &source, &result);

      must("point the result to the parsed string, including quotes");
        verify(eq(result, "\" \t  \n  \""));
      must("advance the io cursor to consume the string");
        verify(io->cursor == result.length);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      string source = s("123    ");
      apply(preconditions);

      string result;
      json(parse_string, io, &source, &result);

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
      string source = s("\"abc\": 123 ,  \t  \n");
      apply(preconditions);

      string result;
      json(parse_string, io, &source, &result);

      must("point the result to the parsed string, including quotes");
        verify(eq(result, "\"abc\""));
      must("advance the io cursor to consume the string");
        verify(io->cursor == result.length);
      success();
        io_close(io);
    } end();

    when("the io does not start with string") {
      string source = s("123    , 123");
      apply(preconditions);

      string result;
      json(parse_string, io, &source, &result);

      must("point the result to an empty string");
        verify(eq(result, NULL));
      must("reset the io cursor");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the io has reached the end of input") {
    string source = s("\"123\"    ");
    apply(preconditions);

    io->cursor = 9;
    string result;
    json(parse_string, io, &source, &result);

    must("point the result to an empty string");
      verify(eq(result, NULL));
    must("reset the io cursor");
      verify(io->cursor == 9);
    success();
      io_close(io);
  } end();

  when("the io read fails") {
    /* An invalid file. Shall fail upon calling the `io_read` function. */
    struct file file = file_open(s("/wrong/path"));
    apply(preconditions);
    io_buffer_init(io, 0);

    string result;
    json(parse_string, io, &file, &result);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is("file open error: No such file or directory"));
    must("point the result to an empty string");
      verify(eq(result, NULL));
    must("restore the io cursor to the original position");
      verify(io->cursor == 0);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
