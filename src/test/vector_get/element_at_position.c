test( vector_get, element_at_position ) {

  given("a struct vector");
    struct vector vector;
    struct memory allocator = memory_init(0);
    vector = vector_init(sizeof(u64), 8, &allocator);


  when("the vector has some elements in it");
    for (u64 index = 0; index < 4; index++)
      vector_set(&vector, index, &index);


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("vector_get()");
    u64 element = as(u64, vector_get(&vector, position));


  must("return the correct element at that position");
    verify(element == 2);


  success();
    memory_release(&allocator);
}
