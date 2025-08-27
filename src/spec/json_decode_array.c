spec( json_decode_array ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      struct squadmate squad[3] = { 0 }; \
      obj = &squad; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { \
        type(ARRAY, struct squadmate [3]), of({ \
          type(STRUCT, struct squadmate), fields({ \
            { field(name, STRING, struct squadmate) }, \
            { field(class, ENUM, struct squadmate) }, \
            { field(health, INT, struct squadmate) }, \
            { field(shields, INT, struct squadmate) }, \
          }) \
        }) \
      }; \
      allocator = spec_allocator;

  when("the json array is not an array") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    json_decode_array(obj, io, rfx, allocator);

    must("fail with a specific error");
      verify(failure.occurred == true);
      verify(streq(failure.message,
        "expected array begin '[', at position 4:\n"\
        "   123 \\  \n"\
        "   ^\n"));
    success();
      io_close(io);
  } end();

  when("the json array is an empty array") {
    apply(preconditions);
    *io = io(s("   \n [ \n\t ] "));
    json_decode_array(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the array");
      verify(io->cursor == 11);
    must("not add any element");
      verify(byte_eq(&squad, (struct squadmate [3]) { 0 }, sizeof(struct squadmate [3])));
    success();
      io_close(io);
  } end();

  when("the json array has some elements") {
    apply(preconditions);
    *io = io(s("   \n [ \n"\
      "{ \"name\": \"Jane Shepard\", \"class\": 0 }, \n"\
      "{ \"name\": \"Garrus Vakarian\", \"class\": 2 } \n"\
      "] "));
    json_decode_array(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the object");
      verify(io->cursor == 93);
    must("add the corresponding elements");
      verify(streq(squad[0].name, "Jane Shepard"));
      verify(squad[0].class == SOLDIER);
      verify(streq(squad[1].name, "Garrus Vakarian"));
      verify(squad[1].class == INFILTRATOR);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
