spec( json_parse_number ) {

  argument(struct io* io);

  precondition("valid io");
    #define preconditions \
      io = memory_alloc(spec_allocator, sizeof(struct io));

  when("the parsing reaches the end of input") {
    when("the io contains a positive number") {
      when("the number is integer") {
        apply(preconditions);
        *io = io(s("123"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 3);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is decimal") {
        apply(preconditions);
        *io = io(s("123.77"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 6);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential integer") {
        apply(preconditions);
        *io = io(s("123e03"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 6);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential decimal") {
        apply(preconditions);
        *io = io(s("123.77e03"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 9);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();
    } end();

    when("the io contains a negative number") {
      when("the number is integer") {
        apply(preconditions);
        *io = io(s("-123"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 4);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is decimal") {
        apply(preconditions);
        *io = io(s("-123.77"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 7);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential integer") {
        apply(preconditions);
        *io = io(s("-123e+04"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 8);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential decimal") {
        apply(preconditions);
        *io = io(s("-123.77e-3"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 10);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();
    } end();
  } end();

  when("the parsing does not reach the end of input") {
    when("the io contains a positive number") {
      when("the number is integer") {
        apply(preconditions);
        *io = io(s("123, 123"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 3);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is decimal") {
        apply(preconditions);
        *io = io(s("123.77]"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 6);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential integer") {
        apply(preconditions);
        *io = io(s("123e03,\"abc\""));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 6);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential decimal") {
        apply(preconditions);
        *io = io(s("123.77e-03}"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 10);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();
    } end();

    when("the io contains a negative number") {
      when("the number is integer") {
        apply(preconditions);
        *io = io(s("-123,0"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 4);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is decimal") {
        apply(preconditions);
        *io = io(s("-123.77}"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 7);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential integer") {
        apply(preconditions);
        *io = io(s("-123e+04]"));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 8);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();

      when("the number is exponential decimal") {
        apply(preconditions);
        *io = io(s("-123.77e-3,\"abc\""));
        int result = json_parse_number(io);

        must("return the length of the number");
          verify(result == 10);
        must("restore the cursor position");
          verify(io->cursor == 0);
        success();
          io_close(io);
      } end();
    } end();
  } end();

  when("the io read fails") {
    apply(preconditions);
    /* An invalid io channel. Shall fail upon calling the `io_read` function. */
    io->channel = -1;
    int result = json_parse_number(io);

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
