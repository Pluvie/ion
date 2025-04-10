test( buffer_alloc, data_consistency ) {

  given("a buffer allocator");
    buffer allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);
    u64 initial_capacity = allocator.capacity;


  when("there is some buffer already allocated");
    u64 amount = 40;
    u64 position = buffer_alloc(&allocator, amount);
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);
    memset(buffer_data(&allocator, position), 7, amount);
    byte* data = allocator.data;


  when("the next amount to allocate produces a growth in capacity");
    amount = 1000;


  calling("buffer_alloc()");
    position = buffer_alloc(&allocator, amount);


  must("grow the allocator and preserve the data");
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == next_pow2(amount + initial_capacity));
    verify(allocator.position == 40 + 1000);
    verify(allocator.data != data);
    for (u64 i = 0; i < 40; i++)
      verify(allocator.data[i] == 7);


  success();
    buffer_release(&allocator);
}
