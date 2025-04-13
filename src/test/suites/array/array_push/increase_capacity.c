test( array_push, increase_capacity ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);
    verify(ary.length == 0);
    verify(ary.capacity == 8);


  when("the array has some elements in it");
    for (u64 index = 0; index < ary.capacity; index++)
      array_push(i32)(&ary, &(i32) { index });


  calling("array_push()");
    array_push(i32)(&ary, &(i32) { 99 });


  must("increase the capacity of the array to make space for the new element");
    i32 element = as(i32, array_last(i32)(&ary));
    verify(element == 99);
    verify(ary.capacity == 16);


  success();
    memory_release(&allocator);
}
