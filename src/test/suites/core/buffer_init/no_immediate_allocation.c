test( buffer_init, no_immediate_allocation ) {

  given("a buffer allocator");
    buffer allocator;


  calling("buffer_init()");
    allocator = buffer_init(MEMORY_DEFAULT_CAPACITY);


  must("initialize the allocator but not allocate any buffer yet");
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);
    verify(allocator.data == NULL);


  success();
}
