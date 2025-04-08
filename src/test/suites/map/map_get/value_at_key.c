test( map_get, value_at_key ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);
    map = map_init(sizeof(u32), sizeof(u32), 8, &allocator);


  when("the map has some keys in it");
    for (u32 index = 0; index < 3; index++)
      map_set(&map, &index, &index);


  when("an element is requested at a specific key");
    u32 key = 2;


  calling("map_get()");
    u32 element = as(u32, map_get(&map, &key));


  must("return the correct element at that key");
    verify(element == 2);


  success();
    memory_release(&allocator);
}
