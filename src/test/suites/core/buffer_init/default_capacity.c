test( buffer_init, default_capacity ) {

  given("a buffer allocator");
    buffer allocator;


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("buffer_init()");
    allocator = buffer_init(capacity);


  must("initialize the allocator with #MEMORY_DEFAULT_CAPACITY capacity");
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);


  success();
}
