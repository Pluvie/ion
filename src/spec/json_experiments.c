spec( json_experiments ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("json_parse_string") {
    when("a valid json string") {
      apply(preconditions);
      string str = s("\"Jane Shepard\"");

      string result;
      json(parse_string, io, &str, &result);

      must("point the result to the parsed string, including quotes");
        verify(eq(result, "\"Jane Shepard\""));
      must("advance the io cursor to consume the input");
        verify(io->cursor == str.length);

      success();
        io_close(io);
    } end();

    when("a invalid json string") {
      apply(preconditions);
      string str = s("123");

      string result;
      json(parse_string, io, &str, &result);

      must("point the result to an empty string");
        verify(eq(result, NULL));
      must("reset the io cursor");
        verify(io->cursor == 0);

      success();
        io_close(io);
    } end();
  } end();

  when("json_decode") {
    apply(preconditions);
    string str = s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } ");
    //struct io json = file_read("prf/json/exe/decode.json", spec_allocator);
    //io = &json;
    json(decode_direct, io, &str);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);

    success();
      io_close(io);
  } end();

  #undef preconditions
}
