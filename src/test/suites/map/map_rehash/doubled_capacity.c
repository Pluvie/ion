test( map_rehash, doubled_capacity ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);
    map = map_init(sizeof(u64), sizeof(u64), 8, &allocator);
    u64 original_capacity = map.capacity;


  when("the map has some keys in it");
    for (u64 index = 0; index < 3; index++)
      map_set(&map, &index, &index);


  calling("map_rehash()");
    map_rehash(&map);


  must("double the map capacity");
    verify(map.capacity == 2 * original_capacity);


  success();
    memory_release(&allocator);
}
