test( array_push, stack_allocated ) {

  given("a stack allocated declined array");
    array(i32) array = array_of(i32, { 7, 8, 9 });
    verify(array.length == 3);


  calling("array_push()");
    i32* address = array_push(i32)(&array, &(i32) { 10 });


  must("return NULL and fail with a specific error");
    verify(error.occurred == true);
    verify(address == NULL);
    verify(error_is("cannot push on a stack allocated array"));


  success();
}
