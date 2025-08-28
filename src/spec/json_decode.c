spec( json_decode ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      struct squadmate shepard; \
      obj = &shepard; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { \
        type(STRUCT, struct squadmate), fields({ \
          { field(name, STRING, struct squadmate) }, \
          { field(class, ENUM, struct squadmate) }, \
          { field(health, INT, struct squadmate) }, \
          { field(shields, INT, struct squadmate) }, \
        }) \
      }; \
      allocator = spec_allocator;

  when("the json is null") {
    apply(preconditions);
    *io = io(s("   null \n  "));
    json_decode(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("zero out the object");
      verify(byte_eq(obj, &(struct squadmate) { 0 }, sizeof(struct squadmate)));
    must("exhaust the io");
      verify(io->cursor == io->length);
    success();
      io_close(io);
  } end();

  when("the reflection is NULL") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    rfx = NULL;
    json_decode(obj, io, rfx, allocator);

    must("decode and discard the value");
      verify(io->cursor == 6);
    success();
      io_close(io);
  } end();

  when("the json is an incompatible value") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    json_decode(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(failure_is(
        "expected object begin '{', at position 4:\n"\
        "   123 \\  \n"\
        "   ^\n"));
    success();
      io_close(io);
  } end();

  when("the json is a compatible value") {
    apply(preconditions);
    *io = io(s("   \n { \"name\": \"Jane Shepard\", \"class\": 0 } "));
    json_decode(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 43);
    must("set the correct value to the corresponding fields");
      verify(eq(shepard.name, "Jane Shepard"));
      verify(shepard.class == SOLDIER);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
