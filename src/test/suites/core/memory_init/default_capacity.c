test( memory_init, default_capacity ) {

  given("a memory allocator");
    memory allocator;


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("memory_init()");
    allocator = memory_init(capacity);


  must("initialize the allocator with #MEMORY_DEFAULT_CAPACITY capacity");
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);


  success();
}
