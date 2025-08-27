spec( json_decode_map ) {

  argument(void* obj);
  argument(struct io* io);
  argument(struct reflection* rfx);
  argument(struct memory* allocator);

  precondition("a valid object");
  precondition("a valid io");
  precondition("a valid reflection for the object");
  precondition("a valid memory allocator");
    #define preconditions \
      map<string, struct squadmate> squad = { 0 }; \
      obj = &squad; \
      io = memory_alloc_zero(spec_allocator, sizeof(struct io)); \
      rfx = &(struct reflection) { \
        type(MAP), container(map<string, struct squadmate>_), of({ \
          type(STRING), of({ \
            type(STRUCT, struct squadmate), fields({ \
              { field(name, STRING, struct squadmate) }, \
              { field(class, ENUM, struct squadmate) }, \
              { field(health, INT, struct squadmate) }, \
              { field(shields, INT, struct squadmate) }, \
            }) \
          }) \
        }) \
      }; \
      allocator = spec_allocator;

  when("the json array is not an array") {
    apply(preconditions);
    *io = io(s("   123 \n  "));
    json_decode_map(obj, io, rfx, allocator);

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
    json_decode_map(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the array");
      verify(io->cursor == 11);
    must("not add any element");
      verify(squad.length == 0);
    success();
      io_close(io);
  } end();

  when("the json array has some elements") {
    apply(preconditions);
    *io = io(s("   \n [ \n"\
      "[ \"Commander\", { \"name\": \"Jane Shepard\", \"class\": 0 } ], \n"\
      "[ \"Archangel\", { \"name\": \"Garrus Vakarian\", \"class\": 2 } ] \n"\
      "] "));
    json_decode_map(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the array");
      verify(io->cursor == 127);
    must("add the corresponding elements");
      verify(squad.length == 2);
      struct squadmate* shepard = map_get(&squad, s("Commander"));
      struct squadmate* garrus = map_get(&squad, s("Archangel"));
      verify(streq(shepard->name, s("Jane Shepard")));
      verify(shepard->class == SOLDIER);
      verify(streq(garrus->name, s("Garrus Vakarian")));
      verify(garrus->class == INFILTRATOR);
    success();
      io_close(io);
  } end();

  when("the json array has some elements, some of which duplicated") {
    apply(preconditions);
    *io = io(s("   \n [ \n"\
      "[ \"Commander\", { \"name\": \"Jane Shepard\", \"class\": 0 } ], \n"\
      "[ \"Commander\", { \"name\": \"Jane Shepard\", \"class\": 0 } ], \n"\
      "[ \"Archangel\", { \"name\": \"Garrus Vakarian\", \"class\": 2 } ] \n"\
      "] "));
    json_decode_map(obj, io, rfx, allocator);

    must("not fail");
      verify(failure.occurred == false);
    must("correctly parse until the end of the array");
      verify(io->cursor == 185);
    must("add the corresponding elements, removing duplicates from the set");
      verify(squad.length == 2);
      struct squadmate* shepard = map_get(&squad, s("Commander"));
      struct squadmate* garrus = map_get(&squad, s("Archangel"));
      verify(streq(shepard->name, s("Jane Shepard")));
      verify(shepard->class == SOLDIER);
      verify(streq(garrus->name, s("Garrus Vakarian")));
      verify(garrus->class == INFILTRATOR);
    success();
      io_close(io);
  } end();

  #undef preconditions
}
