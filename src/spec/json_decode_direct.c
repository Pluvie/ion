spec( json_decode_direct ) {

  argument(struct io* io);

  precondition("a valid io");
    #define preconditions \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io));

  when("the json valid") {
    apply(preconditions);
    *io = io(s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } "));
    //struct io json = file_read("prf/json/exe/decode.json", spec_allocator);
    //io = &json;
    json_decode_direct(io);

    must("not fail");
      verify(unlikely(failure.occurred) == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
