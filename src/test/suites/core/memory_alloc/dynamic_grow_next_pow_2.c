test( memory_alloc, dynamic_grow_next_pow_2 ) {

  given("a memory allocator");
    memory allocator = memory_init(MEMORY_DEFAULT_CAPACITY);
    u64 initial_capacity = allocator.capacity;


  when("there is some memory already allocated");
    u64 amount = 40;
    void* allocation = memory_alloc(&allocator, amount);
    verify(allocation != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);


  when("the next amount to allocate is greater than the initial capacity");
    amount = 1000;


  calling("memory_alloc()");
    allocation = memory_alloc(&allocator, amount);


  must("grow the allocator to the next power of 2 of the amount plus the initial "\
       "capacity, and allocate the memory");
    verify(allocation != NULL);
    verify(allocator.capacity == next_pow2(amount + initial_capacity));
    verify(allocator.position == 40 + 1000);


  success();
    memory_release(&allocator);
}
