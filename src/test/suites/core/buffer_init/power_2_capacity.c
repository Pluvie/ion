test( buffer_init, power_2_capacity ) {

  given("a buffer allocator");
    buffer allocator;


  when("providing a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("buffer_init()");
    allocator = buffer_init(capacity);


  must("initialize the allocator with the next power of 2 capacity");
    verify(allocator.capacity == 128);


  success();
}
