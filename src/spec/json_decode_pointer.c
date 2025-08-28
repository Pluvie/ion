spec( json_decode_pointer ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      struct squadmate* shepard = NULL; \
      obj = &shepard; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { \
        type(POINTER), of({ \
          type(STRUCT, struct squadmate), fields({ \
            { field(name, STRING, struct squadmate) }, \
            { field(class, ENUM, struct squadmate) }, \
            { field(health, INT, struct squadmate) }, \
            { field(shields, INT, struct squadmate) }, \
          }) \
        }) \
      }; \
      allocator = spec_allocator;

  when("the json object is not an object") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    json_decode_pointer(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is(
        "expected object begin '{', at position 4:\n"\
        "   123 \\  \n"\
        "   ^\n"));
    success();
      io_close(io);
  } end();

  when("the json object is an empty object") {
    apply(preconditions);
    *io = io(s("   \n { \n\t } "));
    json_decode_pointer(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 11);
    must("not set any field");
      verify(eq(shepard, &(struct squadmate) { 0 }));
    success();
      io_close(io);
  } end();

  when("the json object has matching fields") {
    apply(preconditions);
    *io = io(s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } "));
    json_decode_pointer(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);
    must("set the correct value to the corresponding fields");
      verify(eq(shepard->name, "Jane Shepard"));
      verify(shepard->class == SOLDIER);
    success();
      io_close(io);
  } end();

  when("the json object has no matching fields") {
    apply(preconditions);
    *io = io(s("   \n { \"_name\": \"Jane Shepard\", \"_class\": 0 } "));
    json_decode_pointer(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 45);
    must("not set any field");
      verify(eq(shepard, &(struct squadmate) { 0 }));
    success();
      io_close(io);
  } end();

  #undef preconditions
}
