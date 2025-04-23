test( array_init, power_2_capacity ) {

  given("a declined array");
    array(i32) array;


  when("the array is provided a capacity which is not a power of 2");
    u64 capacity = 77;


  calling("array_init()");
    array = array_init(i32)(capacity, test_allocator);


  must("initialize the array with the next power of 2 capacity");
    verify(array.capacity == 128);


  success();
}
