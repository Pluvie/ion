test( array_pop, decrease_length ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);
    verify(ary.length == 0);


  when("the array has some elements in it");
    for (i32 index = 0; index < 4; index++)
      array_push(i32)(&ary, &index);

    verify(ary.length == 4);


  calling("array_pop()");
    i32 element = as(i32, array_pop(i32)(&ary));


  must("increase the array length");
    verify(element == 3);
    verify(ary.length == 3);


  success();
    memory_release(&allocator);
}
