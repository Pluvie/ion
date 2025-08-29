spec( json_parse_spaces ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io starts with spaces") {
      string source = s(" \t  \n  ");
      apply(preconditions);

      json(parse_spaces, io, &source);

      must("advance the cursor position to consume the spaces");
        verify(io->cursor == source.length);
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      string source = s("123    ");
      apply(preconditions);

      json(parse_spaces, io, &source);

      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io starts with spaces") {
      string source = s(" \t  \n  , \"abc\": 123");
      apply(preconditions);

      json(parse_spaces, io, &source);

      must("advance the cursor position to consume the spaces");
        verify(io->cursor == string_index(source, s(",")));
      success();
        io_close(io);
    } end();

    when("the io does not start with spaces") {
      string source = s("123    , 123");
      apply(preconditions);

      json(parse_spaces, io, &source);

      must("restore the cursor position");
        verify(io->cursor == 0);
      success();
        io_close(io);
    } end();
  } end();

  when("the io read fails") {
    /* An invalid file. Shall fail upon calling the `io_read` function. */
    struct file file = file_open(s("/wrong/path"));
    apply(preconditions);
    io_buffer_init(io, 0);

    json(parse_spaces, io, &file);

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
