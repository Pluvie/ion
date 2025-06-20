test( memory_alloc, first_allocation_capacity ) {

  given("an initialized memory allocator with a capacity");
    memory allocator = memory_init(64);


  given("an integer amount of data lesser than the memory capacity");
    int amount = 32;


  calling("memory_alloc()");
    void* result = memory_alloc(&allocator, amount);


  must("allocate and leave unchanged the capacity");
    verify(result != NULL);
    verify(result == allocator.data);
    verify(allocator.data != NULL);
    verify(allocator.capacity == 64);
    verify(allocator.position == amount);
    verify(allocator.allocations.count == 1);
    verify(allocator.allocations.size == 32);
    verify(allocator.regions.addresses == NULL);
    verify(allocator.regions.capacity == 0);
    verify(allocator.regions.count == 0);


  success();
    memory_release(&allocator);
}
