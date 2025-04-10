test( memory_alloc, first_alloc_aligned ) {

  given("a memory allocator");
    memory allocator = memory_init(MEMORY_DEFAULT_CAPACITY);


  when("there are no allocations yet");
    verify(allocator.allocations == 0);


  when("there is enough space to allocate");
    u64 amount = 24;


  calling("memory_alloc()");
    void* allocation = memory_alloc(&allocator, amount);


  must("allocate memory aligned to #MEMORY_DEFAULT_ALIGN bytes");
    verify(allocation != NULL);
    verify(allocation == (void*) allocator.data);
    verify(((u64) allocator.data) % MEMORY_DEFAULT_ALIGN == 0);


  success();
    memory_release(&allocator);
}
