test( map_set, rehash_trigger ) {

  given("a declined map");
    memory allocator = memory_init(0);
    map(i32, i32) m = map_init(i32, i32)(0, &allocator);
    i32* original_keys_address = m.keys;


  when("the map has some entries in it, under the load factor");
    for (i32 index = 0; index < 7; index++)
      map_set(i32, i32)(&m, &index, &index);


  when("adding a new key and surpassing the load factor");
    i32 key = 10;
    i32 value = 10;


  calling("map_set()");
    map_set(i32, i32)(&m, &key, &value);


  must("trigger the map rehash and update the keys");
    verify(original_keys_address != m.keys);


  success();
    memory_release(&allocator);
}
