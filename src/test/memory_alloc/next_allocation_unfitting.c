test( memory_alloc, next_allocation_unfitting ) {

  given("an allocator with some data already allocated");
    memory allocator = memory_init(128);
    memory_alloc(&allocator, 96);
    void* initial_allocator_data = allocator.data;


  given("an integer amount of data that does not fits into the capacity");
    int amount = 64;


  calling("memory_alloc()");
    void* result = memory_alloc(&allocator, amount);


  must("allocate, double the capacity and create a region");
    verify(result != NULL);
    verify(result == allocator.data);
    verify(allocator.data != NULL);
    verify(allocator.capacity == 128 * 2);
    verify(allocator.position == amount);
    verify(allocator.allocations.count == 2);
    verify(allocator.allocations.size == 96 + amount);
    verify(allocator.regions.addresses != NULL);
    verify(allocator.regions.addresses[0] == initial_allocator_data);
    verify(allocator.regions.capacity == 8);
    verify(allocator.regions.count == 1);


  success();
    memory_release(&allocator);
}
