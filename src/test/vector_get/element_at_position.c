test( vector_get, element_at_position ) {

  given("a struct vector");
    struct vector vector = vector_of(u64, { 0, 1, 2, 3, 4 });


  when("an element is requested at a specific position");
    u64 position = 2;


  calling("vector_get()");
    u64 element = as(u64, vector_get(&vector, position));


  must("return the correct element at that position");
    verify(element == 2);


  success();
}
