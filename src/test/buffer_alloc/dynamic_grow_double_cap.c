test( buffer_alloc, dynamic_grow_double_cap ) {

  given("a struct buffer allocator");
    struct buffer allocator = buffer_init(MEMORY_DEFAULT_CAP);
    u64 initial_capacity = allocator.capacity;


  when("there is some buffer already allocated");
    u64 amount = 40;
    u64 position = buffer_alloc(&allocator, amount);
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);


  when("the next amount to allocate lesser or equal than the initial capacity");
    amount = 64;


  calling("buffer_alloc()");
    position = buffer_alloc(&allocator, amount);


  must("grow the allocator to double the initial capacity and allocate the buffer");
    verify(buffer_data(&allocator, position) != NULL);
    verify(allocator.capacity == 2 * initial_capacity);
    verify(allocator.position == 40 + 64);


  success();
    buffer_release(&allocator);
}
