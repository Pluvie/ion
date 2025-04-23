test( array_pop, decrease_length ) {

  given("a declined array");
    array(i32) array = array_init(i32)(0, test_allocator);
    verify(array.length == 0);


  when("the array has some elements in it");
    for (i32 index = 0; index < 4; index++)
      array_push(i32)(&array, &index);

    verify(array.length == 4);


  calling("array_pop()");
    i32 element = as(i32, array_pop(i32)(&array));


  must("increase the array length");
    verify(element == 3);
    verify(array.length == 3);


  success();
}
