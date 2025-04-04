test( map_rehash, data_invariance ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);
    map = map_init(sizeof(u64), sizeof(u64), 8, &allocator);


  when("the map has some keys in it");
    for (u64 index = 0; index < 3; index++)
      map_set(&map, &index, &index);
    map_print(&map);


  calling("map_rehash()");
    map_rehash(&map);
    print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    print(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    map_print(&map);


  must("be invariant on keys and values");
    for (u64 index = 0; index < 3; index++)
      verify(as(u64, map_get(&map, &index)) == index);


  success();
    memory_release(&allocator);
}
