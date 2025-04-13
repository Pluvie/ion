test( array_pop, preserve_capacity ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);
    verify(ary.capacity == 8);


  when("the array has some elements in it");
    for (i32 index = 0; index < 10; index++)
      array_push(i32)(&ary, &index);

    verify(ary.capacity == 16);


  calling("array_pop()");
    i32 element = as(i32, array_pop(i32)(&ary));


  must("preserve the capacity of the array");
    verify(element == 9);
    verify(ary.capacity == 16);


  success();
    memory_release(&allocator);
}
