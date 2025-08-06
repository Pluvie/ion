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
      verify(error.occurred == false);
    must("zero out the object");
      verify(memeq(obj, &(struct squadmate) { 0 }, sizeof(struct squadmate)));
    must("exhaust the io");
      verify(io->cursor == io->length);
    success();
      io_close(io);
  } end();

  when("the json is an incompatible value") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    json_decode(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(error.occurred == true);
      verify(streq(error.message, "expected object begin '{'"));
    success();
      io_close(io);
  } end();

  #undef preconditions
}
