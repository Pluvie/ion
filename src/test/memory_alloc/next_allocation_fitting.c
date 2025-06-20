test( memory_alloc, next_allocation_fitting ) {

  given("an allocator with some data already allocated");
    memory allocator = memory_init(128);
    memory_alloc(&allocator, 64);


  given("an integer amount of data that fits into the capacity");
    int amount = 32;


  calling("memory_alloc()");
    void* result = memory_alloc(&allocator, amount);


  must("allocate and leave unchanged the capacity");
    verify(result != NULL);
    verify(result == allocator.data + 64);
    verify(allocator.data != NULL);
    verify(allocator.capacity == 128);
    verify(allocator.position == 64 + amount);
    verify(allocator.allocations.count == 2);
    verify(allocator.allocations.size == 64 + amount);
    verify(allocator.regions.addresses == NULL);
    verify(allocator.regions.capacity == 0);
    verify(allocator.regions.count == 0);


  success();
    memory_release(&allocator);
}
