test( array_init, immediate_allocation ) {

  given("a declined array");
    array(i32) array;
    verify(test_allocator->data == NULL);


  calling("array_init()");
    array = array_init(i32)(0, test_allocator);


  must("initialize the array and immediately allocate its memory");
    verify(array.capacity > 0);
    verify(test_allocator->data != NULL);


  success();
}
