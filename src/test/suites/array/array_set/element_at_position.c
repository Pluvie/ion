test( array_set, element_at_position ) {

  given("a declined array");
    array(i32) array = array_init(i32)(0, test_allocator);


  when("the array has some elements in it");
    for (i32 index = 0; index < 4; index++)
      array_push(i32)(&array, &index);


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("array_set()");
    i32 element = as(i32, array_set(i32)(&array, position, &(i32) { 99 }));


  must("set the correct element at that position");
    verify(element == 99);
    verify(array.length == 4);


  success();
}
