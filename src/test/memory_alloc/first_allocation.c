test( memory_alloc, first_allocation ) {

  given("an initialized memory allocator with zero capacity");
    memory allocator = memory_init(0);


  given("an integer amount of data");
    int amount = 64;


  calling("memory_alloc()");
    void* result = memory_alloc(&allocator, amount);


  must("allocate and set the capacity equal to the amount");
    verify(result != NULL);
    verify(result == allocator.data);
    verify(allocator.data != NULL);
    verify(allocator.capacity == amount);
    verify(allocator.position == amount);
    verify(allocator.allocations.count == 1);
    verify(allocator.allocations.size == 64);
    verify(allocator.regions.addresses == NULL);
    verify(allocator.regions.capacity == 0);
    verify(allocator.regions.count == 0);


  success();
    memory_release(&allocator);
}
