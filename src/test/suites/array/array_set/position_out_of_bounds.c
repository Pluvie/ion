test( array_set, position_out_of_bounds ) {

  given("an array");
    struct array array;
    struct memory allocator = memory_init(0);
    array = array_init(sizeof(u64), 8, &allocator);


  when("the array has some elements in it");
    u64 element = 3;
    array_push(&array, &element);
    array_push(&array, &element);
    array_push(&array, &element);


  when("an element is requested at position that is outside the bounds of the array");
    u64 position = 5;


  calling("array_set()");
    void* address = array_set(&array, position, &(u64) { 99 });


  must("return NULL and fail with a specific error");
    verify(error.occurred == true);
    verify(address == NULL);
    verify(streq(error.message, "position 5 out of bounds."));


  success();
    memory_release(&allocator);
}
