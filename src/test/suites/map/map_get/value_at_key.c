test( map_get, value_at_key ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(i32, i32) m = map_init(i32, i32)(0, &allocator);


  when("the map has some keys in it");
    for (i32 index = 0; index < 3; index++)
      map_set(i32, i32)(&m, &index, &index);


  when("an element is requested at a specific key");
    i32 key = 2;


  calling("map_get()");
    i32 element = as(i32, map_get(i32, i32)(&m, &key));


  must("return the correct element at that key");
    verify(element == 2);


  success();
    memory_release(&allocator);
}
