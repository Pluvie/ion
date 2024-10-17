test( vector_init, correct_length ) {

  given("a struct vector");
    struct vector vector;
    struct memory allocator = memory_init(0);


  when("providing a length");
    u64 length = 3;


  calling("vector_init()");
    vector = vector_init(sizeof(u64), length, &allocator);


  must("initialize the vector with the provided length");
    verify(vector.length == length);


  success();
    memory_release(&allocator);
}
