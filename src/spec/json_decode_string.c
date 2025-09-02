spec( json_decode_string ) {

  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(void* target);

  precondition("a valid io");
  precondition("a valid reflection");
  precondition("a valid target");
    #define preconditions \
      string name; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      io->allocator = spec_allocator; \
      rfx = &(struct reflection) { type(STRING) }; \
      target = &name;

  when("the io is direct") {
    #define io_direct_condition \
      struct io_direct* io_direct = &(io->direct);

    when("the input is not a string") {
      apply(preconditions);
      apply(io_direct_condition);
      string source = s("123");
      *io = io_open(&source);

      json_decode_string(io_direct, rfx, target);

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
      apply(preconditions);
      apply(io_direct_condition);
      string source = s("\"abc");
      *io = io_open(&source);

      json_decode_string(io_direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "unterminated string, at position 3:\n"\
          "\"abc\n"\
          "   ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string") {
      apply(preconditions);
      apply(io_direct_condition);
      string source = s("\"abc def\"");
      *io = io_open(&source);

      json_decode_string(io_direct, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io_direct->cursor - io_direct->data->pointer;
        verify(parsed_length == 9);
        verify(io_exhausted(io_direct));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc def"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string with escaped characters") {
      apply(preconditions);
      apply(io_direct_condition);
      string source = s("\"abc def\"");
      *io = io_open(&source);

      json_decode_string(io_direct, rfx, target);

      must("not fail");
        verify(failure.occurred == false);
      must("correctly parse until the end of the string");
        int parsed_length = io_direct->cursor - io_direct->data->pointer;
        verify(parsed_length == 9);
        verify(io_exhausted(io_direct));
      must("store the parsed string in the reflection target, without quotes");
        verify(eq(name, "abc def"));
      success();
        io_close(io);
    } end();
  } end();

  #undef io_direct_condition

  #undef preconditions
}
