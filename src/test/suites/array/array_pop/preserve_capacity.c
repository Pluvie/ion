test( array_pop, preserve_capacity ) {

  given("a declined array");
    array(i32) array = array_init(i32)(0, test_allocator);
    verify(array.capacity == 8);


  when("the array has some elements in it");
    for (i32 index = 0; index < 10; index++)
      array_push(i32)(&array, &index);

    verify(array.capacity == 16);


  calling("array_pop()");
    i32 element = as(i32, array_pop(i32)(&array));


  must("preserve the capacity of the array");
    verify(element == 9);
    verify(array.capacity == 16);


  success();
}
