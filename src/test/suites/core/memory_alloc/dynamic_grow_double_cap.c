test( memory_alloc, dynamic_grow_double_cap ) {

  given("a memory allocator");
    memory allocator = memory_init(MEMORY_DEFAULT_CAPACITY);
    u64 initial_capacity = allocator.capacity;


  when("there is some memory already allocated");
    u64 amount = 40;
    void* allocation = memory_alloc(&allocator, amount);
    verify(allocation != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);


  when("the next amount to allocate lesser or equal than the initial capacity");
    amount = 64;


  calling("memory_alloc()");
    allocation = memory_alloc(&allocator, amount);


  must("grow the allocator to double the initial capacity and allocate the memory");
    verify(allocation != NULL);
    verify(allocator.capacity == 2 * initial_capacity);
    verify(allocator.position == 40 + 64);


  success();
    memory_release(&allocator);
}
