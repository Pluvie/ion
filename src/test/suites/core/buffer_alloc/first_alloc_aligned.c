test( buffer_alloc, first_alloc_aligned ) {

  given("a buffer allocator");
    buffer allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);


  when("there are no allocations yet");
    verify(allocator.data == NULL);


  when("there is enough space to allocate");
    u64 amount = 24;


  calling("buffer_alloc()");
    u64 position = buffer_alloc(&allocator, amount);


  must("allocate buffer aligned to #MEMORY_DEFAULT_ALIGN bytes");
    verify(buffer_data(&allocator, position) != NULL);
    verify(((u64) allocator.data) % MEMORY_DEFAULT_ALIGN == 0);


  success();
    buffer_release(&allocator);
}
