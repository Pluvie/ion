test( memory_alloc, regions_saturation ) {

  given("an allocator with some data already allocated");
    memory allocator = memory_init(2);


  when("the allocator regions are at capacity");
    memory_alloc(&allocator, 2);
    memory_alloc(&allocator, 4);
    memory_alloc(&allocator, 8);
    memory_alloc(&allocator, 16);
    memory_alloc(&allocator, 32);
    memory_alloc(&allocator, 64);
    memory_alloc(&allocator, 128);
    memory_alloc(&allocator, 256);
    memory_alloc(&allocator, 512);
    verify(allocator.regions.capacity == 8);
    verify(allocator.regions.count == 8);


  given("an integer amount of data");
    int amount = 1024;


  calling("memory_alloc()");
    void* result = memory_alloc(&allocator, amount);


  must("allocate and increase the regions capacity");
    verify(result != NULL);
    verify(result == allocator.data);
    verify(allocator.data != NULL);
    verify(allocator.capacity == 2048);
    verify(allocator.position == amount);
    verify(allocator.allocations.count == 10);
    verify(allocator.allocations.size == 2046);
    verify(allocator.regions.addresses != NULL);
    verify(allocator.regions.capacity == 16);
    verify(allocator.regions.count == 9);


  success();
    memory_release(&allocator);
}
