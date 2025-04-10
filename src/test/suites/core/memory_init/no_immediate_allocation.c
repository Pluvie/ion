test( memory_init, no_immediate_allocation ) {

  given("a memory allocator");
    memory allocator;


  calling("memory_init()");
    allocator = memory_init(MEMORY_DEFAULT_CAPACITY);


  must("initialize the allocator but not allocate any memory yet");
    verify(allocator.capacity == MEMORY_DEFAULT_CAPACITY);
    verify(allocator.data == NULL);


  success();
}
