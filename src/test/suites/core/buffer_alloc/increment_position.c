test( buffer_alloc, increment_position ) {

  given("a buffer allocator");
    buffer allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);


  when("there are no allocations yet");
    verify(allocator.data == NULL);


  when("there is enough space to allocate");
    u64 amount = 24;


  calling("buffer_alloc()");
    u64 position = buffer_alloc(&allocator, amount);


  must("allocate buffer and increment the allocator position");
    verify(allocator.position == amount);
    verify(allocator.data != NULL);
    verify(buffer_data(&allocator, position) != NULL);


  success();
    buffer_release(&allocator);
}
