test( vector_get, position_out_of_bounds ) {

  given("a struct vector");
    struct vector vector;
    struct memory allocator = memory_init(0);
    vector = vector_init(sizeof(u64), 8, &allocator);


  when("the vector has some elements in it");
    vector_set(&vector, 0, &(u64) { 1 });
    vector_set(&vector, 1, &(u64) { 2 });
    vector_set(&vector, 2, &(u64) { 3 });


  when("an element is requested at position that is outside the bounds of the vector");
    u64 position = 5;


  calling("vector_get()");
    signal(SIGABRT, sigabrt_catch);
    sigabrt_caught = false;
    vector_get(&vector, position);


  must("abort the program");
    verify(sigabrt_caught = true);


  success();
    memory_release(&allocator);
}