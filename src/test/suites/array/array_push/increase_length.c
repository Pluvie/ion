test( array_push, increase_length ) {

  given("a declined array");
    array(i32) array = array_init(i32)(0, test_allocator);
    verify(array.length == 0);


  calling("array_push()");
    array_push(i32)(&array, &(i32) { 2 });


  must("increase the array length");
    i32 element = as(i32, array_get(i32)(&array, 0));
    verify(element == 2);
    verify(array.length == 1);


  success();
}
