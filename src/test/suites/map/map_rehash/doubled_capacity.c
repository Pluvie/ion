test( map_rehash, doubled_capacity ) {

  given("a declined map");
    map(i32, i32) map = map_init(i32, i32)(0, test_allocator);
    u64 original_capacity = map.capacity;


  when("the map has some keys in it");
    for (i32 index = 0; index < 3; index++)
      map_set(i32, i32)(&map, &index, &index);


  calling("map_rehash()");
    map_rehash(i32, i32)(&map);


  must("double the map capacity");
    verify(map.capacity == 2 * original_capacity);


  success();
}
