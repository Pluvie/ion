test( array_init, immediate_allocation ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary;


  calling("array_init()");
    ary = array_init(i32)(0, &allocator);


  must("initialize the array and immediately allocate its memory");
    verify(ary.capacity > 0);
    verify(allocator.data != NULL);


  success();
    memory_release(&allocator);
}
