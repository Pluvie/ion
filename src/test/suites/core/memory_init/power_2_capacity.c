test( memory_init, power_2_capacity ) {

  given("a struct memory allocator");
    struct memory allocator;


  when("providing a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("memory_init()");
    allocator = memory_init(capacity);


  must("initialize the allocator with the next power of 2 capacity");
    verify(allocator.capacity == 128);


  success();
}
