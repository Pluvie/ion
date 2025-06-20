test( memory_init, initialize_empty ) {

  given("a memory allocator");
    memory allocator;


  calling("memory_init()");
    allocator = memory_init(1024);


  must("initialize the allocator but not allocate any memory yet");
    verify(allocator.data == NULL);
    verify(allocator.capacity == 1024);
    verify(allocator.position == 0);
    verify(allocator.regions.addresses == NULL);
    verify(allocator.regions.capacity == 0);
    verify(allocator.regions.count == 0);
    verify(allocator.allocations.count == 0);
    verify(allocator.allocations.size == 0);


  success();
}
