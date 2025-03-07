test( reflection_initialize, link_target ) {

  given("a type");
    struct example {
      u64 value_u64;
      d64 value_d64;
    };


  when("it has an associated reflection");
    struct reflection rfx = {
      type(STRUCT, struct example), fields({
        { field(value_u64, U64, struct example) },
        { field(value_d64, D64, struct example) },
      }),
    };


  when("exists an object of that type");
    struct example object;


  when("an allocator is initialized");
    struct memory allocator = memory_init(0);


  calling("reflection_initialize()");
    reflection_initialize(&rfx, &object, &allocator);


  must("link the reflection to the object");
    verify(rfx.target = &object);
    verify(rfx.allocator = &allocator);


  success();
}
