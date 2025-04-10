test( buffer_alloc, dynamic_grow_next_pow_2 ) {

  given("a buffer allocator");
    buffer allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);
    u64 initial_capacity = allocator.capacity;


  when("there is some buffer already allocated");
    u64 amount = 40;
    u64 position = buffer_alloc(&allocator, amount);
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);


  when("the next amount to allocate is greater than the initial capacity");
    amount = 1000;


  calling("buffer_alloc()");
    position = buffer_alloc(&allocator, amount);


  must("grow the allocator to the next power of 2 of the amount plus the initial "\
       "capacity, and allocate the buffer");
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == next_pow2(amount + initial_capacity));
    verify(allocator.position == 40 + 1000);


  success();
    buffer_release(&allocator);
}
