test( memory_init, default_capacity ) {

  given("a struct memory allocator");
    struct memory allocator;


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("memory_init()");
    allocator = memory_init(capacity);


  must("initialize the allocator with #MEMORY_DEFAULT_CAP capacity");
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);


  success();
}
