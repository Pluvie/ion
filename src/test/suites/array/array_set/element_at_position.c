test( array_set, element_at_position ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);


  when("the array has some elements in it");
    for (u64 index = 0; index < 4; index++)
      array_push(&array, &index);


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("array_set()");
    u64 element = as(u64, array_set(&array, position, &(u64) { 99 }));


  must("set the correct element at that position");
    verify(element == 99);
    verify(array.length == 4);


  success();
    memory_release(&allocator);
}
