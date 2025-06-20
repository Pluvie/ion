test( memory_init, negative_capacity ) {

  given("a memory allocator");
    memory allocator;


  when("the provided capacity is negative");
    int capacity = -3;


  calling("memory_init()");
    allocator = memory_init(capacity);


  must("initialize the allocator with capacity equal to 0");
    verify(allocator.capacity == 0);


  success();
}
