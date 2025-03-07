test( array_pop, preserve_capacity ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);
    verify(array.capacity == 8);


  when("the array has some elements in it");
    for (u64 index = 0; index < 10; index++)
      array_push(&array, &index);

    verify(array.capacity == 16);


  calling("array_pop()");
    u64 element = as(u64, array_pop(&array));


  must("preserve the capacity of the array");
    verify(element == 9);
    verify(array.capacity == 16);


  success();
    memory_release(&allocator);
}
