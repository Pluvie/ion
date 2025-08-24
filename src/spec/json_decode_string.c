spec( json_decode_string ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      string name; \
      obj = &name; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { type(STRING) }; \
      allocator = spec_allocator;

  when("the json string is not a string") {
    apply(preconditions);
    *io = io(s("123"));
    json_decode_string(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(unlikely(failure.occurred) == true);
      verify(streq(failure.message,
        "expected a string, at position 0:\n"\
        "123\n"\
        "^\n"));
    success();
      io_close(io);
  } end();

  when("the json string is an empty string") {
    apply(preconditions);
    *io = io(s("\"\""));
    json_decode_string(obj, io, rfx, allocator);

    must("not fail");
      verify(unlikely(failure.occurred) == false);
    must("correctly parse until the end of the string");
      verify(io->cursor == 2);
    must("correctly set the string value");
      verify(streq(name, ""));
    success();
      io_close(io);
  } end();

  when("the json string is not empty") {
    apply(preconditions);
    *io = io(s("\"abc\""));
    json_decode_string(obj, io, rfx, allocator);

    must("not fail");
      verify(unlikely(failure.occurred) == false);
    must("correctly parse until the end of the string");
      verify(io->cursor == 5);
    must("correctly set the string value");
      verify(streq(name, "abc"));
    success();
      io_close(io);
  } end();

  #undef preconditions
}
