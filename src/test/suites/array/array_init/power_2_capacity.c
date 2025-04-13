test( array_init, power_2_capacity ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary;


  when("the array is provided a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("array_init()");
    ary = array_init(i32)(capacity, &allocator);


  must("initialize the array with the next power of 2 capacity");
    verify(ary.capacity == 128);


  success();
    memory_release(&allocator);
}
