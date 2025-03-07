test( array_pop, decrease_length ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);
    verify(array.length == 0);


  when("the array has some elements in it");
    for (u64 index = 0; index < 4; index++)
      array_push(&array, &index);

    verify(array.length == 4);


  calling("array_pop()");
    u64 element = as(u64, array_pop(&array));


  must("increase the array length");
    verify(element == 3);
    verify(array.length == 3);


  success();
    memory_release(&allocator);
}
