test( array_init, default_capacity ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);


  when("the array is provided a capacity inferior to the default");
    u64 capacity = 3;


  calling("array_init()");
    array = array_init(sizeof(u64), capacity, &allocator);


  must("initialize the array with #ARRAY_DEFAULT_CAP capacity");
    verify(array.capacity == ARRAY_DEFAULT_CAP);


  success();
    memory_release(&allocator);
}
