test( array_get, element_at_position ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);


  when("the array has some elements in it");
    for (i32 index = 0; index < 4; index++)
      array_push(i32)(&ary, &index);


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("array_get()");
    i32 element = as(i32, array_get(i32)(&ary, position));


  must("return the correct element at that position");
    verify(element == 2);


  success();
    memory_release(&allocator);
}
