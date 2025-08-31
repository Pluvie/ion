spec( json_experiments ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("json_decode") {
    apply(preconditions);
    string str = s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } ");
    struct squadmate shepard = { 0 };
    struct io json = io_open(&str);
    //struct io json = file_read("prf/json/exe/decode.json", spec_allocator);
    //io = &json;
    json_decode(&json, &shepard);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(*io->direct.cursor == '}');

    success();
      io_close(io);
  } end();

  #undef preconditions
}
