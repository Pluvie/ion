spec( json_decode_bool ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      bool boolean; \
      obj = &boolean; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { type(BOOL) }; \
      allocator = spec_allocator;

  when("the json value is not a boolean") {
    apply(preconditions);
    *io = io(s("\"string!\""));
    json_decode_bool(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(error.occurred == true);
      verify(streq(error.message,
        "expected a boolean, at position 0:\n"\
        "\"string!\"\n"\
        "^\n"));
    success();
      io_close(io);
  } end();

  when("the json value is a boolean") {
    when("the json value is true") {
      apply(preconditions);
      *io = io(s("true"));
      json_decode_bool(obj, io, rfx, allocator);

      must("not fail");
        verify(error.occurred == false);
      must("correctly parse until the end of the value");
        verify(io->cursor == 4);
      must("correctly set the boolean value");
        verify(boolean == true);
      success();
        io_close(io);
    } end();

    when("the json value is false") {
      apply(preconditions);
      *io = io(s("false"));
      json_decode_bool(obj, io, rfx, allocator);

      must("not fail");
        verify(error.occurred == false);
      must("correctly parse until the end of the value");
        verify(io->cursor == 5);
      must("correctly set the boolean value");
        verify(boolean == false);
      success();
        io_close(io);
    } end();
  } end();

  #undef preconditions
}
