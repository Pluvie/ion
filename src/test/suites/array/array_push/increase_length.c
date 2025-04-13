test( array_push, increase_length ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);
    verify(ary.length == 0);


  calling("array_push()");
    array_push(i32)(&ary, &(i32) { 2 });


  must("increase the array length");
    i32 element = as(i32, array_get(i32)(&ary, 0));
    verify(element == 2);
    verify(ary.length == 1);


  success();
    memory_release(&allocator);
}
