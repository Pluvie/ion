test( map_set, rehash_trigger ) {

  given("a declined map");
    map(i32, i32) map = map_init(i32, i32)(0, test_allocator);
    i32* original_keys_address = map.keys;


  when("the map has some entries in it, under the load factor");
    for (i32 index = 0; index < 7; index++)
      map_set(i32, i32)(&map, &index, &index);


  when("adding a new key and surpassing the load factor");
    i32 key = 10;
    i32 value = 10;


  calling("map_set()");
    map_set(i32, i32)(&map, &key, &value);


  must("trigger the map rehash and update the keys");
    verify(original_keys_address != map.keys);


  success();
}
