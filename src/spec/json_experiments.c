spec( json_experiments ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("json_parse_string") {
    when("a valid json string") {
      apply(preconditions);
      string str = s("\"Jane Shepard\"");
      *io = io(&str, NULL, NULL);

      bool result = json_parse_string_direct(io, &str);

      must("return true");
        verify(result == true);
      must("advance the io cursor to consume the input");
        verify(io->cursor == str.length);

      success();
    } end();

    when("a invalid json string") {
      apply(preconditions);
      string str = s("123");
      *io = io(&str, NULL, NULL);

      bool result = json_parse_string_direct(io, &str);

      must("return false");
        verify(result == false);
      must("reset the io cursor");
        verify(io->cursor == 0);

      success();
    } end();
  } end();

  when("json_decode") {
    apply(preconditions);
    string str = s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } ");
    *io = io(&str, NULL, NULL);
    //struct io json = file_read("prf/json/exe/decode.json", spec_allocator);
    //io = &json;
    json_decode_direct(io, &str);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);

    success();
  } end();

  #undef preconditions
}
