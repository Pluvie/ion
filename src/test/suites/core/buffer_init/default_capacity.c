test( buffer_init, default_capacity ) {

  given("a struct buffer allocator");
    struct buffer allocator;


  when("providing a capacity inferior to the default");
    u64 capacity = 3;


  calling("buffer_init()");
    allocator = buffer_init(capacity);


  must("initialize the allocator with #MEMORY_DEFAULT_CAP capacity");
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);


  success();
}
