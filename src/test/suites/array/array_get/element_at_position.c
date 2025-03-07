test( array_get, element_at_position ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);


  when("the array has some elements in it");
    for (u64 index = 0; index < 4; index++)
      array_push(&array, &index);


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("array_get()");
    u64 element = as(u64, array_get(&array, position));


  must("return the correct element at that position");
    verify(element == 2);


  success();
    memory_release(&allocator);
}
