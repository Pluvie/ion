test( array_get, position_out_of_bounds ) {

  given("a declined array");
    memory allocator = memory_init(0);
    array(i32) ary = array_init(i32)(0, &allocator);


  when("the array has some elements in it");
    i32 element = 3;
    array_push(i32)(&ary, &element);
    array_push(i32)(&ary, &element);
    array_push(i32)(&ary, &element);


  when("an element is requested at position that is outside the bounds of the array");
    u64 position = 5;


  calling("array_get()");
    i32* address = array_get(i32)(&ary, position);


  must("return NULL and fail with a specific error");
    verify(error.occurred == true);
    verify(address == NULL);
    verify(error_is("position 5 out of bounds"));


  success();
    memory_release(&allocator);
}
