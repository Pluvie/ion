test( array_push, increase_capacity ) {

  given("a declined array");
    array(i32) array = array_init(i32)(0, test_allocator);
    verify(array.length == 0);
    verify(array.capacity == 8);


  when("the array has some elements in it");
    for (u64 index = 0; index < array.capacity; index++)
      array_push(i32)(&array, &(i32) { index });


  calling("array_push()");
    array_push(i32)(&array, &(i32) { 99 });


  must("increase the capacity of the array to make space for the new element");
    i32 element = as(i32, array_last(i32)(&array));
    verify(element == 99);
    verify(array.capacity == 16);


  success();
}
