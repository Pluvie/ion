test( buffer_alloc, address_unreliability ) {

  given("a buffer allocator");
    buffer allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);
    u64 initial_capacity = allocator.capacity;


  when("there is some buffer already allocated");
    u64 amount = 40;
    u64 position = buffer_alloc(&allocator, amount);
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);
    void* data = allocator.data;


  when("the next amount to allocate produces a growth in capacity");
    amount = 1000;


  calling("buffer_alloc()");
    position = buffer_alloc(&allocator, amount);


  must("grow the allocator and change the data address to with the buffer points");
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == next_pow2(amount + initial_capacity));
    verify(allocator.position == 40 + 1000);
    verify(allocator.data != data);


  success();
    buffer_release(&allocator);
}
