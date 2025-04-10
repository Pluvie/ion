test( memory_alloc, increment_position ) {

  given("a memory allocator");
    memory allocator = memory_init(MEMORY_DEFAULT_CAPACITY);


  when("there are no allocations yet");
    verify(allocator.allocations == 0);


  when("there is enough space to allocate");
    u64 amount = 24;


  calling("memory_alloc()");
    void* allocation = memory_alloc(&allocator, amount);


  must("allocate memory and increment the allocator position");
    verify(allocator.position == amount);
    verify(allocator.data != NULL);
    verify(allocation != NULL);


  success();
    memory_release(&allocator);
}
