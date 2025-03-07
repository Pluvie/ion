test( memory_init, no_immediate_allocation ) {

  given("a struct memory allocator");
    struct memory allocator;


  calling("memory_init()");
    allocator = memory_init(MEMORY_DEFAULT_CAP);


  must("initialize the allocator but not allocate any memory yet");
    verify(allocator.capacity == MEMORY_DEFAULT_CAP);
    verify(allocator.data == NULL);


  success();
}
