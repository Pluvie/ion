test( array_init, default_capacity ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary;


  when("the array is provided a capacity inferior to the default");
    u64 capacity = 3;


  calling("array_init()");
    ary = array_init(i32)(capacity, &allocator);


  must("initialize the array with #ARRAY_CAPACITY_DEFAULT capacity");
    verify(ary.capacity == ARRAY_CAPACITY_DEFAULT);


  success();
    memory_release(&allocator);
}
