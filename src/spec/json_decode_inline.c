spec( json_decode_inline ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the json valid") {
    apply(preconditions);
    //*io = io(s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } "));
    struct io json = file_read("prf/json/exe/decode.json", spec_allocator);
    io = &json;
    if (error.occurred) {
      error_print();
      return;
    }
    json_decode_inline(io);

    must("not fail");
      verify(error.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
