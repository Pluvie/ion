spec( json_decode_dec ) {

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
    when("the input is not a number") {
      string source = s("abc");
      apply(preconditions);

      json_decode_dec(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "expected a number, at position 0:\n"\
          "abc\n"\
          "^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an decimal json number without fractional part") {
      string source = s("123.");
      apply(preconditions);

      json_decode_dec(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "invalid number, at position 4:\n"\
          "123.\n"\
          "   ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is an decimal json number without exponent part") {
      string source = s("123.77e");
      apply(preconditions);

      json_decode_dec(io->direct, rfx, target);

      must("fail with a specific error");
        verify(failure.occurred == true);
        verify(failure_is(
          "invalid number, at position 6:\n"\
          "123.77e\n"\
          "      ^\n"));
      success();
        io_close(io);
    } end();

    when("the input is a valid json string") {
      string source = s("\"abc def\"");
      apply(preconditions);

      json_decode_dec(io->direct, rfx, target);

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

      json_decode_dec(io->direct, rfx, target);

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

  #undef preconditions
}
