test( array_init, immediate_allocation ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);


  calling("array_init()");
    array = array_init(sizeof(u64), 0, &allocator);


  must("initialize the array and immediately allocate its memory");
    verify(array.capacity > 0);
    verify(allocator.data != NULL);


  success();
    memory_release(&allocator);
}
