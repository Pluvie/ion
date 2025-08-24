spec( json_decode_dec ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      dec number; \
      obj = &number; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { type(DEC) }; \
      allocator = spec_allocator;

  when("the json string is not a number") {
    apply(preconditions);
    *io = io(s("\"string!\""));
    json_decode_dec(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(unlikely(failure.occurred) == true);
      verify(streq(failure.message,
        "expected a number, at position 0:\n"\
        "\"string!\"\n"\
        "^\n"));
    success();
      io_close(io);
  } end();

  when("the json string is a decimal number") {
    apply(preconditions);
    *io = io(s("123.77"));
    json_decode_dec(obj, io, rfx, allocator);

    must("correctly parse until the end of the string");
      verify(io->cursor == 6);
    must("correctly set the number value");
      verify(number == 123.77);
    success();
      io_close(io);
  } end();

  when("the json string is an integer number") {
    apply(preconditions);
    *io = io(s("12345"));
    json_decode_dec(obj, io, rfx, allocator);

    must("not fail");
      verify(unlikely(failure.occurred) == false);
    must("correctly parse until the end of the string");
      verify(io->cursor == 5);
    must("correctly set the number value");
      verify(number == 12345);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
