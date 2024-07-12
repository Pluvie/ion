test( memory_alloc_zero, zero_out ) {

  given("a struct memory allocator");
    struct memory allocator = memory_init(MEMORY_DEFAULT_CAP);


  when("some space is requested to allocate");
    u64 amount = 24;


  calling("memory_alloc_zero()");
    byte* allocation = memory_alloc_zero(&allocator, amount);


  must("allocate memory and zero out its value");
    verify(allocation != NULL);
    verify(allocator.data != NULL);
    for (u32 index = 0; index < amount; index++)
      verify(allocation[index] == 0);


  success();
    memory_release(&allocator);
}
