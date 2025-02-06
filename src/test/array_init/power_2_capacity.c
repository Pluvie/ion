test( array_init, power_2_capacity ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);


  when("the array is provided a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("array_init()");
    array = array_init(sizeof(u64), capacity, &allocator);


  must("initialize the array with the next power of 2 capacity");
    verify(array.capacity == 128);


  success();
    memory_release(&allocator);
}
