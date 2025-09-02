spec( json_decode_string ) {

  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(void* target);

  precondition("a valid io");
  precondition("a valid reflection");
  precondition("a valid target");
    #define preconditions \
      string name; target = &name; \
      rfx = &(struct reflection) { type(STRING) }; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      *io = io_open(&source, rfx, spec_allocator);

  when("the io is direct") {
    when("the input is not a string") {
      string source = s("123");
      apply(preconditions);

      json_decode_string(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "expected a string, at position 0:\n"\
          "123\n"\
          "^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an unterminated json string") {
      string source = s("\"abc");
      apply(preconditions);

      json_decode_string(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "unterminated string, at position 3:\n"\
          "\"abc\n"\
          "   ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an invalid json string") {
      string source = s("\"abc\ndef\"");
      apply(preconditions);

      json_decode_string(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "invalid string, at position 4:\n"\
          "\"abc\\def\"\n"\
          "    ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string") {
      string source = s("\"abc def\"");
      apply(preconditions);

      json_decode_string(io->direct, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io->direct->cursor - io->direct->data->pointer;
        verify(parsed_length == 9);
        verify(io_exhausted(io->direct));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc def"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string with escaped characters") {
      string source = s("\"abc def\"");
      apply(preconditions);

      json_decode_string(io->direct, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io->direct->cursor - io->direct->data->pointer;
        verify(parsed_length == 9);
        verify(io_exhausted(io->direct));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc def"));
      success();
        io_close(io);
    } end();
  } end();


  when("the io is buffered") {
    when("the input is not a string") {
      struct pipe source = pipe_open();
      apply(preconditions);
      pipe_write(&source, slice("123"));

      json_decode_string(io->buffered, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "expected a string, at position 0:\n"\
          "123\n"\
          "^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an unterminated json string") {
      struct pipe source = pipe_open();
      apply(preconditions);
      pipe_write(&source, slice("\"abc"));

      json_decode_string(io->buffered, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "unterminated string, at position 3:\n"\
          "\"abc\n"\
          "   ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an invalid json string") {
      struct pipe source = pipe_open();
      apply(preconditions);
      pipe_write(&source, slice("\"abc\ndef\""));

      json_decode_string(io->buffered, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "invalid string, at position 4:\n"\
          "\"abc\\def\"\n"\
          "    ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string") {
      struct pipe source = pipe_open();
      apply(preconditions);
      pipe_write(&source, slice("\"abc def\""));

      json_decode_string(io->buffered, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io->buffered->cursor - io->buffered->buffer.data;
        verify(parsed_length == 9);
        verify(io_exhausted(io->buffered));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc def"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string with escaped characters") {
      struct pipe source = pipe_open();
      apply(preconditions);
      pipe_write(&source, slice("\"abc\\ndef\""));

      json_decode_string(io->buffered, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io->buffered->cursor - (char*) io->buffered->buffer.data;
        verify(parsed_length == 10);
        verify(io_exhausted(io->buffered));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc\ndef"));
      success();
        io_close(io);
    } end();
  } end();

  #undef preconditions
}
