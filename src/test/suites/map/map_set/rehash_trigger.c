test( map_set, rehash_trigger ) {

  given("a struct map");
    struct map map;
    struct memory allocator = memory_init(0);
    map = map_init(sizeof(u64), sizeof(u64), 8, &allocator);
    void* original_keys_address = map.keys;


  when("the map has some entries in it, under the load factor");
    for (u64 index = 0; index < 5; index++)
      map_set(&map, &index, &index);


  when("adding a new key and surpassing the load factor");
    u64 key = 10;
    u64 value = 10;


  calling("map_set()");
    map_set(&map, &key, &value);


  must("trigger the map rehash");
    verify(original_keys_address != map.keys);


  success();
    memory_release(&allocator);
}
