test( array_init, default_capacity ) {

  given("a declined array");
    array(i32) array;


  when("the array is provided a capacity inferior to the default");
    u64 capacity = 3;


  calling("array_init()");
    array = array_init(i32)(capacity, test_allocator);


  must("initialize the array with #ARRAY_CAPACITY_DEFAULT capacity");
    verify(array.capacity == ARRAY_CAPACITY_DEFAULT);


  success();
}
