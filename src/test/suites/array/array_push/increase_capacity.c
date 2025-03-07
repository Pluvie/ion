test( array_push, increase_capacity ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);
    verify(array.capacity == 8);


  when("the array has some elements in it");
    for (u64 index = 0; index < array.capacity; index++)
      array_push(&array, &index);


  calling("array_push()");
    array_push(&array, &(u64) { 99 });


  must("increase the capacity of the array to make space for the new element");
    u64 element = as(u64, array_last(&array));
    verify(element == 99);
    verify(array.capacity == 16);


  success();
    memory_release(&allocator);
}
