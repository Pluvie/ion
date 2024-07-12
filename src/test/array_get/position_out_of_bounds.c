test( array_get, position_out_of_bounds ) {

  given("a struct array");
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


  calling("array_get()");
    signal(SIGABRT, sigabrt_catch);
    sigabrt_caught = false;
    array_get(&array, position);


  must("abort the program");
    verify(sigabrt_caught = true);


  success();
    memory_release(&allocator);
}
