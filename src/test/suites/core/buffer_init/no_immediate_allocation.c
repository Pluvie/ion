test( buffer_init, no_immediate_allocation ) {

  given("a struct buffer allocator");
    struct buffer allocator;


  calling("buffer_init()");
    allocator = buffer_init(MEMORY_DEFAULT_CAP);


  must("initialize the allocator but not allocate any buffer yet");
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);
    verify(allocator.data == NULL);


  success();
}
